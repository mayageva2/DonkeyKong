#ifndef _GHOST_H
#define _GHOST_H
#include "point.h"
#include "gameConfig.h"
#include "movingobject.h"
#include "gameRenderer.h"
#include <vector>
#include <iostream>

constexpr int LEFT = -1;
constexpr int RIGHT = 1;

class GameActions;
class Mario; //declaration
class Steps;
class Results;

class Ghost : public movingObject 
{
public:
	enum ClimbingState {  //chat GPT solution
		NONE,      // Not climbing
		CLIMBING_UP,
		CLIMBING_DOWN,
		FINISHED_CLIMBING
	};
	Ghost(int x, int y, char character, bool dir = true): movingObject(x, y, dir), ch(character) {} //Constractor
	virtual ~Ghost() = default;
	virtual bool canClimbLadders() const = 0;
	void checkMove(GameActions& game, GameRenderer& renderer, GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results, bool& saveMode); //check ghost's move
	virtual void handleClimbing(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps) {};
	virtual void handleMovement(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps);
	void checkCollision(std::vector<Ghost*>& ghosts, GameConfig& board);  //check if a ghost is meeting another ghost
	void randomDirection(long seed);//changing direction randomly
	void moveGhosts(); //moving ghosts according to direction
	void clearGhostFromScreen(GameActions& game, GameRenderer& renderer, GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results, bool& saveMode); //clear ghosts from screen
	bool isGhostOnFloor(GameConfig& board) const;
	bool isGhostReachingCliff(GameConfig& board) const;

protected:
	char ch;
	ClimbingState climbingState = NONE;
};

#endif

