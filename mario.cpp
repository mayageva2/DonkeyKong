#include "mario.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "game.h"
#include "barrel.h"
#include "ghost.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void Mario::draw(const Point& pos) const  //this func draws mario in the location given
{
	gotoxy(pos.x, pos.y);
	cout << this->ch;
}

void Mario::move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& flag) //this func moves mario according to user's key
{
	bool sideJump = false;
	if (currBoard.GetChar(this->location.x, this->location.y) == BARREL_CH || currBoard.GetChar(this->location.x, this->location.y) == GHOST_CH)
		collide(currBoard, flag);
	Game::setCharCheck(this->location, currBoard, DELETE_CH, *this, flag); //resets mario's previous location

	switch (key)
	{
	case GameConfig::eKeys::LEFT:
	case GameConfig::eKeys::LEFT2:
		state = MarioState::moving;
		left(currBoard, moveCounter, flag);
		break;
	case GameConfig::eKeys::RIGHT:
	case GameConfig::eKeys::RIGHT2:
		state = MarioState::moving;
		right(currBoard, moveCounter, flag);
		break;
	case GameConfig::eKeys::UP:
	case GameConfig::eKeys::UP2:
		state = MarioState::jumping;
		up(currBoard, moveCounter, sideJump, flag);
		break;

	case GameConfig::eKeys::DOWN:
	case GameConfig::eKeys::DOWN2:
		state = MarioState::falling;
		down(currBoard, moveCounter, sideJump, flag);
		break;
	case GameConfig::eKeys::STAY:
	case GameConfig::eKeys::STAY2:
		state = MarioState::standing;
		stay(currBoard);
		break;
	}
	

	if (currBoard.GetChar(this->location.x, this->location.y) == BARREL_CH || currBoard.GetChar(this->location.x, this->location.y) == GHOST_CH)
		collide(currBoard, flag);
	Game::setCharCheck(location, currBoard, this->ch, *this, flag);
}

bool Mario::checkMove(GameConfig& currBoard, int x, int y)  //checks if mario hits a floor tile
{
	return currBoard.GetChar(x, y) != '<' && currBoard.GetChar(x, y) != '>';
}

bool Mario::isInBoard(GameConfig& currBoard, int x)  //checks if a point is on board
{
	return (x < MAX_X - 1 && x >= 1);
}

bool Mario::isMarioOnLadder(GameConfig& currBoard)
{
	return currBoard.GetChar(this->location.x, this->location.y) == LADDER_CH;
}

void Mario::left(GameConfig& currBoard, int& moveCounter, bool& flag)  //moves mario to the left
{
	bool isH = false;
	Point p(this->location);

	this->location.diff_x = -1;
	this->location.diff_y = 0;

	if (currBoard.GetChar(p.x, p.y) == LADDER_CH)  //checks if there's a ladder
	{
		p.draw(LADDER_CH, this->location);
		isH = true;
	}
	else
	{
		p.draw(DELETE_CH, this->location);
		isH = false;
	}

	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(currBoard, flag);
		if (flag)
		{
			Mario::draw(this->location);
			Sleep(100);
		}
	}
	else
		stay(currBoard);

	moveCounter = 0;
}

void Mario::right(GameConfig& currBoard, int& moveCounter, bool& flag)   //moves mario to the right
{
	Point p(this->location);
	bool isH = false;

	this->location.diff_x = 1;
	this->location.diff_y = 0;

	if (currBoard.GetChar(p.x, p.y) == LADDER_CH)
	{
		p.draw(LADDER_CH, this->location);
		isH = true;
	}
	else
	{
		p.draw(DELETE_CH, this->location);
		isH = false;
	}


	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(currBoard, flag);
		if (flag)
		{
			Mario::draw(this->location);
			Sleep(100);
		}
		Mario::draw(this->location);
		//Sleep(100);
	}
	else
		stay(currBoard);

	moveCounter = 0;
}

