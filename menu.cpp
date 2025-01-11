#include <iostream>
#include <conio.h>
#include <windows.h> 

#include "menu.h"
#include "point.h"
#include "general.h"
#include "game.h"

const Point startMenu(8, 5);
bool flag = true;
const int START_GAME = 1;
const int INSTRUCTIONS = 8;
const int EXIT = 9;

void Menu::printScreen(const char** print) //prints screen
{
	Point p = startMenu;
	for (int i = 0; i < MENU_Y; i++)
	{
		gotoxy(p.x, p.y);
		std::cout << print[i];
		p.y++;
	}
}

void Menu::displayMenu(Mario& mario) // displays main menu
{
	GameConfig board;
	bool exitMenu = false; //chatGPT solution
	Game game;  /************************ !!!need to change to Game:: but startgame cant be static!!! ****************************/
	bool flag = true;
	bool screenError = false;
	char screenKey = DELETE_CH;
	std::string path = ".";
	std::vector<std::string> screens = board.getDkongScreens(path);

	while (!exitMenu)
	{
		clrscr();
		printScreen(mainMenu);
		board.init();
		char key = _getch();
		switch (key)
		{
		case '1':	
			loadScreens(0, screens, board, screenError, mario);
			break;
		case '8':
			printScreen(instructions);
			while (!_kbhit()) {}
			break;
		case '2':
			printScreen(chooseScreen);
			screenKey = _getch();
			choosescreen(screenKey, screens, board, screenError, mario);
			break;
		case '9':
			exitMenu = true;
			break;
		}
	}
}

void Menu::choosescreen(char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario)
{
	switch (screenKey)
	{
	case '1':
		loadScreens(0, screens, board, screenError, mario);
		break;
	case '2':
		loadScreens(1, screens, board, screenError, mario);
		break;
	case '3':
		loadScreens(2, screens, board, screenError, mario);
		break;
	}
}

void Menu::loadScreens(size_t i, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario)
{
	Game game;
	bool mariowin = true;
	for (i; i < screens.size(); i++)
	{
		board.init();
		if (mariowin)
		{
			board.load(screens[i], screenError);

			if (!screenError)
			{
				mariowin = false;
				mario.resetMarioPos();
				game.startGame(mario, board, flag, mariowin);
			}
		}
	}
	mario.resetMario();
}

void Menu::displayEnd_Game(Mario& mario)  //ends game
{
	printScreen(end_game);
	Sleep(2500);
	clrscr();
}

const char Menu::legend[Menu::LegendY][Menu::LegendX + 1] = {
	// 012345678901234567890
	  " lives              ",//0
	  " score              ",//1
	  " hammer             "//2
};

