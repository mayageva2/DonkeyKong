#ifndef _CLIMBINGGHOST_H
#define _CLIMBINGGHOST_H
#include "ghost.h"

class ClimbingGhost: public Ghost
{
public:
	ClimbingGhost(int x, int y, bool dir = true) : Ghost(x, y, CLIMBING_GHOST_CH, dir) { this->ch = CLIMBING_GHOST_CH; } //Constractor
	bool canClimbLadders() const override { return true; }
	void climbUp(bool& climbing, GameConfig& board);
};
#endif
