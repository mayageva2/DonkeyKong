#include "point.h"
#include "general.h"
#include <iostream>

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
	diff_x = 0;
	diff_y = 0;
}

void Point::draw(char ch, Point pos)
{
	gotoxy(pos.x, pos.y);
	std::cout << ch;
}

void Point::move(GameConfig::eKeys key)
{
	switch (key)  //moving with keyboard
	{
	case GameConfig::eKeys::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case GameConfig::eKeys::UP:
		diff_x = 0;
		diff_y = -1;
		break;

	}
	// UPDATING LOCATION
	x += diff_x;
	if (x > GameConfig::MAX_X-1) // if reach right border go back
		x = GameConfig::MAX_X - 1;
	else if (x < GameConfig::MIN_X) // if reach left boarder go 1 step right
		x = GameConfig::MIN_X;

	y += diff_y;
	if(y>GameConfig::MAX_Y-2) // if reach down border go up
		y= GameConfig::MAX_Y - 2;
	else if (y < GameConfig::MIN_Y) // if reach up border go down
		y = GameConfig::MIN_Y;
}