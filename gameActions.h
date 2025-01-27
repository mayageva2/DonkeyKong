#pragma once
#include "gameConfig.h"
#include "mario.h"

static constexpr int ENDJUMP = -1;

class gameActions
{
public:
    virtual void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode) = 0;
	virtual void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost>& ghosts, bool& ifcolorMode) = 0;	
	virtual ~gameActions() = default;
};

