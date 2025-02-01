#include "mario.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "gameWithKeys.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void Mario::move(GameActions& game, GameRenderer& renderer, GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, vector<Ghost*>& ghosts, vector<Barrel>& barrels,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter,bool& saveMode) //this func moves mario according to user's key
{
	bool sideJump = false;
	if (key != GameConfig::eKeys::KILL && key != GameConfig::eKeys::KILL2)
	{
		if (currBoard.GetCurrentChar(this->location.x, this->location.y) == BARREL_CH)
		{
			if (saveMode)
				results.addResult(counter, results.hitBarrel, curr_score);

			GameActions::hitByBarrel = true;
			collide(game,renderer,currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
		}
		else if(currBoard.GetCurrentChar(this->location.x, this->location.y) == CLIMBING_GHOST_CH || currBoard.GetCurrentChar(this->location.x, this->location.y) == NON_CLIMBING_GHOST_CH)
		{
			if (saveMode)
				results.addResult(counter, results.hitGhost, curr_score);

			GameActions::hitByGhost = true;
			collide(game,renderer,currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
		}
	}
	if(flag)
		game.setCharCheck(game,renderer,this->location, currBoard, DELETE_CH, *this, flag, mariowin,ifcolorMode, steps, results,saveMode); //resets mario's previous location

	switch (key)
	{
	case GameConfig::eKeys::LEFT:
	case GameConfig::eKeys::LEFT2:
		state = MarioState::moving;
		if(flag)
			left(renderer,currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
		break;
	case GameConfig::eKeys::RIGHT:
	case GameConfig::eKeys::RIGHT2:
		state = MarioState::moving;
		if (flag)
			right(renderer, currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
		break;
	case GameConfig::eKeys::UP:
	case GameConfig::eKeys::UP2:
		state = MarioState::jumping;
		if (flag)
			up(renderer, game,currBoard, moveCounter, sideJump, flag, mariowin,ifcolorMode, results, steps, counter,saveMode);
		break;

	case GameConfig::eKeys::DOWN:
	case GameConfig::eKeys::DOWN2:
		state = MarioState::falling;
		if (flag)
			down(renderer, game,currBoard, moveCounter, sideJump, flag, mariowin,ifcolorMode, results, steps, counter,saveMode);
		break;
	case GameConfig::eKeys::STAY:
	case GameConfig::eKeys::STAY2:
		state = MarioState::standing;
		if (flag)
		{
			stay(renderer, currBoard, ifcolorMode);
			moveCounter = 0;
		}
		break;
	case GameConfig::eKeys::KILL:
	case GameConfig::eKeys::KILL2:
		state = MarioState::killing;
		if (flag)
			killEnemy(renderer, game, counter, currBoard, *this, ghosts, barrels, flag, mariowin, ifcolorMode, results, steps, saveMode);
		break;
	}
	
  	if (flag)
   {
	    if (currBoard.GetCurrentChar(this->location.x, this->location.y) == HAMMER)//Mario reaches to hammer
	    	pickHammer(renderer,currBoard,ifcolorMode);
		
		if (currBoard.GetCurrentChar(this->location.x, this->location.y) == BARREL_CH)
		{
			if (saveMode)
				results.addResult(counter, results.hitBarrel, curr_score);

			GameActions::hitByBarrel = true;
			collide(game, renderer, currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
		}
		else if (currBoard.GetCurrentChar(this->location.x, this->location.y) == CLIMBING_GHOST_CH || currBoard.GetCurrentChar(this->location.x, this->location.y) == NON_CLIMBING_GHOST_CH)
		{
			if (saveMode)
				results.addResult(counter, results.hitGhost, curr_score);
			
			collide(game, renderer, currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
			GameActions::hitByGhost = true;
		}

	    if (flag)
		  	game.setCharCheck(game,renderer,location, currBoard, MARIO_CH, *this, flag, mariowin,ifcolorMode, steps, results,saveMode);
    }
}

bool Mario::checkMove(GameConfig& currBoard, int x, int y)  //checks if mario hits a floor tile
{
	return currBoard.GetCurrentChar(x, y) != '<' && currBoard.GetCurrentChar(x, y) != '>' && currBoard.GetCurrentChar(x, y) != '=';
}

bool Mario::isInBoard(GameConfig& currBoard, int x)  //checks if a point is on board
{
	return (x < MAX_X - 1 && x >= 1);
}

bool Mario::isMarioOnLadder(GameConfig& currBoard)  //checks if mario is on a ladder
{
	return currBoard.GetCurrentChar(this->location.x, this->location.y) == LADDER_CH;
}

void Mario::left(GameRenderer& renderer, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode)  //moves mario to the left
{
	bool isH = false;
	Point p(this->location);

	this->location.diff_x = -1;
	this->location.diff_y = 0;

	if (currBoard.GetCurrentChar(p.x, p.y) == DONKEY_KONG_CH)
		renderer.draw(DONKEY_KONG_CH, this->location, ifcolorMode);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH )  //checks if there's a ladder
	{
		renderer.draw(LADDER_CH, this->location, ifcolorMode);
		isH = true;
	}
	else if (GameActions::isInLegend(p, currBoard))
		renderer.draw(currBoard.GetCurrentChar(p.x, p.y), this->location, ifcolorMode);
	else 
		renderer.draw(DELETE_CH, this->location, ifcolorMode);

	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		didMarioWin(renderer,currBoard, flag, mariowin,ifcolorMode, results, counter, saveMode);
		if (flag)
		{
			renderer.draw(MARIO_CH,this->location, ifcolorMode);
			renderer.sleep(100);
		}
	}
	else
		stay(renderer,currBoard,ifcolorMode);

	moveCounter = 0;
}

void Mario::right(GameRenderer& renderer, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode)   //moves mario to the right
{
	Point p(this->location);
	bool isH = false;

	this->location.diff_x = 1;
	this->location.diff_y = 0;

	if (currBoard.GetCurrentChar(p.x, p.y) == DONKEY_KONG_CH)
		renderer.draw(DONKEY_KONG_CH, this->location, ifcolorMode);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
	{
		renderer.draw(LADDER_CH, this->location, ifcolorMode);
		isH = true;
	}
	else if (GameActions::isInLegend(p, currBoard))
		renderer.draw(currBoard.GetCurrentChar(p.x, p.y), this->location, ifcolorMode);
	else
		renderer.draw(DELETE_CH, this->location, ifcolorMode);


	if (checkMove(currBoard, p.x + this->location.diff_x, p.y + this->location.diff_y))
	{
		if (isInBoard(currBoard, p.x + this->location.diff_x))
			this->location.x += this->location.diff_x;

		if (isInBoard(currBoard, p.y + this->location.diff_y))
			this->location.y += this->location.diff_y;

		didMarioWin(renderer,currBoard, flag, mariowin,ifcolorMode, results, counter, saveMode);
		if (flag)
		{
			renderer.draw(MARIO_CH,this->location, ifcolorMode);
			renderer.sleep(100);
		}
		
		renderer.draw(MARIO_CH, this->location, ifcolorMode);
	}
	else
		stay(renderer,currBoard,ifcolorMode);

	moveCounter = 0;
}

void Mario::up(GameRenderer& renderer, GameActions& game, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode)  //makes mario jump or climb a ladder
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
			jumpUp(renderer,game,moveCounter, currBoard, sideJump, flag, mariowin,ifcolorMode, results, steps, counter, saveMode);
		}
		else if (moveCounter >= 2 && moveCounter < 4)
			falling(renderer,game,moveCounter, currBoard, sideJump, flag, mariowin,ifcolorMode, results, steps, counter,saveMode);

		if (moveCounter == 4)
			moveCounter = ENDJUMP;
		if (moveCounter > 4)
			climbUpAladder(renderer,moveCounter, currBoard, ifcolorMode);
	}
	else  //going up a ladder
	{
		climbUpAladder(renderer,moveCounter, currBoard, ifcolorMode);
	}
}

void Mario::jumpUp(GameRenderer& renderer, GameActions& game, int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode) //this func makes mario jump up
{
	Point p(this->location);

	if (isInBoard(currBoard, p.y - 1) && checkMove(currBoard, this->location.x, p.y - 1)) //checks if the desination is outside boundries and checks for ceiling
	{
		if (GameActions::isInLegend(p, currBoard))
			renderer.draw(currBoard.GetCurrentChar(p.x, p.y), this->location, ifcolorMode);
		else 
			renderer.draw(DELETE_CH, this->location,ifcolorMode);
		this->location.y -= 1;
		
		renderer.draw(MARIO_CH, this->location, ifcolorMode);
			renderer.sleep(70);
		
		moveCounter++;
	}
	else
	{
		falling(renderer,game,moveCounter, currBoard, sideJump, flag, mariowin,ifcolorMode, results, steps, counter,saveMode);
		this->state = MarioState::falling;
		moveCounter = 4;
		sideJump = false;
		if (isMarioOnFloor(currBoard))
		{
			stay(renderer,currBoard,ifcolorMode);
			moveCounter = 0;
		}
	}

}

void Mario::falling(GameRenderer& renderer,GameActions& game, int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter,bool& saveMode) //this func makes mario fall down
{
	Point p(this->location);

	if (!isMarioOnFloor(currBoard))
	{
		if(GameWithKeys::isInLegend(p, currBoard))
			renderer.draw(currBoard.GetCurrentChar(p.x, p.y), this->location, ifcolorMode);
		else 
			renderer.draw(DELETE_CH, this->location, ifcolorMode);
		this->location.y += 1;
		
		renderer.draw(MARIO_CH, this->location, ifcolorMode);
		renderer.sleep(80);
		moveCounter++;
	}
	didMarioWin(renderer,currBoard, flag, mariowin, ifcolorMode, results, counter, saveMode);

	if (isMarioOnFloor(currBoard))
	{
		state = MarioState::standing;
		if (sideJump)
		{
			moveCounter -= 4;
			state = MarioState::moving;
		}
		if (moveCounter > 4)
		{
			if (saveMode)
				results.addResult(counter, results.falling, curr_score);

			GameActions::fellToDeath = true;
			collide(game,renderer,currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
		}
		sideJump = false;
		moveCounter = ENDJUMP;
	}
  
	didMarioWin(renderer,currBoard, flag, mariowin,ifcolorMode, results, counter, saveMode);
}

void Mario::climbUpAladder(GameRenderer& renderer, int& moveCounter, GameConfig& currBoard,bool& ifcolorMode) //this func makes mario climb up on a ladder
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == DONKEY_KONG_CH)
		renderer.draw(DONKEY_KONG_CH, this->location, ifcolorMode);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH )
	{
		renderer.draw(LADDER_CH, this->location, ifcolorMode);
	}
	else //ends climbing
	{
		char way = currBoard.GetCurrentChar(this->location.x, this->location.y);
		
		renderer.draw(way, this->location, ifcolorMode);
		
		
		moveCounter = ENDJUMP;
		
		if (way != '>' && way != '=' && way != '<')
		{
			state = MarioState::standing;
			this->location.y += 2;
		}
	}

	this->location.y -= 1;


	renderer.draw(MARIO_CH, this->location, ifcolorMode);
		renderer.sleep(80);
	moveCounter++;
	if (isMarioOnFloor(currBoard))
		stay(renderer, currBoard,ifcolorMode);

}

