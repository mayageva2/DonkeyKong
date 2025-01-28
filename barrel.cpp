#include "barrel.h"
#include "mario.h"
#include "gameWithKeys.h"
#include "gameConfig.h"

void Barrel::clearFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& mariowin, bool& marioKilled,bool& ifcolorMode, Steps& steps, Results& results) //this function clears barrels from the screen
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GameWithKeys::setCharCheck(location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode, steps, results); //resets barrel's previous location

	if (mario.findMarioLocation().x == this->location.x && mario.findMarioLocation().y == this->location.y)
		mario.collide(board, flag, mariowin,ifcolorMode, results, steps);
	else
	{
		if (marioKilled) //don't explode on mario
		{
			if (mario.findMarioLocation().x > location.x)
				location.x -= 2;
		}

		if (location.x == MAX_X-2 && !marioKilled)
		{
			location.x = MAX_X - 5;
		}
		
			Point::draw(DELETE_CH, location, ifcolorMode);
			gotoxy(location.x, location.y);
			if (ifcolorMode)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			}
			cout << EXPLOSION;
			Sleep(80);
			for (int i = 0; i < 4; i++) // CLEANS 'BOOM' from screen
			{
				char originalCh = board.GetCurrentChar(location.x + i, location.y);
				Point tmp = location;
				tmp.x += i;
				Point::draw(originalCh, tmp, ifcolorMode);
			}
		
		if (marioCloseToExplosion(board, mario) && mario.state != MarioState::killing)
			mario.collide(board, flag, mariowin,ifcolorMode, results, steps);
	}
	deactivate();
}

void Barrel::moveBarrel(GameConfig& board,Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results) //this func moves barrels
{
	Point p(location.x, location.y);

	GameWithKeys::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin, ifcolorMode, steps, results); //resets barrel's previous location
	char originalChar = board.GetCurrentChar(location.x, location.y); //Restore the original character at the barrel's current location
	GameWithKeys::setCharCheck(location, board, originalChar, mario, flag, mariowin, ifcolorMode, steps, results);
	p.draw(originalChar, location, ifcolorMode); //print original char on board

	if (location == GameConfig::getDonkeyKongPos()) // if barrel crossed donkey kong
	{
		GameWithKeys::setCharCheck(location, board, DONKEY_KONG_CH, mario, flag, mariowin,ifcolorMode, steps, results);
		p.draw(DONKEY_KONG_CH, location, ifcolorMode); //return donkey kong's char
	}
	else
	{
		GameWithKeys::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode, steps, results); //resets barrel's previous location
		char originalChar = board.GetCurrentChar(location.x, location.y); //Restore the original character at the barrel's current location
		GameWithKeys::setCharCheck(location, board, originalChar, mario, flag, mariowin,ifcolorMode, steps, results);
		p.draw(originalChar, location, ifcolorMode); //print original char on board
	}
	
	char floor = board.GetCurrentChar(location.x, location.y + 1);//Check the char below the barrel to determine the floor type
	if (dropDirection == false) // Drop barrel down else drop barrel forward
	{
		location.y++;
		dropDirection = true;//Drop barrel forward
	}

	switch (floor)
	{
	case '>'://Floor mooving right
	{
		if (fallCount >= 8)// If the barrel has fallen more then 8 floors,then deactivate it
		{
			deactivate();
		}
		else
		{
			direction = true;
			fallCount = 0;
			++location.x;
		}
		break;
	}
	case '<':// Floor mooving left
	{
		if (fallCount >= 8)
		{
			deactivate();
		}
		else
		{
			direction = false;
			fallCount = 0;
			--location.x;
		}
		break;
	}
	case '=':// Continue previous direction 
	case 'Q':
	{
		if (fallCount >= 8)
		{
			deactivate();
		}
		else
		{
			fallCount = 0;
			++location.x;
		}
		break;
	}
	default:// If there is no floor (barrel is falling)
		++location.y;
		++fallCount;
		break;
	}
	if (flag)
	{
		GameWithKeys::setCharCheck(location, board, BARREL_CH, mario, flag, mariowin, ifcolorMode, steps, results); //Update barrel's new position on the game board.
		p.draw(BARREL_CH, location, ifcolorMode);//Draw the barrel at its new position on screen
	}
}

bool Barrel::marioCloseToExplosion(GameConfig& board, Mario& mario) //checks if mario is close to barrel's explosion
{
	Point marioPos = mario.findMarioLocation();
	if (isInExplosionArea(this->location, marioPos))
		return true;
	else
		return false;
}

bool Barrel::isInExplosionArea(Point& barrelPos, Point& marioPos) //checks if mario is in an explosion area
{
	int min_x = barrelPos.x - 2;
	int max_x = barrelPos.x + 2;
	int min_y = barrelPos.y - 2;
	int max_y = barrelPos.y + 2;

	if (marioPos.x >= min_x && marioPos.x <= max_x && marioPos.y >= min_y && marioPos.y <= max_y)
		return true;
	else
		return false;
}

void Barrel::barrelsMovement(vector<Barrel>& barrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results) //moves each barrel
{
	Point p(0, 0);
	if (board.getDonkeyKongPos() == p) //in case there isn't a donkey kong char
		return;

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
			barrels[i].moveBarrel(board, mario, flag, mariowin, ifcolorMode, steps, results);

			//Remove barrel from array if reached screen boundaries or became inactive
			if (barrels[i].getLocation().x >= MAX_X - 2 || barrels[i].getLocation().x <= MIN_X || !barrels[i].isBarrelActive())
			{
				barrels[i].clearFromScreen(board, mario, flag, mariowin, marioKilled, ifcolorMode, steps, results); //Print EXPLOSION
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
