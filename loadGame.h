#pragma once
#include <list>
#include <fstream>
#include <filesystem>
#include "gameActions.h"

class loadGame:public GameActions
{
	bool isSilent;
	
public:
	virtual char getNextMove(GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey) override;
	static void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	void load_game(GameActions& game, bool& _silent, Mario& mario, Results& results, Steps& steps, bool& saveMode);
	 
};

