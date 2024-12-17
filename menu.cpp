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
	bool exitMenu = false; //chatGPT solution
	Game game;
	bool flag = true;

	while (!exitMenu)
	{
		clrscr();
		printScreen(this->mainMenu);
		char key = _getch();
		switch (key)
		{
		case '1':
			mario.resetMario();
			game.startGame(mario, flag);
			break;
		case '8':
			printScreen(this->instructions);
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


