#ifndef _MARIO_H
#define _MARIO_H
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include <conio.h>
#include<iostream>

const Point start = { 77, 23 };
const Point hearts = { 64,1 };
enum class MarioState { moving, jumping, standing, falling }; //chat GPT solution

class Mario
{
	Point location;   // mario's location
	int num_of_hearts = 3;   // num of lives
	int score = 0;     // mario's score
	const char ch = '@';  // how mario appears on screen

public:
	MarioState state = MarioState::standing;  //initiallize state
	Mario() : location(start) {} //constructor
	Mario(const Mario& m) = delete;      //copy constructor block
	GameConfig* pBoard = nullptr;    //pointer to board
	void draw(const Point& pos) const;
	void move(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter);
	void setPboard(GameConfig& board) { pBoard = &board; }
	bool checkMove(GameConfig& currBoard, int x, int y);
	bool isInBoard(GameConfig& currBoard, int x);
	bool isMarioOnLadder(GameConfig& currBoard);
	void left(GameConfig& currBoard, int& moveCounter);
	void right(GameConfig& currBoard, int& moveCounter);
	void up(GameConfig& currBoard, int& moveCounter, bool& sideJump);
	void jumpUp(int& moveCounter, GameConfig& currBoard, bool& sideJump);
	void falling(int& moveCounter, GameConfig& currBoard, bool& sideJump);
	void climbUpAladder(int& moveCounter, GameConfig& currBoard);
	void down(GameConfig& currBoard, int& moveCounter, bool& sideJump);
	void stay(GameConfig& currBoard);
	void jumpToSide(GameConfig::eKeys key, GameConfig& currBoard, int& moveCounter, bool& sideJump);
	bool isMarioOnFloor(GameConfig& currBoard);
	Point findMarioLocation();
	int getNumOfHearts() { return num_of_hearts; }
	void printHearts(); 
};
#endif