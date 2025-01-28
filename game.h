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
	static void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results);  //starts game
	static void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts,bool& ifcolorMode, Steps& steps, Results& results); //makes mario move according to key
	static void barrelsMovement(vector<Barrel>& barrels, GameConfig& board, int& interval, Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results); //moves each barrel
	static void pauseGame(GameConfig& board, Mario& mario,bool&ifcolorMode); //pause the game
	static void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results); // checks if theres a ladder or floor and then goes to set char on board
	static void createGhosts(vector<Ghost*>& ghosts, GameConfig& board); //creates a vector containing all ghosts data
	static bool isInLegend(Point& p, GameConfig& currBoard); //checks if mario runs over the Legend
};

#endif