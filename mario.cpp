#include "mario.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "game.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void Mario::draw(const Point& pos) const  //this func draws mario in the location given
{
	gotoxy(pos.x, pos.y);
	cout << this->ch;
}

void Mario::move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter) //this func moves mario according to user's key
{
	bool sideJump = false;
	if (currBoard.GetChar(this->location.x, this->location.y) == 'O')
		collide(currBoard);
	currBoard.SetChar(this->location.x, this->location.y, ' '); //resets mario's previous location

	switch (key)
	{
	case GameConfig::eKeys::LEFT:
	case GameConfig::eKeys::LEFT2:
		state = MarioState::moving;
		left(currBoard, moveCounter);
		break;
	case GameConfig::eKeys::RIGHT:
	case GameConfig::eKeys::RIGHT2:
		state = MarioState::moving;
		right(currBoard, moveCounter);
		break;
	case GameConfig::eKeys::UP:
	case GameConfig::eKeys::UP2:
		state = MarioState::jumping;
		up(currBoard, moveCounter, sideJump);
		break;

	case GameConfig::eKeys::DOWN:
	case GameConfig::eKeys::DOWN2:
		state = MarioState::falling;
		down(currBoard, moveCounter, sideJump);
		break;
	case GameConfig::eKeys::STAY:
	case GameConfig::eKeys::STAY2:
		state = MarioState::standing;
		stay(currBoard);
		break;
	}

	if (currBoard.GetChar(this->location.x, this->location.y) == 'O')
		collide(currBoard);
	currBoard.SetChar(this->location.x, this->location.y, this->ch);
}

bool Mario::checkMove(GameConfig& currBoard, int x, int y)  //checks if mario hits a floor tile
{
	return currBoard.GetChar(x, y) != '<' && currBoard.GetChar(x, y) != '>';
}

bool Mario::isInBoard(GameConfig& currBoard, int x)  //checks if a point is on board
{
	return (x < GameConfig::MAX_X - 1 && x >= 1);
}

bool Mario::isMarioOnLadder(GameConfig& currBoard)
{
	return currBoard.GetChar(this->location.x, this->location.y) == 'H';
}

void Mario::left(GameConfig& currBoard, int& moveCounter)  //moves mario to the left
{
	bool isH = false;
	Point p(this->location);

	this->location.diff_x = -1;
	this->location.diff_y = 0;

	if (currBoard.GetChar(p.x, p.y) == 'H')  //checks if there's a ladder
	{
		p.draw('H', this->location);
		isH = true;
	}
	else
	{
		p.draw(' ', this->location);
		isH = false;
	}

	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(currBoard);
		Mario::draw(this->location);
		Sleep(100);
	}
	else
		stay(currBoard);

	moveCounter = 0;
}

void Mario::right(GameConfig& currBoard, int& moveCounter)   //moves mario to the right
{
	Point p(this->location);
	bool isH = false;

	this->location.diff_x = 1;
	this->location.diff_y = 0;

	if (currBoard.GetChar(p.x, p.y) == 'H')
	{
		p.draw('H', this->location);
		isH = true;
	}
	else
	{
		p.draw(' ', this->location);
		isH = false;
	}


	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(currBoard);
		Mario::draw(this->location);
		Sleep(100);
	}
	else
		stay(currBoard);

	moveCounter = 0;
}

void Mario::up(GameConfig& currBoard, int& moveCounter, bool& sideJump)  //makes mario jump or climb a ladder
{
	Point p(this->location);
	bool isH = false;

	if ((currBoard.GetChar(p.x, p.y) == 'H') || (!checkMove(currBoard, p.x, p.y) && currBoard.GetChar(p.x, p.y + 1) == 'H'))  //going up a ladder 
		isH = true;
	else    //jump
		isH = false;

	if (isH == false) //jump
	{
		if (moveCounter >= 0 && moveCounter < 2)
		{
			jumpUp(moveCounter, currBoard, sideJump);
		}
		else if (moveCounter >= 2 && moveCounter < 4)
			falling(moveCounter, currBoard, sideJump);

		if (moveCounter == 4)
			moveCounter = ENDJUMP;
	}
	else  //going up a ladder
	{
		climbUpAladder(moveCounter, currBoard);
	}
}

void Mario::jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump)
{
	Point p(this->location);

	if (isInBoard(currBoard, p.y - 1) && checkMove(currBoard, this->location.x, p.y - 1)) //checks if the desination is outside boundries and checks for ceiling
	{
		p.draw(' ', this->location);
		this->location.y -= 1;
		Mario::draw(this->location);
		Sleep(80);
		moveCounter++;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump);
		this->state = MarioState::falling;
		moveCounter = 4;
		sideJump = false;
	}

}

void Mario::falling(int& moveCounter, GameConfig& currBoard, bool& sideJump)
{
	Point p(this->location);

	if (!isMarioOnFloor(currBoard))
	{
		p.draw(' ', this->location);
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
			collide(currBoard);
		sideJump = false;
		moveCounter = 0;
	}
	didMarioWin(currBoard);
}

