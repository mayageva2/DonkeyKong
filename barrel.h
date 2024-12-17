#ifndef _BARREL_H
#define _BARREL_H
#include "gameConfig.h"
#include <Windows.h>
#include <iostream>
#include "general.h"
#include "point.h"
#include "mario.h"
#include <string>
using namespace std;

const Point upstart = { 7,4 };
static constexpr char barrelCh = 'O';

class Barrel
{
	int fallCount;
	Point location;
	bool direction;
	bool isActive;

public:
	bool dropDirection;
	static const int maxBarrels = 100;
	//true = right ; false = left;
	Barrel() :location(upstart), direction(true), dropDirection(true), isActive(false), fallCount(0) {};

	void moveBarrel(GameConfig& board, Mario& mario, bool& flag);
	void Print(int x, int y);
	Point getLocation() const { return location; }
	void clearFromScreen(GameConfig& board, Mario& mario, bool& flag);
	void deactivate() { isActive = false; }
	void activate() { isActive = true; }
	bool isBarrelActive() const { return isActive; }
	bool marioCloseToExplosion(GameConfig& board, Mario& mario);
	bool isInExplosionArea(Point& barrelPos, Point& marioPos);
};

#endif
