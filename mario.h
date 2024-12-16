#ifndef _MARIO_H
#define _MARIO_H
#include "point.h"
#include "general.h"
#include "gameConfig.h"

#include <conio.h>
#include<iostream>

const Point start = { 77, 23 };
const Point hearts = { 64,1 };
enum class MarioState { moving, jumping , standing, falling }; //chat GPT solution
const int FULL_LIFE = 3;

class Mario
{
	Point location;                  // mario's location
	int num_of_hearts = FULL_LIFE;   // num of lives
	int score = 0;                   // mario's score
	const char ch = '@';             // how mario appears on screen

public:
	MarioState state = MarioState::standing;     //initiallize state
	Mario() : location(start) {}                 //constructor
	Mario(const Mario& m) = delete;              //copy constructor block
	void draw(const Point& pos) const;           //draw mario on point   
	void move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter); //move mario accoring to key pressed
	bool checkMove(GameConfig& currBoard, int x, int y);   //check if point is a floor char
	bool isInBoard(GameConfig& currBoard, int x);          //check if point is in board limits
	bool isMarioOnLadder(GameConfig& currBoard);           //checks if mario is on a ladder
	void left(GameConfig& currBoard, int& moveCounter);    //moves mario left
	void right(GameConfig& currBoard, int& moveCounter);   //moves mario right
	void up(GameConfig& currBoard, int& moveCounter, bool& sideJump);       //moves mario up
	void jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump);   //moves mario down
	void falling(int& moveCounter, GameConfig& currBoard, bool& sideJump);  //makes mario fall down
	void climbUpAladder(int& moveCounter, GameConfig& currBoard);           //moves mario up a ladder
	void down(GameConfig& currBoard, int& moveCounter, bool& sideJump);     //moves mario down
	void stay(GameConfig& currBoard);  //stops mario's movement
	void jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump); //makes mario jump and then move to side according to key
	bool isMarioOnFloor(GameConfig& currBoard);   //checks if mario stands on a floor
	Point findMarioLocation();   //return mario's position
	int getNumOfHearts() { return num_of_hearts; }  //returns amount of lives left
	void printLessHearts(); //prints new amount of hearts
	void collide(GameConfig& currBoard); //makes mario explode and restarts game
	void didMarioLose(GameConfig& currBoard); //checks if mario lost all hearts
	void didMarioWin(GameConfig& currBoard);  //checks if mario reached pauline
	void printHearts();  //prints hearts on screen
	void resetMario();   //resets mario
};
#endif
