#ifndef _GAMEWITH_KEYS_H
#define _GAMEWITH_KEYS_H
#include "mario.h"
#include "barrel.h"
#include "ghost.h"
#include "gameActions.h"
#include <vector>
#include <iostream>
using namespace std;

class GameWithKeys: public gameActions
{
	GameWithKeys(const GameWithKeys&) = delete;
public:
	GameWithKeys() = default;
	virtual void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin,bool& ifcolorMode) override;  //starts game
	virtual void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts, bool& ifcolorMode) override ; //makes mario move according to key
	static void pauseGame(GameConfig& board, Mario& mario,bool&ifcolorMode); //pause the game
	static void setCharCheck(Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results); // checks if theres a ladder or floor and then goes to set char on board
	static bool isInLegend(Point& p, GameConfig& currBoard); //checks if mario runs over the Legend
};

#endif