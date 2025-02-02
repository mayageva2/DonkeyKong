#ifndef _GAME_ACTIONS_H
#define _GAME_ACTIONS_H
#include "gameConfig.h"
#include "mario.h"
#include "gameRenderer.h"
#include "ghost.h"

static constexpr int ENDJUMP = -1;
static constexpr int BARREL_HIT = 0;
static constexpr int GHOST_HIT = 1;
static constexpr int FALL_HIT = 2;

class GameActions
{
protected:
	static size_t currentIteration;
	GameRenderer* renderer;
	static bool isSilent;
	static bool error_unmatch;
public:
	GameActions() : renderer(nullptr) {}  // Constructor 
	virtual ~GameActions() = default; // Virtual destructor
	static bool hitByBarrel;
	static bool hitByGhost;
	static bool fellToDeath;
	static bool MarioFinished;

	virtual char getNextMove(Mario& mario, GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag, GameConfig::eKeys lastKey) const = 0; //get Mario's next move
    void startGame(GameActions& game, GameRenderer& renderer, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode) ; //activates game
	void marioMovement(GameActions& game, GameRenderer& renderer, Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode);  //makes sure mario goes as he should 
	virtual void createGhosts(std::vector<Ghost*>& ghosts, GameConfig& board); //creates ghost
	void cleanUp(std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels, HANDLE hConsole, bool& fellToDeath, bool& hitByBarrel, bool& hitByGhost, bool& marioFinished); //clears ghost and barrels
	static void pauseGame(GameRenderer& renderer,GameConfig& board, Mario& mario, bool& ifcolorMode);  //pause the game
	void checkCollisions(GameActions& game, GameRenderer& renderer, size_t& counter, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps,bool& saveMode); //check for collisions of mario with object
	void setCharCheck(GameActions& game, GameRenderer& renderer, Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results, bool& saveMode); // checks if theres a ladder or floor and then goes to set char on board
	static bool isInLegend(Point& p, GameConfig& currBoard); //checks if mario is running over the legend
	void checkErrors(Mario& mario, Results& results); //Error handling
	void checkErrorsEndOfGame(Mario& mario, Results& results); //Error handling in end of game
};
#endif
