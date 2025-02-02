#ifndef _CLIMBINGGHOST_H
#define _CLIMBINGGHOST_H
#include "ghost.h"

//Declarations//
class Mario; 
class Steps;
class Results;

class ClimbingGhost: public Ghost
{
public:
	ClimbingGhost(int x, int y, bool dir = true) : Ghost(x, y, CLIMBING_GHOST_CH, dir) { this->ch = CLIMBING_GHOST_CH; } //Constractor
	enum ClimbingState {  //chat GPT solution
		NONE,              // Not climbing state
		CLIMBING_UP,       // Climb up state  
		CLIMBING_DOWN,     // Climb down state 
		FINISHED_CLIMBING  // End of climb state 
	};
	ClimbingState climbingState = NONE; //data member state of ghost climb
	bool canClimbLadders() const override { return true; } //check if ghost is a climbing ghost
	void climbUp(GameConfig& board); //makes ghost climb up
	void climbDown(GameConfig& board); //makes ghost climb down
	void handleClimbing(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps) override; //handles climbing conditions
};
#endif
