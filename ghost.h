#ifndef _GHOST_H
#define _GHOST_H
#include "point.h"
#include "gameConfig.h"
#include "movingobject.h"

#include <vector>
#include <iostream>

class Mario;
static constexpr char GHOST_CH = 'x';

class Ghost : public movingObject 
{
public:
	Ghost(int x, int y, bool dir = true) : movingObject(x, y, dir) {} //Constractor
	void checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts, bool& mariowin);
	void checkCollision(std::vector<Ghost>& ghosts);
	void randomDirection();
	void moveGhosts();
	Point getLocation() const { return location; } //Get ghost location
	void clearGhostFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin);
};

#endif