void Mario::up(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag)  //makes mario jump or climb a ladder
{
	Point p(this->location);
	bool isH = false;

	if ((currBoard.GetChar(p.x, p.y) == LADDER_CH) || (!checkMove(currBoard, p.x, p.y) && currBoard.GetChar(p.x, p.y + 1) == LADDER_CH))  //going up a ladder 
		isH = true;
	else    //jump
		isH = false;

	if (isH == false) //jump
	{
		if (moveCounter >= 0 && moveCounter < 2)
		{
			jumpUp(moveCounter, currBoard, sideJump, flag);
		}
		else if (moveCounter >= 2 && moveCounter < 4)
			falling(moveCounter, currBoard, sideJump, flag);

		if (moveCounter == 4)
			moveCounter = ENDJUMP;
	}
	else  //going up a ladder
	{
		climbUpAladder(moveCounter, currBoard);
	}
}

void Mario::jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag) //this func makes mario jump up
{
	Point p(this->location);

	if (isInBoard(currBoard, p.y - 1) && checkMove(currBoard, this->location.x, p.y - 1)) //checks if the desination is outside boundries and checks for ceiling
	{
		p.draw(DELETE_CH, this->location);
		this->location.y -= 1;
		Mario::draw(this->location);
		Sleep(70);
		moveCounter++;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump, flag);
		this->state = MarioState::falling;
		moveCounter = 4;
		sideJump = false;
		if (isMarioOnFloor(currBoard))
		{
			stay(currBoard);
			moveCounter = 0;
		}
	}

}

void Mario::falling(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag) //this func makes mario fall down
{
	Point p(this->location);

	if (!isMarioOnFloor(currBoard))
	{
		p.draw(DELETE_CH, this->location);
		this->location.y += 1;
		Mario::draw(this->location);
		Sleep(80);
		moveCounter++;
	}
	else
	{
		if (sideJump)
			moveCounter -= 4;
		stay(currBoard);
		if (moveCounter > 4)
			collide(currBoard, flag);
		sideJump = false;
		moveCounter = 0;
	}
	didMarioWin(currBoard, flag);
}

void Mario::climbUpAladder(int& moveCounter, GameConfig& currBoard) //this func makes mario climb up on a ladder
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y) == LADDER_CH)
	{
		p.draw(LADDER_CH, this->location);
	}
	else
	{
		char way = currBoard.GetChar(this->location.x, this->location.y);
		p.draw(way, this->location);
		moveCounter = ENDJUMP;
	}

	this->location.y -= 1;

	Mario::draw(this->location);
	Sleep(80);
	moveCounter++;
	if (isMarioOnFloor(currBoard))
		stay(currBoard);

}

void Mario::down(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag)   //makes mario climb down by ladder
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y) == LADDER_CH)
	{
		if (!isMarioOnFloor(currBoard))
		{
			p.draw(LADDER_CH, this->location);
			this->location.y += 1;
		}
		else
		{
			stay(currBoard);
			moveCounter = ENDJUMP;
		}
	}
	else if ((currBoard.GetChar(p.x, p.y + 1) == LADDER_CH || currBoard.GetChar(p.x, p.y + 2) == LADDER_CH) && sideJump == false)
	{
		char way = currBoard.GetChar(this->location.x, this->location.y);
		p.draw(way, this->location);
		this->location.y += 1;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump, flag);
		return;
	}

	if (!_kbhit())
	{
		Mario::draw(this->location);
		Sleep(80);
		moveCounter++;
	}
	else
	{
		this->location.y -= 1;
		char key = _getch();
		if ((key == (char)GameConfig::eKeys::STAY || key == (char)GameConfig::eKeys::STAY2) && (moveCounter != -1) && (this->state != MarioState::standing))
		{
			stay(currBoard);
			moveCounter = 0;
		}
		else if (key == (char)GameConfig::eKeys::LEFT || key == (char)GameConfig::eKeys::LEFT2)
			left(currBoard, moveCounter, flag);
		else if (key == (char)GameConfig::eKeys::RIGHT || key == (char)GameConfig::eKeys::RIGHT2)
			right(currBoard, moveCounter, flag);
	}
}

void Mario::stay(GameConfig& currBoard) //stops mario's movement
{
	Point p(this->location);
	this->location.diff_x = 0;
	this->location.diff_y = 0;

	Mario::draw(this->location);
	this->state = MarioState::standing;
}

