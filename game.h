#pragma once
#include "game.h"
#include "mario.h"
#include "barrel.h"

class Game
{
public:
	void startGame(Mario& mario);
	void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump);
	void barrelsMovement(std::vector<Barrel>& barrels, GameConfig& board, int& interval);
	void pauseGame(GameConfig& board, Mario& mario);
};

