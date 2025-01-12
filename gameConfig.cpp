#include "gameConfig.h"
#include "general.h"
#include "mario.h"

#include <iostream>
using namespace std;

char GameConfig::currentBoard[MAX_Y][MAX_X] = {}; //Initialize static member - chatGPT solution

void GameConfig::PrintBoard(Mario& mario) //prints board
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		cout << originalBoard[i] << '\n';
	}
	cout << originalBoard[MAX_Y - 1];

	printHammer();
	mario.printHearts();
	mario.printHammers();
	mario.printScore();
}

void GameConfig::resetBoard() //resets to original board
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}
}



