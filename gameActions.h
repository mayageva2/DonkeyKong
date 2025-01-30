#pragma once
#include "gameConfig.h"
#include "mario.h"

static constexpr int ENDJUMP = -1;

class gameActions
{
protected:
	static size_t currentIteration;
public:
    virtual void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps) = 0;
	virtual void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts, bool& ifcolorMode, Results& results, Steps& steps) = 0;
	virtual ~gameActions() = default;
	virtual void createGhosts(vector<Ghost*>& ghosts, GameConfig& board);
};

