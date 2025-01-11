#include "gameConfig.h"
#include <iostream>
#include "general.h"
using namespace std;

void GameConfig::PrintBoard() //prints board
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		cout << originalBoard[i] << '\n';
	}
	cout << originalBoard[MAX_Y - 1];
}

void GameConfig::resetBoard() //resets to original board
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}
}



