#ifndef _BARREL_H
#define _BARREL_H
#include "gameConfig.h"
#include <Windows.h>
#include <iostream>
#include "general.h"
#include "point.h"
#include "mario.h"
#include "movingobject.h"
#include <string>
using namespace std;

static constexpr char BARREL_CH = 'O';

class Barrel : public movingObject
{
	int fallCount;
	bool isActive;

public:
	bool dropDirection;// Indicates if the barrel is dropping: true = down, false = no drop
	static const int maxBarrels = 100;
	Barrel(): movingObject(GameConfig::getDonkeyKongPos().x, GameConfig::getDonkeyKongPos().y, true), fallCount(0), isActive(false), dropDirection(true) {} //Constractor

	void moveBarrel(GameConfig& board, Mario& mario, bool& flag, bool& mariowin);
	void clearFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& mariowin); // Clears the barrel from the screen and updates the game board
	void deactivate() { isActive = false; } //Deactivate barrel
	void activate() { isActive = true; } //Activate Barrel
	bool isBarrelActive() const { return isActive; }
	bool marioCloseToExplosion(GameConfig& board, Mario& mario);
	bool isInExplosionArea(Point& barrelPos, Point& marioPos);
};

#endif
