#include "gameConfig.h"
#include "general.h"
#include "mario.h"
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

void GameConfig::load(const std::string& filename, bool& error) //this func loads a screen 
{
	std::ifstream screen_file(filename);
	int curr_row = 0;
	int curr_col = 0;
	char c;
	GhostsPos.clear();
	GhostsType.clear();
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
			if (curr_row == MAX_Y || curr_col == MAX_X) //is screen oversize
			{
				if (c != DELETE_CH)
				{
					oversizeScreen = true;
				}
			}
			else if (c == MARIO_CH) 
			{
				marioCounter++;
				if (marioCounter > 1) //if there's more than one Mario
				{
					originalBoard[marioPos.y][marioPos.x] = DELETE_CH;
					marioCounter--;
				}
				marioPos = { curr_col, curr_row };
			}
			else if (c == DONKEY_KONG_CH) 
			{
				c = DELETE_CH;
				if (donkeyCounter < 1) //if there's more than one DonkeyKong
				{
					donkeyPos = { curr_col, curr_row };
					c = DONKEY_KONG_CH;
				}
				donkeyCounter++;
			}
			else if (c == NON_CLIMBING_GHOST_CH || c == CLIMBING_GHOST_CH)
			{
				Point p = { curr_col, curr_row };
				GhostsPos.push_back(p);
				GhostsType.push_back(c);
				ghostCounter++;
			}
			else if (c == HAMMER)
			{
				hammerCounter++;
				if (hammerCounter > 1) //if there's more than one Hammer
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
			else if (c == PAULINE_CH)
			{
				c = DELETE_CH;
				if (PaulineCounter < 1) //if there's more than one Pauline
				{
					c = PAULINE_CH;
				}
				PaulineCounter++;
			}
			else if(c != DELETE_CH && c!= LADDER_CH && c!= '<' && c!= '>' && c!= '=')
			{
				c = DELETE_CH;
			}

			if(curr_col < MAX_X && curr_row < MAX_Y)
				originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	addFrame();

	//checking for errors in screen
	if (isGhostsOnFloor())
		error = true;
	if (marioCounter < 1 || legendCounter != 1 || PaulineCounter < 1)
		error = true;
	if (insertLegend())
		error = true;
}

void GameConfig::initBoard()  //initialize board
{
	for (int i = 0; i < MAX_Y; ++i) 
	{
		for (int j = 0; j < MAX_X; ++j) 
		{
			originalBoard[i][j] = DELETE_CH;
		}
	}
}

void GameConfig::addFrame() //add Q frame to screen
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

bool GameConfig::isGhostsOnFloor() //checks if ghosts are in the air
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

void GameConfig::printErrors() const //prints errors on screens
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

bool GameConfig::insertLegend() //insert legend to screen
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

void GameConfig::printHearts(GameRenderer& renderer, Mario& mario, bool& ifcolorMode) //this func print hearts on screen
{
	Point heartsNumPos = { legendPos.x + 15, legendPos.y };
	renderer.drawNumber(mario.getNumOfHearts(), heartsNumPos, ifcolorMode);
}

void GameConfig::PrintBoard(GameRenderer& renderer, bool& ifcolorMode) const //prints board
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0, 0);

	for (int i = 0; i < MAX_Y; i++) 
	{
		for (int j = 0; originalBoard[i][j] != '\0'; j++) 
		{
			Point pos(j, i);
			renderer.draw(originalBoard[i][j], pos, ifcolorMode);
		}
		std::cout << '\n';
	}
}

void GameConfig::resetBoard() //resets to original board
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}
}

Point GameConfig::getGhostPos()  //return ghosts positions
{
	Point ghostPos = GhostsPos[currentGhostIndex];
	currentGhostIndex = (currentGhostIndex + 1) % GhostsPos.size();
	return ghostPos;
}

char GameConfig::getGhostType() 
{
	char type = GhostsType[currentTypeIndex];
	currentTypeIndex = (currentTypeIndex + 1) % GhostsType.size();
	return type;
}

void GameConfig::printHammer(GameRenderer& renderer,bool& ifcolorMode) //prints hammer on screen 
{
	Point hammerPickedPos = { legendPos.x + 15,legendPos.y + 2 };
	renderer.draw('V', hammerPickedPos, ifcolorMode);
}

void GameConfig::printScore(GameRenderer& renderer, Mario& mario, bool& ifcolorMode) const//prints score on screen
{
	Point scorePos = { legendPos.x + 15, legendPos.y + 1 };
	renderer.drawNumber(mario.getScore(), scorePos, ifcolorMode);
}


void GameConfig::init()  //initialize counters
{
	ghostCounter = 0;
	marioCounter = 0;
	donkeyCounter = 0;
	hammerCounter = 0;
	legendCounter = 0;
	PaulineCounter = 0;
}

bool GameConfig::isDkongScreenFile(const std::string& filename) //check if file is a screen file
{
	const std::string prefix = "dkong_";
	const std::string suffix = ".screen";

	return filename.size() > prefix.size() + suffix.size() &&
		filename.substr(0, prefix.size()) == prefix &&
		filename.substr(filename.size() - suffix.size()) == suffix;
}

std::vector<std::string> GameConfig::getDkongScreens(const std::string& directoryPath) //chat GPT solution- gets screens
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



