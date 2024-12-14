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
	int interval = 0;
	vector<Barrel>barrels;
	Barrel b(board);
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	Menu menu;

	mario.draw(mario.findMarioLocation());
	mario.state = MarioState::standing;

	while (true)
	{
		barrelsMovement(barrels, board, interval);

		if (moveCounter == 0)
		{
			Sleep(100);
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

		if (mario.state == MarioState::standing) // In case key wasn't prased
		{
			mario.checkCollide(board);
			Sleep(200);
		}
		++interval;

	}
	gotoxy(0, GameConfig::MAX_Y + 2);
	barrels.clear(); //Clear barrels array

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
		if (_kbhit() && moveCounter != -1)
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
		else if (moveCounter == -1)  //ends jump
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

void Game::barrelsMovement(std::vector<Barrel>& barrels, GameConfig& board, int& interval)
{
	if (interval % 20 == 0)
	{
		barrels.emplace_back(board); //Create new Barrel
		if (interval % 40 == 0)
		{
			barrels.back().dropDirection = false; // Change drop direction
		}
	}

	for (size_t i = 0; i < barrels.size();)
	{
		barrels[i].moveBarrel(board); // Move new barrel

		//Clean barrels that got to the end of screen
		if (barrels[i].getLocation().x >= 75 || barrels[i].getLocation().x <= 1 || (barrels[i].isBarrelActive() == false))
		{
			barrels[i].clearFromScreen(board);
			barrels.erase(barrels.begin() + i);
		}
		i++;
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
	mario.draw(mario.findMarioLocation());
}