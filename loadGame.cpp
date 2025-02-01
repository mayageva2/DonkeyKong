#include "loadGame.h"
#include "silentRenderer.h"
#include "consoleRenderer.h"
#include "ghost.h"
#include "barrel.h"


char loadGame::getNextMove(GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey)
{
	if (!steps.isEmpty() && steps.isNextStepOnIteration(currentIteration)) 
	{
		return steps.popStep();
	}
	else if (steps.isEmpty())
	{
		flag = false;
	}
	return INVALID_KEY;
}


void loadGame::getAllBoardFileNames(std::vector<std::string>& vec_to_fill)
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") 
		{
			vec_to_fill.push_back(filenameStr);
		}
	}
}


void loadGame::load_game(GameActions& game, bool& _silent, Mario& mario, Results& results, Steps& steps,bool& saveMode)
{
	GameRenderer* renderer = _silent ? static_cast<GameRenderer*>(new SilentRenderer()) : static_cast<GameRenderer*>(new ConsoleRenderer());
	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);
	bool screenError = false;
	bool flag = true;
	bool mariowin = false;
	

	for (const auto& filename : fileNames) //load files
	{
		GameConfig board;
		game.currentIteration = 0;
		board.load(filename, screenError);
		mario.resetMario();
		std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";
		bool colorMode = false;
		steps.clear();// clear steps from previous game if left
		steps.loadSteps(stepsFilename); //load steps	
		results.loadResults(resultsFilename); // load results
		srand(steps.getRandomSeed()); 
		char ch = steps.getColorMode();
		if (ch == 'c' || ch == 'C')
		{
			colorMode = true;
		}
		
		this->startGame(game,*renderer,mario, board, flag, mariowin, colorMode, results, steps,saveMode);//start recorded game
	}
}

