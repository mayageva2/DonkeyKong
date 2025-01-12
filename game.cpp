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


void Game::startGame(Mario& mario, bool& flag)  //starts game
{
	clrscr();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	GameConfig board;
	board.resetBoard();
	board.PrintBoard(mario);
	int interval = 0;
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;
	vector<Ghost> ghosts;
	vector<Barrel> barrels;
	ghosts.reserve(2);
	createGhosts(ghosts);

	mario.draw(mario.findMarioLocation());
	mario.state = MarioState::standing;

	flag = true;
	while (flag)
	{
		for (int i = 0; i < ghosts.size(); i++)
			ghosts[i].checkMove(board, mario, flag, ghosts);

		barrelsMovement(barrels, board, interval, mario, flag); // Move Barrels

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
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, barrels, ghosts);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, barrels, ghosts);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, barrels, ghosts);

		if (mario.state == MarioState::standing) 
		{
			if (board.GetCurrentChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == BARREL_CH)
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
	barrels.clear(); //Clear barrels array
}

void Game::createGhosts(vector<Ghost>& ghosts)
{
	Point p1(78, 10);
	int numGhostsToAdd = 1;

	for (int i = 0; i < numGhostsToAdd; i++)
	{
		Ghost ghost(p1.x, p1.y);
		ghosts.push_back(ghost);
		p1.x -= 3;
	}
}


void Game::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, vector<Barrel>& barrels, vector<Ghost>& ghosts)   //makes sure mario goes as he should 
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
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::KILL) || ((GameConfig::eKeys)key == GameConfig::eKeys::KILL2))//////NEED TO ADD LAST KEY TO MOVE/////////
	{
		MarioState prevState = mario.state;
		mario.move(GameConfig::eKeys::KILL, board, moveCounter, flag, ghosts, barrels);

		if (prevState != MarioState::standing) // if mario was walking before kill then keep walking after
		{
			key = (char)lastKey;
		}
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
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, ghosts, barrels);
		}
		else
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, ghosts, barrels);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, ghosts, barrels);
			lastKey = (GameConfig::eKeys)key;
		}
		else
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, ghosts, barrels);
	}

}

void Game::barrelsMovement(vector<Barrel>& barrels, GameConfig& board, int& interval, Mario& mario, bool& flag) //moves each barrel
{
	bool marioKilled = false;
	if (!flag) { return; }
	if (interval % 10 == 0)
	{
		barrels.emplace_back();  // Add a new barrel to the vector
		barrels.back().activate();
		if (interval % 20 == 0) //Change drop direction every 40 intervals
		{
			barrels.back().dropDirection = false;
		}
	}

	for (size_t i = 0; i < barrels.size();)
	{
		if (!flag) { break; }
		if (barrels[i].isBarrelActive()) //Move barrel only if active
		{
			barrels[i].moveBarrel(board, mario, flag);

			//Remove barrel from array if reached screen boundaries or became inactive
			if (barrels[i].getLocation().x >= 78 || barrels[i].getLocation().x <= 1 || !barrels[i].isBarrelActive())
			{
				barrels[i].clearFromScreen(board, mario, flag, marioKilled); //Print EXPLOSION
				barrels.erase(barrels.begin() + i);
			}
			else
			{
				i++; // Move to next barrel
			}
		}
		else
		{
			barrels.erase(barrels.begin() + i);
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
	board.PrintBoard(mario);
	mario.printHearts();
	mario.draw(mario.findMarioLocation());
}

void Game::setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag) // checks if theres a ladder or floor and then goes to set char on board
{
	char ch = currBoard.GetCurrentChar(p.x, p.y);
	if (ch == LADDER_CH || ch == '<' || ch == '>')
	{
		currBoard.SetChar(p.x, p.y, object);
		if (currBoard.GetCurrentChar(mario.findMarioLocation().x, mario.findMarioLocation().y) == BARREL_CH)
			mario.collide(currBoard, flag);
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, object);
}