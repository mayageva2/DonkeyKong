#include "gameConfig.h"
#include <iostream>
#include "general.h"
using namespace std;

void GameConfig::PrintBoard()
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		cout << originalBoard[i] << '\n';
	}
	cout << originalBoard[MAX_Y - 1];
}

void GameConfig::resetBoard()
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void GameConfig::PrintKong()
{
	gotoxy(4, 4);
	std::cout << "\xF0\x9F\x99\x89";
}
