#ifndef _MARIO_H
#define _MARIO_H
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "barrel.h"
#include "ghost.h"
#include "results.h"
#include "steps.h"

#include <conio.h>
#include<iostream>
#include<vector>


enum class MarioState { moving, jumping, standing, falling, killing }; //chat GPT solution
const int FULL_LIFE = 3;
const int ZERO = 0;

class Mario
{
	Point location;                  // mario's location
	int num_of_hearts = FULL_LIFE;   // num of lives
	int curr_score = ZERO;           // mario's current score
	int last_score = ZERO;           // mario's former score
	bool hammer = false;             //checks if mario has hammer

public:
	MarioState state = MarioState::standing;     //initiallize state
	Mario() : location(GameConfig::getMarioPos()) {}                 //constructor
	Mario(const Mario& m) = delete;              //copy constructor block
	void draw(const Point& pos,bool& ifcolorMode) const;           //draw mario on point   
	void move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, vector<Ghost*>& ghosts, vector<Barrel>& barrels,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter); //move mario accoring to key pressed
	bool checkMove(GameConfig& currBoard, int x, int y);   //check if point is a floor char
	bool isInBoard(GameConfig& currBoard, int x);          //check if point is in board limits
	bool isMarioOnLadder(GameConfig& currBoard);           //checks if mario is on a ladder
	void left(GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, size_t& counter);    //moves mario left
	void right(GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, size_t& counter);   //moves mario right
	void up(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter);       //moves mario up
	void jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter);   //moves mario down
	void falling(int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter);  //makes mario fall down
	void climbUpAladder(int& moveCounter, GameConfig& currBoard, bool& ifcolorMode);           //moves mario up a ladder
	void down(GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter);     //moves mario down
	void stay(GameConfig& currBoard, bool& ifcolorMode);  //stops mario's movement
	void killEnemy(GameConfig& currBoard, Mario& mario, vector<Ghost*>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps); //kill barrel or ghost with hammer
	void jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter); //makes mario jump and then move to side according to key
	bool isMarioOnFloor(GameConfig& currBoard);   //checks if mario stands on a floor
	Point findMarioLocation();   //return mario's position
	int getNumOfHearts() const { return num_of_hearts; }  //returns amount of lives left
	int getScore() const { return curr_score; }  //returns amount of lives left
	void collide(GameConfig& currBoard, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps); //makes mario explode and restarts game
	void didMarioLose(GameConfig& currBoard, bool& flag,  bool& ifcolorMode); //checks if mario lost all hearts
	void didMarioWin(GameConfig& currBoard, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, size_t& counter);  //checks if mario reached pauline
	void resetMario();   //resets mario
	void pickHammer(GameConfig& board, bool& ifcolorMode); //takes care of hammer when mario reaches it
	void deleteKilledEnemy(GameConfig& currBoard, Point killPos, vector<Ghost*>& ghosts, vector<Barrel>& barrels, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps); //deletesghosts andbarrels that were killed
	void setScore(int points) { curr_score += points; } //sets new score
	void setLastScore() { last_score = curr_score; } //sets new score
	void resetMarioPos();  //brings mario back to starting position

	bool hasHammer() const //check if mario has a hammer
	{
		return hammer;
	}

	void setHammer(bool hasHammer) //switch hammer to true
	{
		hammer = hasHammer;
	}

};
#endif
