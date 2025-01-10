#include "menu.h"
#include "point.h"
#include "general.h"
#include "game.h"

#include <iostream>
#include <windows.h> 
#include <conio.h>
using namespace std;

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
		cout << print[i];
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

	while (!exitMenu)
	{
		clrscr();
		printScreen(mainMenu);
		board.init();
		char key = _getch();
		switch (key)
		{
		case '1':
			printScreen(chooseScreen);
			screenKey = _getch();
			switch (screenKey)
			{
			case '1':
				board.load("dkong_a.screen", screenError);
				break;
			case '2':
				board.load("dkong_b.screen", screenError);
				break;
			case '3':
				board.load("dkong_c.screen", screenError);
				break;
			}

			if (!screenError)
			{
				mario.resetMario();
				game.startGame(mario, board, flag);
			}
			break;
		case '8':
			printScreen(instructions);
			while (!_kbhit()) {}
			break;
		case '9':
			exitMenu = true;
			break;
		}
	}
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

