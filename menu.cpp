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
			screenKey = printChooseScreen(screens);
			loadChosenScreen(screenKey, screens, board, screenError, mario);
			break;
		case '9':
			exitMenu = true;
			break;
		}
	}
}

char Menu::printChooseScreen(std::vector<std::string> screens)
{
	size_t size = screens.size();
	int i = 0, j = 0;
	char counter = '1';
	while (size != 0)
	{
		switch (size)
		{
		case 1: {
			Point namePoints[1] = { Point(38, 16) };
			Point counterPoints[1] ={ Point(49, 18) }; //check place
			j = 0;
			printScreen(choose1Screen);
			addNames(1, counter, namePoints, counterPoints, screens);
			size--;
			break;
		}
		case 2: {
			Point namePoints[2] = { Point(20, 16), Point(56, 16) }; //check place
			Point counterPoints[2] = { Point(31, 18),  Point(67, 18) }; //check place
			j = 0;
			printScreen(choose2Screen);
			addNames(2, counter, namePoints, counterPoints, screens);
			size = size - 2;
			break;
		}
		default: {
			Point namePoints[3] = { Point(13, 16), Point(38, 16), Point(63, 16) };
			Point counterPoints[3] = { Point(24, 18), Point(49, 18), Point(74, 18) }; //check place
			j = 0;
			printScreen(choose3Screen);
			namePoints[i].draw(screens[i][j], namePoints[i]);
			addNames(3, counter, namePoints, counterPoints, screens);
			size = size - 3;
			break;
		}
		}
		if (size != 0)
		{
			gotoxy(61, 20);
			std::cout << "press 0 to next screens";
		}
		char key = _getch();
		if (key != '0')
			return key;
	}
}

void Menu::addNames(int size, char& counter, Point* namePoints, Point* counterPoints, std::vector<std::string>& screens)
{
	int j = 0;

	for (int i = 0; i < size; i++)
	{
		while (screens[i][j] != '\0')
		{
			namePoints[i].draw(screens[i][j], namePoints[i]);
			namePoints[i].x++;
			j++;
		}
		counterPoints[i].draw(counter, counterPoints[i]);
		counter++;
		j = 0;
	}

	for (int i = 0; i < size; i++)
	{
		screens.erase(screens.begin());
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

void Menu::loadChosenScreen(char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario)
{
	int i = screenKey - '0' -1;
	loadScreens(i, screens, board, screenError, mario);
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