void Mario::jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag)   //this func allows mario to jump and move simultaneously
{
	Point p(this->location);
	bool isH = false;

	if (key == GameConfig::eKeys::LEFT || key == GameConfig::eKeys::LEFT2) //check if after jump mario should move left
	{
		this->location.diff_x = -2;
		this->location.diff_y = -2;

		if (currBoard.GetChar(p.x, p.y) == LADDER_CH)
		{
			moveCounter = 3;
		}
	}
	else if (key == GameConfig::eKeys::RIGHT || key == GameConfig::eKeys::RIGHT2)  //check if after jump mario should move right
	{
		this->location.diff_x = 2;
		this->location.diff_y = -2;
		if (currBoard.GetChar(p.x, p.y) == LADDER_CH)
		{
			moveCounter = 3;
		}
	}
	else if (key == GameConfig::eKeys::STAY || key == GameConfig::eKeys::STAY2)
	{
		if (isMarioOnFloor(currBoard) || isMarioOnLadder(currBoard))  //block stay in the middle of jump
		{
			stay(currBoard);
			moveCounter = 0;
			sideJump = false;
			return;
		}
	}
	else if (key == GameConfig::eKeys::ESC)
	{
		Game::pauseGame(currBoard, *this);
		sideJump = false;
		return;
	}


	if (moveCounter >= 0 && moveCounter < 2)
	{
		up(currBoard, moveCounter, sideJump, flag);
	}
	else if (moveCounter >= 2 && moveCounter < 4)
	{
		if (this->location.diff_x == -2)
		{
			if (moveCounter == 2)
			{
				left(currBoard, moveCounter, flag);
				moveCounter = 2;
			}
			else
			{
				left(currBoard, moveCounter, flag);
				moveCounter = 3;
			}
		}
		if (this->location.diff_x == 2)
		{
			if (moveCounter == 2)
			{
				right(currBoard, moveCounter, flag);
				moveCounter = 2;
			}
			else
			{
				right(currBoard, moveCounter, flag);
				moveCounter = 3;
			}
		}
		moveCounter++;
	}
	else if (moveCounter >= 4)
		down(currBoard, moveCounter, sideJump, flag);
	if (flag)
		Sleep(50);
}

bool Mario::isMarioOnFloor(GameConfig& currBoard) //checks if mario stands on a floor
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y + 1) != '<' && currBoard.GetChar(p.x, p.y + 1) != '>' && currBoard.GetChar(p.x, p.y + 1) != '-')
		return false;
}

Point Mario::findMarioLocation() //this func returns mario's location
{
	return (this->location);
}

void Mario::printHearts() //this func print hearts on screen
{
	gotoxy(hearts.x, hearts.y);
	cout << this->num_of_hearts;
}

void Mario::collide(GameConfig& currBoard, bool& flag)  //this func takes care of mario's explosion
{
	if (location.x >= 77)
	{
		location.x = 75;
	}
	gotoxy(location.x, location.y);
	//Sleep(200);
	cout << EXPLOSION;
	this->num_of_hearts--;
	Sleep(2000);

	didMarioLose(currBoard, flag);
	if (flag)
	{
		this->location = start;
		Game game;
		game.startGame(*this, flag);  /************************ !!!need to change to Game:: but startgame cant be static!!! ****************************/
	}
}

void Mario::didMarioLose(GameConfig& currBoard, bool& flag)  //checks if mario lost and if so returns to main menu
{
	if (num_of_hearts == 0)
	{
		stay(currBoard);
		clrscr();
		Menu menu;
		menu.displayEnd_Game(*this);
		flag = false;
	}
}

void Mario::didMarioWin(GameConfig& currBoard, bool& flag) //checks if mario won and if so returns to main menu
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y) == '$')   //checks if you reached pauline
	{
		stay(currBoard);
		clrscr();
		Menu menu;
		Sleep(70);
		menu.printScreen(menu.win);
		Sleep(3000);
		flag = false;
	}
}

void Mario::resetMario()  //this func initiallize mario's data members
{
	this->num_of_hearts = FULL_LIFE;
	this->location = start;
}