#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"

#include <conio.h>
#include <Windows.h>


void Game::startGame(Mario& mario, bool& flag)  //starts game
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
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;

	mario.draw(mario.findMarioLocation());
	mario.state = MarioState::standing;

	flag = true;
	while (flag)
	{
		barrelsMovement(barrels, numBarrels, board, interval, mario, flag); // Move Barrels

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
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag);

		if (mario.state == MarioState::standing) 
		{
			if (board.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == BARREL_CH)
				mario.collide(board, flag);
			if (flag)
				Sleep(100);
		}
		if (mario.state == MarioState::falling)
		{
			if (flag)
				Sleep(50);
		}

		++interval;
	}
	gotoxy(0, GameConfig::MAX_Y + 2);
	deleteArray(barrels, numBarrels); //Clear barrels array
}


void Game::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag)   //makes sure mario goes as he should 
{
	if (sideJump == true)
	{
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
				pauseGame(board, mario);
		}
		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::UP) || ((GameConfig::eKeys)key == GameConfig::eKeys::UP2))
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
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag);
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
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag);
		}
		else
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag);
			lastKey = (GameConfig::eKeys)key;
		}
		else
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter, flag);
	}

}

void Game::barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario, bool& flag) //moves each barrel
{
	if (!flag) { return; }
	if (interval % 10 == 0 && numBarrels < Barrel::maxBarrels)
	{
		barrels[numBarrels] = new Barrel();  //Add a new barrel to the array
		barrels[numBarrels]->activate();
		if (interval % 20 == 0) //Change drop direction every 40 intervals
		{
			barrels[numBarrels]->dropDirection = false;
		}
		numBarrels++;
	}

	for (int i = 0; i < numBarrels;)
	{
		if (!flag) { break; }
		if (barrels[i]->isBarrelActive()) //Move barrel only if active
		{
			barrels[i]->moveBarrel(board, mario, flag);

			//Remove barrel from array if reached screen boundaries or became inactive
			if (barrels[i]->getLocation().x >= 78 || barrels[i]->getLocation().x <= 1 || !barrels[i]->isBarrelActive())
			{
				barrels[i]->clearFromScreen(board, mario, flag); //Print EXPLOSION
				barrels[i]->deactivate();
				deleteFromArray(barrels, i, numBarrels);
			}
			else
			{
				i++; // Move to next barrel
			}
		}
		else
		{
			deleteFromArray(barrels, i, numBarrels);
		}
	}
}

void Game::pauseGame(GameConfig& board, Mario& mario)  //pause the game
{
	Menu menu;
	clrscr();
	menu.printScreen(menu.pause);

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

void Game::deleteFromArray(Barrel** barrels, int index, int& numBarrels) //deletes barrels
{
	if (barrels[index] != nullptr)
	{
		delete barrels[index]; 
		barrels[index] = nullptr;
	}
	if (index != numBarrels - 1)
	{
		barrels[index] = barrels[numBarrels - 1];  //Move last barrel to the deleted position- ChatGpt solution
		barrels[numBarrels - 1] = nullptr;
	}
	numBarrels--;
}

void Game::deleteArray(Barrel** barrels, int& numBarrels) //deletes barrels array
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

void Game::setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag) // checks if theres a ladder or floor and then goes to set char on board
{
	char ch = currBoard.GetChar(p.x, p.y);
	if (ch == LADDER_CH || ch == '<' || ch == '>')
	{
		currBoard.SetChar(p.x, p.y, object);
		if (currBoard.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == BARREL_CH)
			mario.collide(currBoard, flag);
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, object);
}