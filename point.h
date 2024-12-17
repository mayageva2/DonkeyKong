#pragma once
#include "GameConfig.h"
#include <iostream>

class Point
{
public:
	int x, y;
	int diff_x, diff_y; // new point location
	Point(int _x, int _y) : x(_x), y(_y), diff_x(0), diff_y(0) {}; //constructor
	void draw(char ch, Point pos); //draws point on screen
};


