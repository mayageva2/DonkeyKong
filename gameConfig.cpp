#include "gameConfig.h"
#include "general.h"

char GameConfig::currentBoard[MAX_Y][MAX_X] = {}; //Initialize static member 'currentBoard'

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

const void GameConfig::drawHammers(vector<Point>& hammers)//draws hammers on board
{
	for (const auto& hammer : hammers)
	{
		SetChar(hammer.x, hammer.y, HAMMER);
		Point::draw(HAMMER, hammer);
	}
}