void Mario::down(GameRenderer& renderer, GameActions& game, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter,bool& saveMode)   //makes mario climb down by ladder
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == DONKEY_KONG_CH)
		renderer.draw(DONKEY_KONG_CH, this->location, ifcolorMode);

	if (currBoard.GetCurrentChar(p.x, p.y) == LADDER_CH)
	{
		if (!isMarioOnFloor(currBoard))
		{
			renderer.draw(LADDER_CH, this->location, ifcolorMode);
			this->location.y += 1;
		}
		else
		{
			stay(renderer, currBoard,ifcolorMode);
			moveCounter = ENDJUMP;
		}
	}
	else if ((currBoard.GetCurrentChar(p.x, p.y + 1) == LADDER_CH || currBoard.GetCurrentChar(p.x, p.y + 2) == LADDER_CH) && sideJump == false)
	{
		char way = currBoard.GetCurrentChar(this->location.x, this->location.y);
		renderer.draw(way, this->location, ifcolorMode);
		this->location.y += 1;
	}
	else
	{
		falling(renderer, game,moveCounter, currBoard, sideJump, flag, mariowin,ifcolorMode, results, steps, counter,saveMode);
		return;
	}

	if (!_kbhit())
	{
		
		renderer.draw(MARIO_CH, this->location, ifcolorMode);
		renderer.sleep(80);
		moveCounter++;
	}
	else
	{
		this->location.y -= 1;
		char key = _getch();
		if ((key == (char)GameConfig::eKeys::STAY || key == (char)GameConfig::eKeys::STAY2) && (moveCounter != -1) && (this->state != MarioState::standing))
		{
			stay(renderer, currBoard,ifcolorMode);
			moveCounter = 0;
		}
		else if (key == (char)GameConfig::eKeys::LEFT || key == (char)GameConfig::eKeys::LEFT2)
			left(renderer,currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
		else if (key == (char)GameConfig::eKeys::RIGHT || key == (char)GameConfig::eKeys::RIGHT2)
			right(renderer, currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
	}
}

void Mario::stay(GameRenderer& renderer, GameConfig& currBoard,bool&ifcolorMode) //stops mario's movement
{
	Point p(this->location);
	this->location.diff_x = 0;
	this->location.diff_y = 0;
	
	renderer.draw(MARIO_CH, this->location, ifcolorMode);
	this->state = MarioState::standing;
}

void Mario::killEnemy(GameRenderer& renderer, GameActions& game, size_t& counter, GameConfig& currBoard, Mario& mario, vector<Ghost*>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode) //this func makes mario kill barrel or ghost
{
	if (hammer)
	{
		Point hammerUsePos = this->location;
		bool enemyKilled = false;

		for (int i = -2; i < 3; i++)
		{
			if (currBoard.GetCurrentChar(hammerUsePos.x + i, hammerUsePos.y) == NON_CLIMBING_GHOST_CH ||
				currBoard.GetCurrentChar(hammerUsePos.x + i, hammerUsePos.y) == CLIMBING_GHOST_CH ||
				currBoard.GetCurrentChar(hammerUsePos.x + i, hammerUsePos.y) == BARREL_CH)
			{
				hammerUsePos.x += i;
				enemyKilled = true;
				break;
			}
		}

		if (enemyKilled)
		{
			curr_score += 1000;
			currBoard.printScore(renderer,mario,ifcolorMode);
			deleteKilledEnemy(game, renderer, counter, currBoard, hammerUsePos, ghosts, barrels, flag, mariowin, ifcolorMode, results, steps, saveMode); // Delete killed enemy
		}

	}
}

void Mario::deleteKilledEnemy(GameActions& game, GameRenderer& renderer, size_t& counter, GameConfig& currBoard, Point killPos, vector<Ghost*>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps,bool& saveMode) //delets a barrel or ghost that mario killed
{
	bool marioKilled = true;
	for (size_t i = 0; i < barrels.size();)
	{
		if (barrels[i].getLocation() == killPos)
		{
			barrels[i].clearFromScreen(game,renderer, counter ,currBoard, *this, flag, mariowin, marioKilled,ifcolorMode, steps, results, saveMode);
			break;
		}
		else
		{
			++i;
		}
	}

	if (currBoard.GetCurrentChar(killPos.x, killPos.y) == NON_CLIMBING_GHOST_CH || currBoard.GetCurrentChar(killPos.x, killPos.y) == CLIMBING_GHOST_CH) //Delete ghost
	{
		for (size_t i = 0; i < ghosts.size();)
		{
			if (ghosts[i]->getLocation() == killPos)
			{
				ghosts[i]->clearGhostFromScreen(game,renderer,currBoard, *this, flag, marioKilled, mariowin,ifcolorMode, steps, results,saveMode); // Delete ghost from screen
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

void Mario::jumpToSide(GameRenderer& renderer, GameActions& game,GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode)   //this func allows mario to jump and move simultaneously
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
			stay(renderer,currBoard, ifcolorMode);
			moveCounter = 0;
			sideJump = false;
			return;
		}
	}
	else if (key == GameConfig::eKeys::ESC)
	{
		GameWithKeys::pauseGame(renderer,currBoard, *this, ifcolorMode);
		sideJump = false;
		return;
	}

	if (moveCounter >= 0 && moveCounter < 2)
	{
		up(renderer,game,currBoard, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, counter,saveMode);
	}
	else if (moveCounter >= 2 && moveCounter < 4)
	{
		if (this->location.diff_x == -2)
		{
			if (moveCounter == 2)
			{
				left(renderer,currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
				moveCounter = 2;
			}
			else
			{
				left(renderer, currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
				moveCounter = 3;
			}
		}
		if (this->location.diff_x == 2)
		{
			if (moveCounter == 2)
			{
				right(renderer, currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
				moveCounter = 2;
			}
			else
			{
				right(renderer, currBoard, moveCounter, flag, mariowin, ifcolorMode, results, counter, saveMode);
				moveCounter = 3;
			}
		}
		moveCounter++;
	}
	else if (moveCounter >= 4)
		down(renderer, game,currBoard, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, counter, saveMode);
	if (flag)
		renderer.sleep(50);
}


bool Mario::isMarioOnFloor(GameConfig& currBoard) //checks if mario stands on a floor
{
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y + 1) != '<' && currBoard.GetCurrentChar(p.x, p.y + 1) != '>' && currBoard.GetCurrentChar(p.x, p.y + 1) != 'Q' && currBoard.GetCurrentChar(p.x, p.y + 1) != '=')
		return false;
}

Point Mario::findMarioLocation() const //this func returns mario's location
{
	return (this->location);
}

void Mario::collide(GameActions& game, GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& mariowin,bool& ifcolorMode,Results& results, Steps& steps,bool& saveMode)  //this func takes care of mario's explosion
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (location.x >= 77)
	{
		location.x = 75;
	}
	renderer.drawString(EXPLOSION, MARIO_CH, this->location, ifcolorMode);
	this->num_of_hearts--;
	renderer.sleep(2000);

	didMarioLose(renderer,currBoard, flag,ifcolorMode);
	if (flag)
	{
		hammer = false;
		curr_score = last_score;
		this->location = GameConfig::getMarioPos();
		game.startGame(game,renderer,*this, currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
	}
}

void Mario::didMarioLose(GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& ifcolorMode)  //checks if mario lost and if so returns to main menu
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (num_of_hearts == 0)
	{
		curr_score = ZERO;
		stay(renderer, currBoard, ifcolorMode);
		renderer.clearScreen();
		if (ifcolorMode)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		Menu::displayEnd_Game(renderer, *this);
		flag = false;
	}
}

void Mario::didMarioWin(GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode) //checks if mario won and if so returns to main menu
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Point p(this->location);

	if (currBoard.GetCurrentChar(p.x, p.y) == PAULINE_CH)   //checks if you reached pauline
	{
		stay(renderer,currBoard,ifcolorMode);
		renderer.clearScreen();
		renderer.sleep(70);

		if (ifcolorMode)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		renderer.printScreen(Menu::winLevel);
		renderer.sleep(3000);
		flag = false;
		mariowin = true;

		if (saveMode)
			results.addResult(counter, Results::finished, curr_score);
		GameActions::MarioFinished = true;
		this->setLastScore();
	}
}

void Mario::resetMario()  //this func initiallize mario's data members
{
	this->num_of_hearts = FULL_LIFE;
	this->hammer = false;
	this->location = GameConfig::getMarioPos();
}

void Mario::pickHammer(GameRenderer& renderer, GameConfig& board, bool& ifcolorMode) //this func takes care of hammer when mario picks it up
{
	Point p(board.getLegendPos());
	setHammer(true);
	
		board.printHammer(renderer,ifcolorMode);
	
	board.SetChar(this->location.x, this->location.y, DELETE_CH);
}

void Mario::resetMarioPos()  //this func initiallize mario's position
{
	this->location = GameConfig::getMarioPos();
}