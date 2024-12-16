#ifndef _GAME_H
#define _GAME_H
#include "game.h"
#include "mario.h"
#include "barrel.h"

const int ENDJUMP = -1;

class Game
{
public:
	void startGame(Mario& mario);
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump);
	void barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario);
	void deleteFromArray(Barrel** barrels, int index, int& numBarrels);
	void deleteArray(Barrel** barrels, int& numBarrels);
	void pauseGame(GameConfig& board, Mario& mario);
};

#endif