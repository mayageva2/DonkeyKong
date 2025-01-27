#ifndef _NONCLIMBINGGHOST_H
#define _NONCLIMBINGGHOST_H
#include "ghost.h"

class NonClimbingGhost : public Ghost
{
public:
	NonClimbingGhost(int x, int y, bool dir = true) : Ghost(x, y, NON_CLIMBING_GHOST_CH, dir) {	this->ch = NON_CLIMBING_GHOST_CH;}  //Constractor
	bool canClimbLadders() const override { return false; }
	void checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin, bool& ifcolorMode) override;
};
#endif
