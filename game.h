#ifndef _GAME_H
#define _GAME_H
#include "game.h"
#include "mario.h"
#include "barrel.h"

const int ENDJUMP = -1;

class Game
{
public:
	void startGame(Mario& mario,bool& flag);
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag);
	void barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario,bool& flag);
	void deleteFromArray(Barrel** barrels, int index, int& numBarrels);
	void deleteArray(Barrel** barrels, int& numBarrels);
	void pauseGame(GameConfig& board, Mario& mario);
	void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario,bool& flag);
};

#endif