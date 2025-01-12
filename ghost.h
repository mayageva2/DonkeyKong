#ifndef _GHOST_H
#define _GHOST_H
#include "point.h"
#include "mario.h"
#include "movingobject.h"
#include <vector>
#include <iostream>

static constexpr char GHOST_CH = 'x';

class Ghost : public movingObject 
{
public:
	Ghost(int x, int y, bool dir = true) : movingObject(x, y, dir) {} //Constractor
	void checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts, bool& mariowin);
	void checkCollision(std::vector<Ghost>& ghosts);
	void randomDirection();
	void moveGhosts();
};

#endif

