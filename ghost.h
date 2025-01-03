#ifndef _GHOST_H
#define _GHOST_H
#include "point.h"
#include "mario.h"
#include <vector>
#include <iostream>

static constexpr char GHOST_CH = 'x';

class Ghost
{
	Point location;
	bool direction; //true = right, false = left

public:
	Ghost(int x, int y, bool dir = true) : location(x, y), direction(dir) {} //Constractor
	void checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts);
	void checkCollision(std::vector<Ghost>& ghosts);
	void randomDirection();
	void moveGhosts();
};

#endif

