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

Point GameConfig::marioPos(0, 0);
Point GameConfig::donkeyPos(0, 0);
Point GameConfig::hammerPos(0, 0);
Point GameConfig::legendPos(0, 0);

void GameConfig::load(const std::string& filename, bool& error) 
{
	std::ifstream screen_file(filename);
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
			}
			else if (c == '&') 
			{
				donkeyPos = { curr_col, curr_row };
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
				hammerPos = { curr_col, curr_row };
				hammerCounter++;
			}
			else if (c == 'L')
			{
				legendCounter++;
				legendPos = { curr_col, curr_row };
			}
			else if (c == '$')
			{
				PaulineCounter++;
			}

			originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	if (marioCounter != 1 || legendCounter != 1 || PaulineCounter != 1 || hammerCounter > 1 || donkeyCounter > 1)
		error = true;
	
	insertLegend();
}

void GameConfig::printErrors()
{
	clrscr();
	if (marioCounter < 1)
	{
		std::cout << "error message: mario char is missing\n";
	}
	if (legendCounter < 1)
	{
		std::cout << "error message: legend char is missing\n";
	}
	if (PaulineCounter < 1)
	{
		std::cout << "error message: Pauline char is missing\n";
	}
	if (marioCounter > 1)
	{
		std::cout << "error message: more than 1 mario\n";
	}
	if (hammerCounter > 1)
	{
		std::cout << "error message:  more than 1 hammer\n";
	}
	if (donkeyCounter > 1)
	{
		std::cout << "error message:  more than 1 donkeyKong\n";
	}
	if (PaulineCounter > 1)
	{
		std::cout << "error message: more than 1 pauline\n";
	}
	std::cout << "\npress any key to continue to next screen\n";
	while (!_kbhit()) {}
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

void GameConfig::PrintBoard(bool& ifcolorMode) const//prints board
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(0, 0);


	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; originalBoard[i][j] != '\0'; j++) {
			if (ifcolorMode) 
			{
				if (originalBoard[i][j] == LADDER_CH) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Yellow 
				}
				else if (originalBoard[i][j] == '>' || originalBoard[i][j] == '=' || originalBoard[i][j] == '<') {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN ); // Brown 
				}
				else if (originalBoard[i][j] == DONKEY_KONG_CH) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // Green
				}
				else if (originalBoard[i][j] == PAULINE_CH) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED| FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Purple
				}
				else if (originalBoard[i][j] == HAMMER) {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED ); // Purple
				}
				else if(originalBoard[i][j] !=DELETE_CH){
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
				}
				
			}

			std::cout << originalBoard[i][j];
		}
		std::cout << '\n';
	}

	if (ifcolorMode) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
	}
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

void GameConfig::printHearts(Mario& mario,bool& ifcolorMode) //this func print hearts on screen
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(legendPos.x + 15, legendPos.y);
	if (ifcolorMode)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	std::cout << mario.getNumOfHearts();
}

void GameConfig::printHammer(bool& ifcolorMode)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(legendPos.x + 15, legendPos.y + 2);
	if (ifcolorMode)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	std::cout << "V";
}

void GameConfig::printScore(Mario& mario, bool& ifcolorMode)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(legendPos.x + 15, legendPos.y + 1);
	if (ifcolorMode)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
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


