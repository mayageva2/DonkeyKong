#pragma once
#include "gameConfig.h"
#include "mario.h"
#include "gameRenderer.h"
#include "ghost.h"

static constexpr int ENDJUMP = -1;

class GameActions
{
protected:
	static size_t currentIteration;
	GameRenderer* renderer;
	static bool isSilent;
public:
	virtual char getNextMove(Mario& mario,GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey) = 0;
    void startGame(GameActions& game, GameRenderer& renderer, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode) ;
	void marioMovement(GameActions& game, GameRenderer& renderer, Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode);  //makes sure mario goes as he should 
	virtual ~GameActions() = default;
	virtual void createGhosts(vector<Ghost*>& ghosts, GameConfig& board);
	void cleanUp(vector<Ghost*>& ghosts, vector<Barrel>& barrels, HANDLE hConsole, bool& fellToDeath, bool& hitByBarrel, bool& hitByGhost, bool& marioFinished);
	static void pauseGame(GameRenderer& renderer,GameConfig& board, Mario& mario, bool& ifcolorMode);  //pause the game
	void checkCollisions(GameActions& game, GameRenderer& renderer, size_t& counter, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps,bool& saveMode);
	void setCharCheck(GameActions& game, GameRenderer& renderer, Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results, bool& saveMode); // checks if theres a ladder or floor and then goes to set char on board
	static bool isInLegend(Point& p, GameConfig& currBoard); //checks if mario is running over the legend
	static bool hitByBarrel;
	static bool hitByGhost;
	static bool fellToDeath;
	static bool MarioFinished;
	void checkErrors(Mario& mario, Results& results, bool& flag);
	void checkErrorsEndOfGame(Mario& mario, Results& results, Steps& steps);
};

