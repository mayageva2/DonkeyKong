#include "barrel.h"
#include "mario.h"
#include "gameWithKeys.h"
#include "gameConfig.h"


void Barrel::clearFromScreen(GameActions& game, GameRenderer& renderer, size_t& counter, GameConfig& board, Mario& mario, bool& flag, bool& mariowin, bool& marioKilled,bool& ifcolorMode, Steps& steps, Results& results, bool& saveMode) //this function clears barrels from the screen
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	game.setCharCheck(game,renderer,location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode, steps, results,saveMode); //resets barrel's previous location
	int whoHit;

	if (mario.findMarioLocation().x == this->location.x && mario.findMarioLocation().y == this->location.y)
	{
		whoHit = BARREL_HIT;
		mario.hitObject(game, renderer, board, flag, mariowin, ifcolorMode, results, steps, counter, saveMode, whoHit);
	}
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
		
		renderer.draw(DELETE_CH, location, ifcolorMode);
			
		renderer.drawString(EXPLOSION, BARREL_CH, this->location, ifcolorMode);
		renderer.sleep(80);
		for (int i = 0; i < 4; i++) // CLEANS 'BOOM' from screen
		{
			char originalCh = board.GetCurrentChar(location.x + i, location.y);
			Point tmp = location;
			tmp.x += i;
			renderer.draw(originalCh, tmp, ifcolorMode);
		}
		
		if (marioCloseToExplosion(board, mario) && mario.state != MarioState::killing)
		{
			whoHit = BARREL_HIT;
			mario.hitObject(game, renderer, board, flag, mariowin, ifcolorMode, results, steps, counter, saveMode, whoHit);
		}
	}
	deactivate();
}

void Barrel::moveBarrel(GameActions& game,GameRenderer& renderer, GameConfig& board,Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results,bool& saveMode) //this func moves barrels
{
	Point p(location.x, location.y);

	game.setCharCheck(game,renderer,this->location, board, DELETE_CH, mario, flag, mariowin, ifcolorMode, steps, results,saveMode); //resets barrel's previous location
	char originalChar = board.GetCurrentChar(location.x, location.y); //Restore the original character at the barrel's current location
	game.setCharCheck(game,renderer,location, board, originalChar, mario, flag, mariowin, ifcolorMode, steps, results, saveMode);
	renderer.draw(originalChar, location, ifcolorMode); //print original char on board

	if (location == GameConfig::getDonkeyKongPos()) // if barrel crossed donkey kong
	{
		game.setCharCheck(game,renderer,location, board, DONKEY_KONG_CH, mario, flag, mariowin,ifcolorMode, steps, results, saveMode);
		renderer.draw(DONKEY_KONG_CH, location, ifcolorMode); //return donkey kong's char
	}
	else
	{
		game.setCharCheck(game,renderer,this->location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode, steps, results, saveMode); //resets barrel's previous location
		char originalChar = board.GetCurrentChar(location.x, location.y); //Restore the original character at the barrel's current location
		game.setCharCheck(game,renderer,location, board, originalChar, mario, flag, mariowin,ifcolorMode, steps, results, saveMode);
		renderer.draw(originalChar, location, ifcolorMode); //print original char on board
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
		game.setCharCheck(game,renderer,location, board, BARREL_CH, mario, flag, mariowin, ifcolorMode, steps, results, saveMode); //Update barrel's new position on the game board.
		renderer.draw(BARREL_CH, location, ifcolorMode);//Draw the barrel at its new position on screen
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

bool Barrel::isInExplosionArea(Point& barrelPos, Point& marioPos) const//checks if mario is in an explosion area
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

void Barrel::barrelsMovement(GameActions& game, GameRenderer& renderer, size_t& counter, std::vector<Barrel>& barrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results,bool& saveMode) //moves each barrel
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
			barrels[i].moveBarrel(game,renderer,board, mario, flag, mariowin, ifcolorMode, steps, results,saveMode);

			//Remove barrel from array if reached screen boundaries or became inactive
			if (barrels[i].getLocation().x >= MAX_X - 2 || barrels[i].getLocation().x <= MIN_X || !barrels[i].isBarrelActive())
			{
				barrels[i].clearFromScreen(game, renderer, counter, board, mario, flag, mariowin, marioKilled, ifcolorMode, steps, results, saveMode); //Print EXPLOSION
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
