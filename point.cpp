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