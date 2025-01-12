#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "ghost.h"

#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;


void Game::startGame(Mario& mario,GameConfig& board, bool& flag, bool& mariowin)  //starts game
{
	clrscr();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	board.resetBoard();
	board.PrintBoard();
	board.printHearts(mario);
	Barrel* barrels[Barrel::maxBarrels] = { nullptr };
	int numBarrels = 0;
	int interval = 0;
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;
	vector<Ghost> ghosts;
	ghosts.reserve(board.getGhostsAmount());
	createGhosts(ghosts, board);

	mario.draw(mario.findMarioLocation());
	mario.state = MarioState::standing;

	flag = true;
	while (flag)
	{
		for (int i = 0; i < ghosts.size(); i++)
			ghosts[i].checkMove(board, mario, flag, ghosts, mariowin);

		barrelsMovement(barrels, numBarrels, board, interval, mario, flag, mariowin); // Move Barrels

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
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin);

		if (mario.state == MarioState::standing) 
		{
			if (flag)
			{
				if (board.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == BARREL_CH || board.GetChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == GHOST_CH)
					mario.collide(board, flag, mariowin);
				Sleep(100);
			}
		}
		if (mario.state == MarioState::falling)
		{
			if (flag)
				Sleep(50);
		}

		++interval;
	}
	gotoxy(0, MAX_Y + 2);
	ghosts.clear();
	ghosts.shrink_to_fit();
	deleteArray(barrels, numBarrels); //Clear barrels array
}

void Game::createGhosts(vector<Ghost>& ghosts, GameConfig& board)
{
	int amountOfGhosts = board.getGhostsAmount();
	for (int i = 0; i < amountOfGhosts; i++)
	{
		Point p1 = board.getGhostPos();
		Ghost ghost(p1.x, p1.y);
		ghosts.push_back(ghost);
	}
}


void Game::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin)   //makes sure mario goes as he should 
{
	if (sideJump == true)
	{
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
				pauseGame(board, mario);
		}
		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin);
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
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin);
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
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin);
		}
		else
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin);
			lastKey = (GameConfig::eKeys)key;
		}
		else
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter, flag, mariowin);
	}

}

void Game::barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin) //moves each barrel
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
			barrels[i]->moveBarrel(board, mario, flag, mariowin);

			//Remove barrel from array if reached screen boundaries or became inactive
			if (barrels[i]->getLocation().x >= 78 || barrels[i]->getLocation().x <= 1 || !barrels[i]->isBarrelActive())
			{
				barrels[i]->clearFromScreen(board, mario, flag, mariowin); //Print EXPLOSION
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
	board.printHearts(mario);
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

bool Game::isInLegend(Point& p, GameConfig& currBoard)
{
	Point legend = currBoard.getLegendPos();
	int min_x = legend.x;
	int max_x = legend.x + 19;
	int min_y = legend.y;
	int max_y = legend.y + 2;

	if (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y)
		return true;
	else
		return false;
}

void Game::setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin) // checks if theres a ladder or floor and then goes to set char on board
{
	char ch = currBoard.GetChar(p.x, p.y);
	bool returnCh = isInLegend(p, currBoard);
	if (ch == LADDER_CH || ch == '<' || ch == '>' || ch == '-' || ch == '|' || ch == 'Q' || ch == '$' || returnCh)
	{
		currBoard.SetChar(p.x, p.y, object);
		Point p1 = mario.findMarioLocation();
		if (currBoard.GetChar(p1.x, p1.y) == BARREL_CH || currBoard.GetChar(p1.x, p1.y) == GHOST_CH)
			mario.collide(currBoard, flag, mariowin);
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, object);
}

