#ifndef _GHOST_H
#define _GHOST_H
#include "point.h"
#include "gameConfig.h"
#include "movingobject.h"

#include <vector>
#include <iostream>

class Mario;

class Ghost : public movingObject 
{
public:
	Ghost(int x, int y, bool dir = true) : movingObject(x, y, dir) {} //Constractor
	void checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts, bool& mariowin,bool& ifcolorMode); //check ghost's move
	void checkCollision(std::vector<Ghost>& ghosts);  //check if a ghost is meeting another ghost
	void randomDirection();
	void moveGhosts();
	void clearGhostFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin, bool& ifcolorMode);
};

#endif

