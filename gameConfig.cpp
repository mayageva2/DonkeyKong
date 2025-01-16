#include "gameConfig.h"
#include "general.h"
#include "mario.h"
#include "point.h"
#include "menu.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <fstream>

Point GameConfig::marioPos = { 0, 0 };
Point GameConfig::donkeyPos = { 0, 0 };
Point GameConfig::hammerPos = { 0, 0 };
Point GameConfig::legendPos = { 0, 0 };

void GameConfig::load(const std::string& filename, bool& error) 
{
	std::ifstream screen_file(filename);
	int curr_row = 0;
	int curr_col = 0;
	char c;
	GhostsPos.clear();
	GhostsPos.shrink_to_fit();
	initBoard();
	ghostPosError = false;
	legendError = false;
	oversizeScreen = false;

	while (!screen_file.get(c).eof() && curr_row <= MAX_Y) 
	{
		if (c == '\n') {
			if (curr_col < MAX_X) 
			{
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col <= MAX_X) {
			if (curr_row == MAX_Y || curr_col == MAX_X)
			{
				if (c != ' ')
				{
					oversizeScreen = true;
				}
			}
			else if (c == '@') 
			{
				marioCounter++;
				if (marioCounter > 1)
				{
					originalBoard[marioPos.y][marioPos.x] = DELETE_CH;
					marioCounter--;
				}
				marioPos = { curr_col, curr_row };
			}
			else if (c == '&') 
			{
				c = DELETE_CH;
				if (donkeyCounter < 1)
				{
					donkeyPos = { curr_col, curr_row };
					c = '&';
				}
				donkeyCounter++;
			}
			else if (c == 'x')
			{
				Point p = { curr_col, curr_row };
				GhostsPos.push_back(p);
				ghostCounter++;
			}
			else if (c == 'p')
			{
				hammerCounter++;
				if (hammerCounter > 1)
				{
					originalBoard[hammerPos.y][hammerPos.x] = DELETE_CH;
					hammerCounter--;
				}
				hammerPos = { curr_col, curr_row };
			}
			else if (c == 'L')
			{
				legendCounter++;
				legendPos = { curr_col, curr_row };
			}
			else if (c == '$')
			{
				c = DELETE_CH;
				if (PaulineCounter < 1)
				{
					c = '$';
				}
				PaulineCounter++;
			}
			else if(c != DELETE_CH && c!= 'H' && c!= '<' && c!= '>' && c!= '=')
			{
				c = DELETE_CH;
			}

			if(curr_col < MAX_X && curr_row < MAX_Y)
				originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	addFrame();

	if (isGhostsOnFloor())
		error = true;
	if (marioCounter < 1 || legendCounter != 1 || PaulineCounter < 1)
		error = true;
	if (insertLegend())
		error = true;
}

void GameConfig::initBoard()
{
	for (int i = 0; i < MAX_Y; ++i) 
	{
		for (int j = 0; j < MAX_X; ++j) 
		{
			originalBoard[i][j] = DELETE_CH;
		}
	}
}

void GameConfig::addFrame()
{
	for (int i = 0; i < MAX_X; ++i) 
	{
		originalBoard[0][i] = 'Q';
		originalBoard[MAX_Y - 1][i] = 'Q';
	}

	for (int i = 0; i < MAX_Y; ++i) 
	{
		originalBoard[i][0] = 'Q';
		originalBoard[i][MAX_X - 1] = 'Q';
	}
}

bool GameConfig::isGhostsOnFloor()
{
	size_t size = GhostsPos.size();
	for (size_t i = 0; i < size; i++)
	{
		char ch = originalBoard[GhostsPos[i].y + 1][GhostsPos[i].x];
		if (ch != '<' && ch != '>' && ch != '=' && ch != 'Q')
		{
			ghostPosError = true;
			return true;
		}
	}
	return false;

}

void GameConfig::printErrors()
{
	clrscr();
	if (oversizeScreen)
	{
		std::cout << "Error Message: The screen exceeds the authorized size: the next errors may happen due to screen resizing\n";
	}
	if (marioCounter < 1)
	{
		std::cout << "Error Message: Mario char is missing\n";
	}
	if (legendCounter < 1)
	{
		std::cout << "Error Message: Legend char is missing\n";
	}
	if (PaulineCounter < 1)
	{
		std::cout << "Error Message: Pauline char is missing\n";
	}
	if (legendCounter > 1)
	{
		std::cout << "Error Message: More than one legend char\n";
	}
	if (ghostPosError)
	{
		std::cout << "Error Message: A ghost is positioned off the floor\n";
	}
	if (legendError)
	{
		std::cout << "Error Message: Insufficient space for the Legend\n";
	}
	std::cout << "\npress any key to continue to next screen\n";
	while (!_kbhit()) {}
}

bool GameConfig::insertLegend()
{
	if (legendPos.x + Menu::LegendX < (MAX_X - 1) && legendPos.y + Menu::LegendY < (MAX_Y - 1))
	{
		for (int i = 0; i < Menu::LegendY; i++)
		{
			for (int j = 0; j < Menu::LegendX; j++)
			{
				originalBoard[legendPos.y + i][legendPos.x + j] = Menu::legend[i][j];
			}
		}
	}
	else
	{
		legendError = true;
		return true;
	}

	return false;

}

void GameConfig::PrintBoard() const//prints board
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << originalBoard[i] << '\n';
	}
	std::cout << originalBoard[MAX_Y - 1];
}

void GameConfig::resetBoard() //resets to original board
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}
}

Point GameConfig::getGhostPos()
{
	Point ghostPos = GhostsPos[currentGhostIndex];
	currentGhostIndex = (currentGhostIndex + 1) % GhostsPos.size();
	return ghostPos;
}

void GameConfig::printHearts(Mario& mario) //this func print hearts on screen
{
	gotoxy(legendPos.x + 15, legendPos.y);
	std::cout << mario.getNumOfHearts();
}

void GameConfig::printHammer()
{
	gotoxy(legendPos.x + 15, legendPos.y + 2);
	std::cout << "V";
}

void GameConfig::printScore(Mario& mario)
{
	gotoxy(legendPos.x + 15, legendPos.y + 1);
	std::cout << mario.getScore();
}


void GameConfig::init()
{
	ghostCounter = 0;
	marioCounter = 0;
	donkeyCounter = 0;
	hammerCounter = 0;
	legendCounter = 0;
	PaulineCounter = 0;
}

bool GameConfig::isDkongScreenFile(const std::string& filename)
{
	const std::string prefix = "dkong_";
	const std::string suffix = ".screen";

	return filename.size() > prefix.size() + suffix.size() &&
		filename.substr(0, prefix.size()) == prefix &&
		filename.substr(filename.size() - suffix.size()) == suffix;
}

std::vector<std::string> GameConfig::getDkongScreens(const std::string& directoryPath) //chat GPT solution
{
	std::vector<std::string> screens;

	for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
	{
		if (entry.is_regular_file()) 
		{
			std::string filename = entry.path().filename().string();
			if (isDkongScreenFile(filename)) {
				screens.push_back(entry.path().string());
			}
		}
	}

	std::sort(screens.begin(), screens.end());
	return screens;
}



