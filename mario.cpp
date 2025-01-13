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

void Mario::move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, vector<Ghost>& ghosts, vector<Barrel>& barrels) //this func moves mario according to user's key
{
	bool sideJump = false;
	if ((currBoard.GetCurrentChar(this->location.x, this->location.y) == BARREL_CH || currBoard.GetCurrentChar(this->location.x, this->location.y) == GHOST_CH) && (char)key != 'p' && (char)key != 'P')
		collide(currBoard, flag, mariowin);
	if(flag)
		Game::setCharCheck(this->location, currBoard, DELETE_CH, *this, flag, mariowin); //resets mario's previous location

	switch (key)
	{
	case GameConfig::eKeys::LEFT:
	case GameConfig::eKeys::LEFT2:
		state = MarioState::moving;
		left(currBoard, moveCounter, flag, mariowin);
		break;
	case GameConfig::eKeys::RIGHT:
	case GameConfig::eKeys::RIGHT2:
		state = MarioState::moving;
		right(currBoard, moveCounter, flag, mariowin);
		break;
	case GameConfig::eKeys::UP:
	case GameConfig::eKeys::UP2:
		state = MarioState::jumping;
		up(currBoard, moveCounter, sideJump, flag, mariowin);
		break;

	case GameConfig::eKeys::DOWN:
	case GameConfig::eKeys::DOWN2:
		state = MarioState::falling;
		down(currBoard, moveCounter, sideJump, flag, mariowin);
		break;
	case GameConfig::eKeys::STAY:
	case GameConfig::eKeys::STAY2:
		state = MarioState::standing;
		stay(currBoard);
		break;
	case GameConfig::eKeys::KILL:
	case GameConfig::eKeys::KILL2:
		state = MarioState::killing;
		killEnemy(currBoard, *this, ghosts, barrels, flag, mariowin);
		break;
	}
	
  	if (flag)
   {
	    if (currBoard.GetCurrentChar(this->location.x, this->location.y) == HAMMER)//Mario reaches to hammer
	    	pickHammer(currBoard);
	    if (currBoard.GetCurrentChar(this->location.x, this->location.y) == BARREL_CH || currBoard.GetCurrentChar(this->location.x, this->location.y) == GHOST_CH)
	    	collide(currBoard, flag, mariowin);
	    if (flag)
		  	Game::setCharCheck(location, currBoard, this->ch, *this, flag, mariowin);
    }
}

bool Mario::checkMove(GameConfig& currBoard, int x, int y)  //checks if mario hits a floor tile
{
	return currBoard.GetCurrentChar(x, y) != '<' && currBoard.GetCurrentChar(x, y) != '>';
}

bool Mario::isInBoard(GameConfig& currBoard, int x)  //checks if a point is on board
{
	return (x < MAX_X - 1 && x >= 1);
}

bool Mario::isMarioOnLadder(GameConfig& currBoard)
{
	return currBoard.GetCurrentChar(this->location.x, this->location.y) == LADDER_CH;
}

void Mario::left(GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin)  //moves mario to the left
{
	bool isH = false;
	Point p(this->location);

	this->location.diff_x = -1;
	this->location.diff_y = 0;

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)  //checks if there's a ladder
	{
		p.draw(LADDER_CH, this->location);
		isH = true;
	}
	else if (Game::isInLegend(p, currBoard))
		p.draw(currBoard.GetCurrentChar(p.x, p.y), this->location);
	else
		p.draw(DELETE_CH, this->location);

	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		didMarioWin(currBoard, flag, mariowin);
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

