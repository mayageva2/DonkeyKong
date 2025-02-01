#ifndef _NONCLIMBINGGHOST_H
#define _NONCLIMBINGGHOST_H
#include "ghost.h"

class Mario; //declaration
class Steps;
class Results;

class NonClimbingGhost : public Ghost
{
public:
	NonClimbingGhost(int x, int y, bool dir = true) : Ghost(x, y, NON_CLIMBING_GHOST_CH, dir) {	this->ch = NON_CLIMBING_GHOST_CH;}  //Constractor
	bool canClimbLadders() const override { return false; }
};
#endif
