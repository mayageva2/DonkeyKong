#include "barrel.h"
#include "mario.h"
#include "game.h"
#include "gameConfig.h"

void Barrel::ExplosionNearBorder(Point& location)
{
	gotoxy(location.x, location.y);
	cout << "|";
	location.x = GameConfig::MAX_X-5;

}

void Barrel::clearFromScreen(GameConfig& board, Mario& mario)
{
	Game game;
	game.setCharCheck(location, board, deleteCh, mario); //resets barrel's previous location
	//cout << "\xF0\x9F\x92\xA5";  // // BETTER VERSION

	if (location.x == GameConfig::MAX_X -1)
	{
		ExplosionNearBorder(location);
	}
	gotoxy(location.x, location.y);
	if (marioCloseToExplosion(board, mario))
	{
		ExplosionNearBorder(location);
		mario.collide(board);
		return;
	}
	cout << EXPLOSION;
	Sleep(150);
	for (int i = 3; i >= 0; i--) // CLEANS 'BOOM' from screen
	{
		gotoxy(location.x + i, location.y);
		cout << deleteCh;
	}
	if (mario.findMarioLocation().x == location.x + 3 && mario.findMarioLocation().y == location.y)
		mario.draw(mario.findMarioLocation());
}

void Barrel::Print(int x, int y)
{
	gotoxy(location.x, location.y);
	cout << barrelCh;
}

void Barrel::PrintLadder()
{
	cout << ladderCh;
}

void Barrel::moveBarrel(GameConfig& board,Mario& mario)
{
	Game game;
	game.setCharCheck(this->location, board, deleteCh, mario); //resets barrel's previous location
	char originalChar = board.GetChar(location.x, location.y);
	game.setCharCheck(location, board, originalChar, mario);
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
	game.setCharCheck(location,board, barrelCh, mario);
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