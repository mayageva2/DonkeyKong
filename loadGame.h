#pragma once
#include <list>
#include <fstream>
#include <filesystem>
#include "gameActions.h"


enum ResultValue { hitBomb, finished, noResult };

class loadGame:public gameActions
{
	bool isSilent;
	long randomSeed=0;
	char colorModeGame;
	size_t currentIteration = 0;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
	std::list<std::pair<size_t, char>> results; 
public:
	static loadGame loadSteps(const std::string& filename);
	static std::list<std::pair<size_t, char>> loadResults(const std::string& filename);
	static void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	void addStep(size_t iteration, char step) 
	{
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const 
	{
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep() 
	{
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}

	virtual void startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode) override;  //starts game
	virtual void marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost>& ghosts, bool& ifcolorMode) override; 
	 void recorded_game(bool& _silent, Mario& mario);
};

