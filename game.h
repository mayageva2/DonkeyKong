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
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost>& ghosts); //makes mario move according to key
	void barrelsMovement(vector<Barrel>& barrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin); //moves each barrel
	static void pauseGame(GameConfig& board, Mario& mario); //pause the game
	static void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin); // checks if theres a ladder or floor and then goes to set char on board
	void createGhosts(vector<Ghost>& ghosts, GameConfig& board); //creates a vector containing all ghosts data
	static bool isInLegend(Point& p, GameConfig& currBoard);  //checks if mario runs over the Legend
};

#endif