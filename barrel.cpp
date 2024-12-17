#include "barrel.h"
#include "mario.h"
#include "game.h"
#include "gameConfig.h"

void Barrel::clearFromScreen(GameConfig& board, Mario& mario, bool& flag)
{
	Game game;
	game.setCharCheck(location, board, DELETE_CH, mario, flag); //resets barrel's previous location

	if (location.x == GameConfig::MAX_X -1)
	{
		location.x == GameConfig::MAX_X - 5;
	}
	gotoxy(location.x, location.y);
	cout << DELETE_CH;
	gotoxy(location.x, location.y);
	cout << EXPLOSION;
	Sleep(150);
	for (int i = 3; i >= 0; i--) // CLEANS 'BOOM' from screen
	{
		gotoxy(location.x + i, location.y);
		cout << DELETE_CH;
	}
	if (mario.findMarioLocation().x == location.x + 3 && mario.findMarioLocation().y == location.y)
		mario.draw(mario.findMarioLocation());
	if (marioCloseToExplosion(board, mario))
		mario.collide(board, flag);
}

void Barrel::Print(int x, int y)
{
	gotoxy(location.x, location.y);
	cout << barrelCh;
}

void Barrel::moveBarrel(GameConfig& board,Mario& mario, bool& flag)
{
	Game game;
	game.setCharCheck(this->location, board, DELETE_CH, mario, flag); //resets barrel's previous location
	char originalChar = board.GetChar(location.x, location.y);
	game.setCharCheck(location, board, originalChar, mario, flag);
	gotoxy(location.x, location.y);
	cout << originalChar;

	char floor = board.GetChar(location.x, location.y + 1);

	if (dropDirection == false) // Drop barrel down else drop barrel forward
	{
		location.y++;
		dropDirection = true;
	}

	switch (floor)
	{
	case '>':
	{
		if (fallCount >= 8)
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
	case '<':
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
	case '=':
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
	default:
		++location.y;
		++fallCount;
		break;
	}
	game.setCharCheck(location,board, barrelCh, mario, flag);
	Print(location.x, location.y);
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