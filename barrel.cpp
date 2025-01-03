#include "barrel.h"
#include "mario.h"
#include "game.h"
#include "gameConfig.h"

void Barrel::clearFromScreen(GameConfig& board, Mario& mario, bool& flag)
{
	Game::setCharCheck(location, board, DELETE_CH, mario, flag); //resets barrel's previous location

	if (mario.findMarioLocation().x == this->location.x && mario.findMarioLocation().y == this->location.y)
		mario.collide(board, flag);
	else
	{
		if (location.x == 78)
		{
			location.x = 75;
		}
		gotoxy(location.x, location.y);
		cout << DELETE_CH;
		gotoxy(location.x, location.y);
		cout << EXPLOSION;
		Sleep(80);
		for (int i = 3; i >= 0; i--) // CLEANS 'BOOM' from screen
		{
			gotoxy(location.x + i, location.y);
			cout << DELETE_CH;
		}
		if (marioCloseToExplosion(board, mario))
			mario.collide(board, flag);
	}
}

void Barrel::moveBarrel(GameConfig& board,Mario& mario, bool& flag)
{
	Point p(location.x, location.y);
	Game::setCharCheck(this->location, board, DELETE_CH, mario, flag); //resets barrel's previous location
	char originalChar = board.GetChar(location.x, location.y); //Restore the original character at the barrel's current location
	Game::setCharCheck(location, board, originalChar, mario, flag);
	p.draw(originalChar, location); //print original char on board

	char floor = board.GetChar(location.x, location.y + 1);//Check the char below the barrel to determine the floor type

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
	case '-':
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
	Game::setCharCheck(location,board, BARREL_CH, mario, flag); //Update barrel's new position on the game board.
	p.draw(BARREL_CH, location);//Draw the barrel at its new position on screen
}

bool Barrel::marioCloseToExplosion(GameConfig& board, Mario& mario)
{
	Point marioPos = mario.findMarioLocation();
	if (isInExplosionArea(this->location, marioPos))
		return true;
	else
		return false;
}

bool Barrel::isInExplosionArea(Point& barrelPos, Point& marioPos)
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