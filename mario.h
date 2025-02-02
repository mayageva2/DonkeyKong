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
	Point location;                       // mario's location
	int num_of_hearts = FULL_LIFE;        // num of lives
	int curr_score = ZERO;                // mario's current score
	int last_score_before_death = ZERO;   // mario's score before death
	int last_score = ZERO;                // mario's former score
	bool hammer = false;                  //checks if mario has hammer

public:
	MarioState state = MarioState::standing;     //initiallize state
	Mario() : location(GameConfig::getMarioPos()) {}                 //constructor
	Mario(const Mario& m) = delete;              //copy constructor block
	void move(GameActions& game, GameRenderer& renderer, GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode); //move mario accoring to key pressed
	bool checkMove(GameConfig& currBoard, int x, int y);   //check if point is a floor char
	bool isInBoard(GameConfig& currBoard, int x);          //check if point is in board limits
	bool isMarioOnLadder(GameConfig& currBoard);           //checks if mario is on a ladder
	void left(GameRenderer& renderer, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode);    //moves mario left
	void right(GameRenderer& renderer, GameConfig& currBoard, int& moveCounter, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode);   //moves mario right
	void up(GameRenderer& renderer, GameActions& game, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode);       //moves mario up
	void jumpUp(GameRenderer& renderer, GameActions& game, int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode);   //moves mario down
	void falling(GameRenderer& renderer, GameActions& game, int& moveCounter, GameConfig& currBoard, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode);  //makes mario fall down
	void climbUpAladder(GameRenderer& renderer, int& moveCounter, GameConfig& currBoard, bool& ifcolorMode);           //moves mario up a ladder
	void down(GameRenderer& renderer, GameActions& game, GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode);     //moves mario down
	void stay(GameRenderer& renderer, GameConfig& currBoard, bool& ifcolorMode);  //stops mario's movement
	void killEnemy(GameRenderer& renderer, GameActions& game, size_t& counter, GameConfig& currBoard, Mario& mario, std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode); //kill barrel or ghost with hammer
	void jumpToSide(GameRenderer& renderer, GameActions& game, GameConfig::eKeys key,GameConfig& currBoard, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode); //makes mario jump and then move to side according to key
	bool isMarioOnFloor(GameConfig& currBoard);   //checks if mario stands on a floor
	Point findMarioLocation() const;   //return mario's position
	int getNumOfHearts() const { return num_of_hearts; }  //returns amount of lives left
	int getLastScoreBeforeDeath() const { return last_score_before_death; }
	int getScore() const { return curr_score; }  //returns amount of lives left
	void collide(GameActions& game, GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode); //makes mario explode and restarts game
	void didMarioLose(GameRenderer& renderer, GameConfig& currBoard, bool& flag,  bool& ifcolorMode); //checks if mario lost all hearts
	void didMarioWin(GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, size_t& counter, bool& saveMode);  //checks if mario reached pauline
	void resetMario();   //resets mario
	void pickHammer(GameRenderer& renderer,GameConfig& board, bool& ifcolorMode); //takes care of hammer when mario reaches it
	void deleteKilledEnemy(GameActions& game, GameRenderer& renderer, size_t& counter, GameConfig& currBoard, Point killPos, std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels, bool& flag, bool& mariowin,bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode); //deletesghosts andbarrels that were killed
	void setScore(int points) { curr_score += points; } //sets new score
	void setLastScore() { last_score = curr_score; } //sets new score
	void resetMarioPos();  //brings mario back to starting position
	bool isAlive() const { return num_of_hearts > 0; }  //checks if mario has hearts
	void hitObject(GameActions& game, GameRenderer& renderer, GameConfig& currBoard, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, size_t& counter, bool& saveMode, int& whoHit); //handles incase of collision

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
