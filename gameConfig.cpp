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

//char GameConfig::currentBoard[MAX_Y][MAX_X] = {}; //Initialize static member - chatGPT solution

Point GameConfig::marioPos(0, 0);
Point GameConfig::donkeyPos(0, 0);
Point GameConfig::hammerPos(0, 0);
Point GameConfig::legendPos(0, 0);

void GameConfig::load(const std::string& filename, bool& error) 
{
	std::ifstream screen_file(filename);
	//cout << screen_file.is_open() << std::endl;
	// TODO: handle errors (all sort of...) - do not submit it like that :)
	int curr_row = 0;
	int curr_col = 0;
	char c;
	GhostsPos.clear();
	GhostsPos.shrink_to_fit();
	while (!screen_file.get(c).eof() && curr_row < MAX_Y) 
	{
		if (c == '\n') {
			if (curr_col < MAX_X) 
			{
				// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < MAX_X) {
			// handle special chars
			if (c == '@') 
			{
				marioPos = { curr_col, curr_row };
				marioCounter++;
				if (marioCounter > 1)
				{
					std::cout << "error message : mario counter";
					error = true;
					return;
				}
			}
			else if (c == '&') 
			{
				donkeyPos = { curr_col, curr_row };
				donkeyCounter++;
				if (donkeyCounter > 1)
				{
					std::cout << "error message: donkey counter";
					error = true;
					return;
				}
			}
			else if (c == 'x')
			{
				Point p = { curr_col, curr_row };
				GhostsPos.push_back(p);
				ghostCounter++;
			}
			else if (c == 'p')
			{
				hammerPos = { curr_col, curr_row };
				hammerCounter++;
				if (hammerCounter > 1)
				{
					std::cout << "error message = hammer counter";
					error = true;
					return;
				}
			}
			else if (c == 'L')
			{
				legendCounter++;
				legendPos = { curr_col, curr_row };
			}

			originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	if (hammerCounter < 1 || marioCounter < 1 || legendCounter < 1 || donkeyCounter < 1)
	{
		std::cout << "error message = object missing";
		error = true;
		return;
	}
	insertLegend();
}

void GameConfig::insertLegend()
{
	if (legendPos.x + Menu::LegendX <= MAX_X && legendPos.y + Menu::LegendY <= MAX_Y)
	{
		for (int i = 0; i < Menu::LegendY; i++)
		{
			for (int j = 0; j < Menu::LegendX; j++)
			{
				originalBoard[legendPos.y + i][legendPos.x + j] = Menu::legend[i][j];
			}
		}
	}
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

void GameConfig::init()
{
	ghostCounter = 0;
	marioCounter = 0;
	donkeyCounter = 0;
	hammerCounter = 0;
	legendCounter = 0;
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


