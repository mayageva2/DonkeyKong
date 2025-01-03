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
// i like turtels
const Point upstart = { 7,4 };
static constexpr char BARREL_CH = 'O';

class Barrel
{
	int fallCount;
	Point location;
	bool direction;
	bool isActive;

public:
	bool dropDirection;// Indicates if the barrel is dropping: true = down, false = no drop
	static const int maxBarrels = 100;
	Barrel() :location(upstart), direction(true), dropDirection(true), isActive(false), fallCount(0) {};//Constractor

	void moveBarrel(GameConfig& board, Mario& mario, bool& flag);
	Point getLocation() const { return location; } //Get barrel location
	void clearFromScreen(GameConfig& board, Mario& mario, bool& flag); // Clears the barrel from the screen and updates the game board
	void deactivate() { isActive = false; } //Deactivate barrel
	void activate() { isActive = true; } //Activate Barrel
	bool isBarrelActive() const { return isActive; }
	bool marioCloseToExplosion(GameConfig& board, Mario& mario);
	bool isInExplosionArea(Point& barrelPos, Point& marioPos);
};

#endif
