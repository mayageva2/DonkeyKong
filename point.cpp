#include "point.h"
#include "general.h"
#include <iostream>

void Point::draw(char ch, Point pos) //draws point on screen
{
	gotoxy(pos.x, pos.y);
	std::cout << ch;
}