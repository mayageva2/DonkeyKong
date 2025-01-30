#pragma once
#include <list>
#include <fstream>
#include <filesystem>
#include "gameActions.h"

class loadGame:public gameActions
{
	bool isSilent;
public:
	static void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	virtual void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps) override;  //starts game
	virtual void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts, bool& ifcolorMode, Results& results, Steps& steps) override;
	 void recorded_game(bool& _silent, Mario& mario, Results& results, Steps& steps);
};

