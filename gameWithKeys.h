#ifndef _GAMEWITH_KEYS_H
#define _GAMEWITH_KEYS_H
#include "mario.h"
#include "barrel.h"
#include "ghost.h"
#include "gameActions.h"
#include <vector>
#include <iostream>
using namespace std;

class GameWithKeys: public GameActions
{
	GameWithKeys(const GameWithKeys&) = delete;
public:
	GameWithKeys() = default;
	virtual char getNextMove(GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey) override;
};

#endif