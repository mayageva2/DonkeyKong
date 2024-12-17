#ifndef _GAME_H
#define _GAME_H
#include "game.h"
#include "mario.h"
#include "barrel.h"

const int ENDJUMP = -1;

class Game
{
public:
	void startGame(Mario& mario, bool& flag);  //starts game
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag); //makes mario move according to key
	void barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario, bool& flag); //moves each barrel
	void deleteFromArray(Barrel** barrels, int index, int& numBarrels); //deletes barrels
	void deleteArray(Barrel** barrels, int& numBarrels); //deletes barrels array
	void pauseGame(GameConfig& board, Mario& mario); //pause the game
	void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag); // checks if theres a ladder or floor and then goes to set char on board
};

#endif