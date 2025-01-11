#ifndef _GAME_H
#define _GAME_H
#include "game.h"
#include "mario.h"
#include "barrel.h"
#include "ghost.h"
#include <vector>
#include <iostream>
using namespace std;

const int ENDJUMP = -1;

class Game
{
	Game(const Game&) = delete;
public:
	Game() = default;
	void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin);  //starts game
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin); //makes mario move according to key
	void barrelsMovement(Barrel** barrels, int& numBarrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin); //moves each barrel
	void deleteFromArray(Barrel** barrels, int index, int& numBarrels); //deletes barrels
	void deleteArray(Barrel** barrels, int& numBarrels); //deletes barrels array
	static void pauseGame(GameConfig& board, Mario& mario); //pause the game
	static void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin); // checks if theres a ladder or floor and then goes to set char on board
	void createGhosts(vector<Ghost>& ghosts, GameConfig& board);
};

#endif