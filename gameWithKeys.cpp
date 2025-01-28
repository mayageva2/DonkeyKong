#include "gameWithKeys.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "ghost.h"
#include "climbingGhost.h"
#include "nonClimbingGhost.h"
#include "results.h"
#include "steps.h"

#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;


void GameWithKeys::startGame(Mario& mario,GameConfig& board, bool& flag, bool& mariowin,bool& ifcolorMode)   //starts game
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clrscr();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	board.resetBoard();
	board.PrintBoard(ifcolorMode);
	board.printHearts(mario,ifcolorMode);
	board.printScore(mario,ifcolorMode);
	int interval = 0;
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	vector<Ghost*> ghosts;
	vector<Barrel> barrels;
	ghosts.reserve(board.getGhostsAmount());
	createGhosts(ghosts, board);
	int counter = 0;
  
	mario.draw(mario.findMarioLocation(), ifcolorMode);
	if(!mario.isMarioOnFloor(board))  //incase mario is positioned in the air
		mario.state = MarioState::falling;
	else
		mario.state = MarioState::standing;

	flag = true;
	while (flag)
	{
		counter++;
		for (int i = 0; i < ghosts.size(); i++)  //Move ghosts
			ghosts[i]->checkMove(board, mario, flag, ghosts, mariowin, ifcolorMode, steps, results);

		Barrel::barrelsMovement(barrels, board, interval, mario, flag, mariowin, ifcolorMode, steps, results); // Move Barrels

		if (moveCounter == 0) //Move Mario
		{
			Sleep(80);
			char inputKey = 0;

			if (_kbhit())
			{
				char inputKey = _getch();
				if ((GameConfig::eKeys)inputKey == GameConfig::eKeys::ESC)
				{
					if (ifcolorMode)
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					}
					pauseGame(board, mario, ifcolorMode);
				}
				else
				{
					steps.addStep(counter, inputKey);
					key = inputKey;
					if ((GameConfig::eKeys)key == lastKey && lastKey == GameConfig::eKeys::UP)
						lastKey = GameConfig::eKeys::STAY;
					marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);

		if (mario.state == MarioState::standing)
		{
			if (flag)
			{
				Point p1 = mario.findMarioLocation();
				if (board.GetCurrentChar(p1.x, p1.y) == BARREL_CH || board.GetCurrentChar(p1.x, p1.y) == NON_CLIMBING_GHOST_CH || board.GetCurrentChar(p1.x, p1.y) == CLIMBING_GHOST_CH)
					mario.collide(board, flag, mariowin, ifcolorMode, results, steps);
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
	ghosts.clear();  //Clear ghosts 
	ghosts.shrink_to_fit();
	barrels.clear(); //Clear barrels array
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//set default screen color
}

void GameWithKeys::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts,bool& ifcolorMode)   //makes sure mario goes as he should 
{
	
	if (sideJump == true)
	{
		if (_kbhit())
		{
			char tmp = _getch();
			if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
				pauseGame(board, mario, ifcolorMode);
		}
		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, currentIteration);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::KILL) || ((GameConfig::eKeys)key == GameConfig::eKeys::KILL2))
	{
		MarioState prevState = mario.state;
		mario.move(GameConfig::eKeys::KILL, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration);

		if (prevState == MarioState::moving) // if mario was walking before kill then keep walking after
		{
			key = (char)lastKey;
		}
		else
		{
			key = (char)GameConfig::eKeys::STAY; //mario was staying before killing
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
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, currentIteration);
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
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration);
		}
		else //mario is jumping
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration);
			lastKey = (GameConfig::eKeys)key;
		}
		else //incase mario is falling
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration);
	}

}

void GameWithKeys::pauseGame(GameConfig& board, Mario& mario, bool& ifcolorMode)  //pause the game
{
	clrscr();
	Menu::printScreen(Menu::pause);

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
	board.PrintBoard(ifcolorMode);
	board.printHearts(mario,ifcolorMode);
	board.printScore(mario, ifcolorMode);
	if (mario.hasHammer())
	{
		board.printHammer(ifcolorMode);
		Point::draw(DELETE_CH, GameConfig::getHammerPos(), ifcolorMode);
	}
	mario.draw(mario.findMarioLocation(), ifcolorMode);
	Point::draw(DELETE_CH, GameConfig::getMarioPos(), ifcolorMode);
}

bool GameWithKeys::isInLegend(Point& p, GameConfig& currBoard) //checks if mario is running over the legend
{
	Point legend = currBoard.getLegendPos();
	int min_x = legend.x;
	int max_x = legend.x + Menu::LegendX-1;
	int min_y = legend.y;
	int max_y = legend.y + Menu::LegendY-1;

	if (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y)
		return true;
	else
		return false;
}

void GameWithKeys::setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results) // checks if theres a ladder or floor and then goes to set char on board
{
	char ch = currBoard.GetCurrentChar(p.x, p.y);
	bool returnCh = isInLegend(p, currBoard);
	if (ch == LADDER_CH || ch == '<' || ch == '>' || ch == '=' || ch == 'Q' || ch == PAULINE_CH || returnCh)
	{
		currBoard.SetChar(p.x, p.y, object);
		Point p1 = mario.findMarioLocation();
		if (currBoard.GetCurrentChar(p1.x, p1.y) == BARREL_CH || currBoard.GetCurrentChar(p1.x, p1.y) == NON_CLIMBING_GHOST_CH || currBoard.GetCurrentChar(p1.x, p1.y) == CLIMBING_GHOST_CH)
			mario.collide(currBoard, flag, mariowin, ifcolorMode, results, steps);
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, object);
}

