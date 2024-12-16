#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"

#include <conio.h>
#include <Windows.h>


void Game::startGame(Mario& mario)
{
	if (mario.getNumOfHearts() == 0)
	{
		mario.resetMario();
	}
	clrscr();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	GameConfig board;
	board.resetBoard();
	board.PrintBoard();
	mario.printHearts();
	Barrel* barrels[Barrel::maxBarrels] = { nullptr };
	int numBarrels = 0;
	int interval = 0;
	int moveCounter = 0;
	int barrelMoveCounter = 2;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;

	mario.draw(mario.findMarioLocation());
	mario.state = MarioState::standing;

	while (true)
	{
		barrelsMovement(barrels, numBarrels, board, interval, mario);
		barrelMoveCounter = 0;

		if (moveCounter == 0)
		{
			Sleep(80);
			char inputKey = 0;

			if (_kbhit())
			{
				char inputKey = _getch();
				if ((GameConfig::eKeys)inputKey == GameConfig::eKeys::ESC)
				{
					pauseGame(board, mario);
				}
				else
				{
					key = inputKey;
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump);

		if (mario.state == MarioState::standing) 
		{
			if (board.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == 'O')
				mario.collide(board);
			Sleep(50);
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
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
				pauseGame(board, mario);
		}

		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::UP || (GameConfig::eKeys)key == GameConfig::eKeys::UP2))
	{
		Sleep(50);
		if (_kbhit() && moveCounter != ENDJUMP)
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp != GameConfig::eKeys::UP && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP2)
			{
				sideJump = true;
				lastKey = (GameConfig::eKeys)key;
				key = tmp;
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump);
				if ((GameConfig::eKeys)key == GameConfig::eKeys::ESC)
				{
					key = (char)GameConfig::eKeys::UP;
					lastKey = GameConfig::eKeys::STAY;
				}
			}
			else
			{
				return;
			}
		}
		else if (moveCounter == ENDJUMP)  //ends jump
		{
			moveCounter = 0;
			key = (char)lastKey;
			mario.move((GameConfig::eKeys)key, board, moveCounter);
		}
		else
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
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

void Game::barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario)
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

			if (barrels[i]->getLocation().x >= 78 || barrels[i]->getLocation().x <= 1 || !barrels[i]->isBarrelActive())
			{
				barrels[i]->clearFromScreen(board, mario);
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

void Game::pauseGame(GameConfig& board, Mario& mario)
{
	Menu menu;
	clrscr();
	menu.displayPause();

	char inputKey2 = 0;
	while (true)
	{
		if (_kbhit())
		{
			inputKey2 = _getch();
			if ((GameConfig::eKeys)inputKey2 == GameConfig::eKeys::ESC)
			{
				break;
			}
		}
	}
	clrscr();
	board.PrintBoard();
	mario.printHearts();
	mario.draw(mario.findMarioLocation());
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