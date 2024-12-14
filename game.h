#ifndef _GAME_H
#define _GAME_H
#include "game.h"
#include "mario.h"
#include "barrel.h"

class Game
{
public:
	void startGame(Mario& mario);
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump);
	void barrelsMovement(Barrel** barrels,int& numBarrels, GameConfig& board, int& interval);
	void deleteFromArray(Barrel** barrels, int index, int& numBarrels);
	void deleteArray(Barrel** barrels, int& numBarrels);
};
#endif

