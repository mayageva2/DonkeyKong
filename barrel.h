#ifndef _BARREL_H
#define _BARREL_H
#include "gameConfig.h"
#include "general.h"
#include "point.h"
#include "movingobject.h"
#include <Windows.h>
#include <iostream>
#include <string> 

using namespace std;

class Mario;
class Steps;
class Results;

class Barrel : public movingObject
{
	int fallCount; //counts the amount of floors barrel falls
	bool isActive; //checks if a barrel is active

public:
	bool dropDirection;      // Indicates if the barrel is dropping: true = down, false = no drop
	Barrel(): movingObject(GameConfig::getDonkeyKongPos().x, GameConfig::getDonkeyKongPos().y, true), fallCount(0), isActive(false), dropDirection(true) {} //Constractor
	Point getLocation() const { return location; } //Get barrel location
	void moveBarrel(GameConfig& board, Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results); //moves barrel
	void clearFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& mariowin, bool& marioKilled,bool& ifcolorMode, Steps& steps, Results& results); // Clears the barrel from the screen and updates the game board
	void deactivate() { isActive = false; } //Deactivate barrel
	void activate() { isActive = true; } //Activate Barrel
	bool isBarrelActive() const { return isActive; }  //checks if a barrel is active
	bool marioCloseToExplosion(GameConfig& board, Mario& mario); //checks if mario is in the barrel explosion area
	bool isInExplosionArea(Point& barrelPos, Point& marioPos);   //helper func to checks if mario is in the barrel explosion area
};

#endif
