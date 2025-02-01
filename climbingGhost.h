#ifndef _CLIMBINGGHOST_H
#define _CLIMBINGGHOST_H
#include "ghost.h"

class Mario; //declaration
class Steps;
class Results;

class ClimbingGhost: public Ghost
{
public:
	ClimbingGhost(int x, int y, bool dir = true) : Ghost(x, y, CLIMBING_GHOST_CH, dir) { this->ch = CLIMBING_GHOST_CH; } //Constractor
	enum ClimbingState {  //chat GPT solution
		NONE,      // Not climbing
		CLIMBING_UP,
		CLIMBING_DOWN,
		FINISHED_CLIMBING
	};
	ClimbingState climbingState = NONE;
	bool canClimbLadders() const override { return true; }
	void climbUp(GameConfig& board);
	void climbDown(GameConfig& board);
	void handleClimbing(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps) override;
};
#endif