void Mario::right(GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin)   //moves mario to the right
{
	Point p(this->location);
	bool isH = false;

	this->location.diff_x = 1;
	this->location.diff_y = 0;

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
	{
		p.draw(LADDER_CH, this->location);
		isH = true;
	}
	else if (Game::isInLegend(p, currBoard))
		p.draw(currBoard.GetCurrentChar(p.x, p.y), this->location);
	else
		p.draw(DELETE_CH, this->location);


	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(currBoard, flag, mariowin);
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

void Mario::up(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin)  //makes mario jump or climb a ladder
{
	Point p(this->location);
	bool isH = false;

	if ((currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH) || (!checkMove(currBoard, p.x, p.y) && currBoard.GetCurrentChar(p.x, p.y + 1) == LADDER_CH))  //going up a ladder 
		isH = true;
	else    //jump
		isH = false;

	if (isH == false) //jump
	{
		if (moveCounter >= 0 && moveCounter < 2)
		{
			jumpUp(moveCounter, currBoard, sideJump, flag, mariowin);
		}
		else if (moveCounter >= 2 && moveCounter < 4)
			falling(moveCounter, currBoard, sideJump, flag, mariowin);

		if (moveCounter == 4)
			moveCounter = ENDJUMP;
	}
	else  //going up a ladder
	{
		climbUpAladder(moveCounter, currBoard);
	}
}

void Mario::jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin) //this func makes mario jump up
{
	Point p(this->location);

	if (isInBoard(currBoard, p.y - 1) && checkMove(currBoard, this->location.x, p.y - 1)) //checks if the desination is outside boundries and checks for ceiling
	{
		if (Game::isInLegend(p, currBoard))
			p.draw(currBoard.GetCurrentChar(p.x, p.y), this->location);
		else
			p.draw(DELETE_CH, this->location);
		this->location.y -= 1;
		Mario::draw(this->location);
		Sleep(70);
		moveCounter++;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump, flag, mariowin);
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

void Mario::falling(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin) //this func makes mario fall down
{
	Point p(this->location);

	if (!isMarioOnFloor(currBoard))
	{
		if(Game::isInLegend(p, currBoard))
			p.draw(currBoard.GetCurrentChar(p.x, p.y), this->location);
		else
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
			collide(currBoard, flag, mariowin);
		sideJump = false;
		moveCounter = 0;
	}
	didMarioWin(currBoard, flag, mariowin);
}

void Mario::climbUpAladder(int& moveCounter, GameConfig& currBoard) //this func makes mario climb up on a ladder
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
	{
		p.draw(LADDER_CH, this->location);
	}
	else
	{
		char way = currBoard.GetCurrentChar(this->location.x, this->location.y);
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

void Mario::down(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin)   //makes mario climb down by ladder
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
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
	else if ((currBoard.GetCurrentChar(p.x, p.y + 1) == LADDER_CH || currBoard.GetCurrentChar(p.x, p.y + 2) == LADDER_CH) && sideJump == false)
	{
		char way = currBoard.GetCurrentChar(this->location.x, this->location.y);
		p.draw(way, this->location);
		this->location.y += 1;
	}
	else
	{
		falling(moveCounter, currBoard, sideJump, flag, mariowin);
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
			left(currBoard, moveCounter, flag, mariowin);
		else if (key == (char)GameConfig::eKeys::RIGHT || key == (char)GameConfig::eKeys::RIGHT2)
			right(currBoard, moveCounter, flag, mariowin);
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

void Mario::killEnemy(GameConfig& currBoard, Mario& mario, vector<Ghost>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin)
{
	if (hammer)
	{
		Point hammerUsePos = this->location;
		bool enemyKilled = false;

		for (int i = -2; i < 3; i++)
		{
			if (currBoard.GetCurrentChar(hammerUsePos.x + i, hammerUsePos.y) == GHOST_CH ||
				currBoard.GetCurrentChar(hammerUsePos.x + i, hammerUsePos.y) == BARREL_CH)
			{
				hammerUsePos.x += i;
				enemyKilled = true;
				break;
			}
		}

		if (enemyKilled)
		{
			num_of_points += 1000;
			currBoard.printScore(mario);
			deleteKilledEnemy(currBoard, hammerUsePos, ghosts, barrels, flag, mariowin); // Delete killed enemy
		}

	}
}

void Mario::deleteKilledEnemy(GameConfig& currBoard, Point killPos, vector<Ghost>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin)
{
	bool marioKilled = true;
	for (size_t i = 0; i < barrels.size();)
	{
		if (barrels[i].getLocation() == killPos)
		{
			barrels[i].clearFromScreen(currBoard, *this, flag, mariowin, marioKilled);
			break;
		}
		else
		{
			++i;
		}
	}

	if (currBoard.GetCurrentChar(killPos.x, killPos.y) == GHOST_CH) //Delete ghost
	{
		for (size_t i = 0; i < ghosts.size();)
		{
			if (ghosts[i].getLocation() == killPos)
			{
				ghosts[i].clearGhostFromScreen(currBoard, *this, flag, marioKilled, mariowin); // Delete ghost from screen
				ghosts.erase(ghosts.begin() + i);
				break;
			}
			else
			{
				++i;
			}
		}
	}

}

void Mario::jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin)   //this func allows mario to jump and move simultaneously
{
	Point p(this->location);
	bool isH = false;

	if (key == GameConfig::eKeys::LEFT || key == GameConfig::eKeys::LEFT2) //check if after jump mario should move left
	{
		this->location.diff_x = -2;
		this->location.diff_y = -2;

		if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
		{
			moveCounter = 3;
		}
	}
	else if (key == GameConfig::eKeys::RIGHT || key == GameConfig::eKeys::RIGHT2)  //check if after jump mario should move right
	{
		this->location.diff_x = 2;
		this->location.diff_y = -2;
		if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
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
		up(currBoard, moveCounter, sideJump, flag, mariowin);
	}
	else if (moveCounter >= 2 && moveCounter < 4)
	{
		if (this->location.diff_x == -2)
		{
			if (moveCounter == 2)
			{
				left(currBoard, moveCounter, flag, mariowin);
				moveCounter = 2;
			}
			else
			{
				left(currBoard, moveCounter, flag, mariowin);
				moveCounter = 3;
			}
		}
		if (this->location.diff_x == 2)
		{
			if (moveCounter == 2)
			{
				right(currBoard, moveCounter, flag, mariowin);
				moveCounter = 2;
			}
			else
			{
				right(currBoard, moveCounter, flag, mariowin);
				moveCounter = 3;
			}
		}
		moveCounter++;
	}
	else if (moveCounter >= 4)
		down(currBoard, moveCounter, sideJump, flag, mariowin);
	if (flag)
		Sleep(50);
}

bool Mario::isMarioOnFloor(GameConfig& currBoard) //checks if mario stands on a floor
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y + 1) != '<' && currBoard.GetCurrentChar(p.x, p.y + 1) != '>' && currBoard.GetCurrentChar(p.x, p.y + 1) != '-')
		return false;
}

