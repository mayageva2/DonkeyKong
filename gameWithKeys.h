#ifndef _GAMEWITH_KEYS_H
#define _GAMEWITH_KEYS_H
#include "mario.h"
#include "barrel.h"
#include "ghost.h"
#include "gameActions.h"
#include <vector>
#include <iostream>

class GameWithKeys: public GameActions
{
	GameWithKeys(const GameWithKeys&) = delete; 
public:
	GameWithKeys() = default; //constructor
	virtual char getNextMove(Mario& mario, GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey) const override; //get Mario's next move
};
#endif