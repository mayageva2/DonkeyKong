#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "menu.h"
#include <conio.h>
#include <Windows.h>


void Game::startGame(Mario& mario)
{
	clrscr();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	GameConfig board;
	board.resetBoard();
	board.PrintBoard();
	mario.printHearts();
	Barrel* barrels[Barrel::maxBarrels] = { nullptr };
	int numBarrels = 0;
	int interval = 0;
	int marioMoveCounter = 0;
	int barrelMoveCounter = 2;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;
	mario.draw(mario.findMarioLocation());

	while (true)
	{
		if (marioMoveCounter == 0)
		{
			Sleep(100);
			if (_kbhit())
			{
				key = _getch();
				if ((GameConfig::eKeys)key == GameConfig::eKeys::ESC)
				{
					menu.displayPauseScreen(board, mario);
				}
				marioMovement(mario, board, lastKey, key, marioMoveCounter, sideJump);
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, marioMoveCounter, sideJump);
		}
		else
			marioMovement(mario, board, lastKey, key, marioMoveCounter, sideJump);

		if (barrelMoveCounter ==2)
		{
			barrelsMovement(barrels,numBarrels, board, interval);
			barrelMoveCounter = 0;
		}

		if (mario.state == MarioState::standing || mario.state == MarioState::falling) // In case key wasn't prased
		{
			Sleep(100);
		}
		++interval;
		++barrelMoveCounter;


	}
	gotoxy(0, GameConfig::MAX_Y + 2);
	deleteArray(barrels, numBarrels); //Clear barrels array
}



void Game::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump)
{
	if (sideJump == true)
	{
		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump);
	}
	else if ((GameConfig::eKeys)key == GameConfig::eKeys::UP || (GameConfig::eKeys)key == GameConfig::eKeys::UP2)
	{
		Sleep(50);
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp != GameConfig::eKeys::UP && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP2)
			{
				sideJump = true;
				lastKey = (GameConfig::eKeys)key;
				key = tmp;
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump);
			}
			else
			{
				return;
			}
		}
		else if (moveCounter == -1)  //ends jump
		{
			moveCounter = 0;
			key = (char)lastKey;
			mario.move((GameConfig::eKeys)key, board, moveCounter);
		}
		else
			mario.move((GameConfig::eKeys)key, board, moveCounter);
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter);
			lastKey = (GameConfig::eKeys)key;
			//moveCounter = 0;
		}
		else
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter);
	}

}



void Game::barrelsMovement(Barrel** barrels,int& numBarrels, GameConfig& board, int& interval)
{
	if (interval % 20 == 0 && numBarrels < Barrel::maxBarrels)
	{
		barrels[numBarrels] = new Barrel();
		barrels[numBarrels]->activate();
		if (interval % 40 == 0)
		{
			barrels[numBarrels]->dropDirection = false;
		}
		numBarrels++;
	}

	for (int i = 0; i < numBarrels;)
	{
		if (barrels[i]->isBarrelActive())
		{
			barrels[i]->moveBarrel(board);

			if (barrels[i]->getLocation().x >= 79 || barrels[i]->getLocation().x <= 1 || !barrels[i]->isBarrelActive())
			{
				barrels[i]->clearFromScreen();
				barrels[i]->deactivate();
				deleteFromArray(barrels, i, numBarrels);
			}
			else
			{
				i++;
			}
		}
		else
		{
			deleteFromArray(barrels, i, numBarrels);
		}
	}
}

void Game::deleteFromArray(Barrel** barrels, int index, int& numBarrels)
{
	delete barrels[index];
	barrels[index] = barrels[numBarrels - 1];
	barrels[numBarrels - 1] = nullptr;
	numBarrels--;
}

void Game::deleteArray(Barrel** barrels, int& numBarrels)
{
	for (int i = 0; i < numBarrels; ++i)
	{
		if (barrels[i] != nullptr)
		{
			delete barrels[i];  
			barrels[i] = nullptr; 
		}
	}

	numBarrels = 0;
}
