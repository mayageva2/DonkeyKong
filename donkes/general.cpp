#include "general.h"

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
using namespace std;

void gotoxy(int x, int y) //Move buffer
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrscr() //Clear screen
{
	system("cls");
}

void hideCursor() // chatGPT solution - get rid of cursor
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);      
	cursorInfo.bVisible = false;                     
	SetConsoleCursorInfo(hConsole, &cursorInfo);      
}


