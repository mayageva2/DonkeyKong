#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"

#include <conio.h>
#include <Windows.h>


void Game::startGame(Mario& mario,bool& flag)
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
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump,flag);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump,flag);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump,flag);

		if (mario.state == MarioState::standing)
		{
			if (board.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == barrelCh)
				mario.collide(board,flag);
			Sleep(50);
		}
		++interval;
	}
	
	deleteArray(barrels, numBarrels); //Clear barrels array
	//gotoxy(0, GameConfig::MAX_Y + 2);
}

void Game::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump,bool& flag)
{
	if (sideJump == true)
	{
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
				pauseGame(board, mario);
		}

		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump,flag);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::UP) || ((GameConfig::eKeys)key == GameConfig::eKeys::UP2) || ((GameConfig::eKeys)key == GameConfig::eKeys::UP3))
	{
		Sleep(50);
		if (_kbhit() && moveCounter != ENDJUMP)
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp != GameConfig::eKeys::UP && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP2 && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP3)
			{
				sideJump = true;
				lastKey = (GameConfig::eKeys)key;
				key = tmp;
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump,flag);
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
			mario.move((GameConfig::eKeys)key, board, moveCounter,flag);
		}
		else
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter,flag);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter,flag);
			lastKey = (GameConfig::eKeys)key;
			//moveCounter = 0;
		}
		else
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter,flag);
	}

}

void Game::barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario,bool& flag)
{
	if (interval % 20 == 0 && numBarrels < Barrel::maxBarrels)//Add a new barrel to the array
	{
		barrels[numBarrels] = new Barrel();
		barrels[numBarrels]->activate();
		if (interval % 40 == 0)//Change drop direction every 40 intervals
		{
			barrels[numBarrels]->dropDirection = false;
		}
		numBarrels++;
	}

	for (int i = 0; i < numBarrels;)
	{
			if (barrels[i]->isBarrelActive()) //Move barrel only if active
			{
				barrels[i]->moveBarrel(board, mario, flag);
				//Remove barrel from array if reached screen boundaries or became inactive
				if (barrels[i]->getLocation().x >= 78 || barrels[i]->getLocation().x <= 1 || !barrels[i]->isBarrelActive())
				{
					barrels[i]->clearFromScreen(board, mario, flag);//Print EXPLOSION
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
	if (barrels[index] != nullptr)
	{
		delete barrels[index]; 
		barrels[index] = nullptr;
	}


	if (index != numBarrels - 1)
	{
		barrels[index] = barrels[numBarrels - 1]; //Move last barrel to the deleted position- ChatGpt solution
		barrels[numBarrels - 1] = nullptr;
	}

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

void Game::setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario,bool& flag)
{
	char ch = currBoard.GetChar(p.x, p.y);
	if (ch == ladderCh || ch == '<' || ch == '>')
	{
		currBoard.SetChar(p.x, p.y, object);
		if (currBoard.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == barrelCh)
			mario.collide(currBoard,flag);
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, ch);
}