Point Mario::findMarioLocation() //this func returns mario's location
{
	return (this->location);
}

void Mario::collide(GameConfig& currBoard, bool& flag, bool& mariowin)  //this func takes care of mario's explosion
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
		hammer = false;
		num_of_points = ZERO;
		this->location = GameConfig::getMarioPos();
		Game game;
		game.startGame(*this, currBoard, flag, mariowin);  /************************ !!!need to change to Game:: but startgame cant be static!!! ****************************/
	}
}

void Mario::didMarioLose(GameConfig& currBoard, bool& flag)  //checks if mario lost and if so returns to main menu
{
	if (num_of_hearts == 0)
	{
		num_of_points = ZERO;
		stay(currBoard);
		clrscr();
		Menu menu;
		menu.displayEnd_Game(*this);
		flag = false;
	}
}

void Mario::didMarioWin(GameConfig& currBoard, bool& flag, bool& mariowin) //checks if mario won and if so returns to main menu
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == '$')   //checks if you reached pauline
	{
		stay(currBoard);
		clrscr();
		Menu menu;
		Sleep(70);
		menu.printScreen(menu.win);
		Sleep(3000);
		flag = false;
		mariowin = true;
	}
}

void Mario::resetMario()  //this func initiallize mario's data members
{
	this->num_of_hearts = FULL_LIFE;
	this->hammer = false;
	this->location = GameConfig::getMarioPos();
}

void Mario::pickHammer(GameConfig& board)
{
	Point p(board.getLegendPos());
	setHammer(true);
	board.printHammer();
	board.SetChar(this->location.x, this->location.y, DELETE_CH);
}

void Mario::resetMarioPos()  //this func initiallize mario's position
{
	this->location = GameConfig::getMarioPos();
}