void Mario::climbUpAladder(int& moveCounter, GameConfig& currBoard)
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y) == 'H')
	{
		p.draw('H', this->location);
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

void Mario::down(GameConfig& currBoard, int& moveCounter, bool& sideJump)   //makes mario climb down by ladder
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y) == 'H')
	{
		if (!isMarioOnFloor(currBoard))
		{
			p.draw('H', this->location);
			this->location.y += 1;
		}
		else
		{
			stay(currBoard);
			moveCounter = ENDJUMP;
		}
	}
	else if ((currBoard.GetChar(p.x, p.y + 1) == 'H' || currBoard.GetChar(p.x, p.y + 2) == 'H') && sideJump == false)
	{
		char way = currBoard.GetChar(this->location.x, this->location.y);
		p.draw(way, this->location);
		this->location.y += 1;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump);
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
			left(currBoard, moveCounter);
		else if (key == (char)GameConfig::eKeys::RIGHT || key == (char)GameConfig::eKeys::RIGHT2)
			right(currBoard, moveCounter);
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

void Mario::jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump)   //this func allows mario to jump and move simultaneously
{
	Point p(this->location);
	bool isH = false;
	Game game;

	if (key == GameConfig::eKeys::LEFT || key == GameConfig::eKeys::LEFT2) //check if after jump mario should move left
	{
		this->location.diff_x = -2;
		this->location.diff_y = -2;

		if (currBoard.GetChar(p.x, p.y) == 'H')
		{
			moveCounter = 3;
		}
	}
	else if (key == GameConfig::eKeys::RIGHT || key == GameConfig::eKeys::RIGHT2)  //check if after jump mario should move right
	{
		this->location.diff_x = 2;
		this->location.diff_y = -2;
		if (currBoard.GetChar(p.x, p.y) == 'H')
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
		game.pauseGame(currBoard, *this);
		sideJump = false;
		return;
	}


	if (moveCounter >= 0 && moveCounter < 2)
	{
		up(currBoard, moveCounter, sideJump);
	}
	else if (moveCounter >= 2 && moveCounter < 4)
	{
		if (this->location.diff_x == -2)
		{
			if (moveCounter == 2)
			{
				left(currBoard, moveCounter);
				moveCounter = 2;
			}
			else
			{
				left(currBoard, moveCounter);
				moveCounter = 3;
			}
		}
		if (this->location.diff_x == 2)
		{
			if (moveCounter == 2)
			{
				right(currBoard, moveCounter);
				moveCounter = 2;
			}
			else
			{
				right(currBoard, moveCounter);
				moveCounter = 3;
			}
		}
		moveCounter++;
	}
	else if (moveCounter >= 4)
	{
		/*if (this->location.diff_x == 2)
			right(currBoard, moveCounter);
		else if(this->location.diff_x == -2)
			left(currBoard, moveCounter);
		else*/
		down(currBoard, moveCounter, sideJump);
	}
}

bool Mario::isMarioOnFloor(GameConfig& currBoard) //checks if mario stands on a floor
{
	Point p(this->location);

	if (currBoard.GetChar(p.x, p.y + 1) != '<' && currBoard.GetChar(p.x, p.y + 1) != '>' && currBoard.GetChar(p.x, p.y + 1) != '-')
		return false;
}

Point Mario::findMarioLocation()
{
	return (this->location);
}

void Mario::printLessHearts()
{
	this->num_of_hearts--;
	gotoxy(hearts.x, hearts.y);
	cout << this->num_of_hearts;
}

void Mario::printHearts()
{
	gotoxy(hearts.x, hearts.y);
	cout << this->num_of_hearts;
}

/*/void Mario::printLessHearts()//BETTER GAME
{
	gotoxy(heartsPro.x + this->num_of_hearts, heartsPro.y);
	cout << "  ";
}/*/

void Mario::collide(GameConfig& currBoard)
{
		gotoxy(this->location.x, this->location.y);
		cout << "BOOM";
		this->num_of_hearts--;
		Sleep(2000);
		didMarioLose(currBoard);
		this->location = start;
		Game game;
		game.startGame(*this);
		printHearts();
}

void Mario::didMarioLose(GameConfig& currBoard)
{
	if (num_of_hearts == 0)
	{
		stay(currBoard);
		clrscr();
		Menu menu;
		menu.displayEnd_Game(*this);
		return;
	}
}

void Mario::didMarioWin(GameConfig& currBoard)
{
	Point p(this->location);

	if (currBoard.GetChar(p.x + this->location.diff_x, p.y) == '$')   //checks if you reached pauline
	{
		draw(this->location);
		stay(currBoard);
		clrscr();
		Menu menu;
		Sleep(80);
		menu.printScreen(menu.win);
		Sleep(3000);
		menu.displayMenu(*this);
		return;
	}
}

void Mario::resetMario()
{
	this->num_of_hearts = FULL_LIFE;
	this->location = start;
}