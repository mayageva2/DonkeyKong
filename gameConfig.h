#ifndef _GAMECONFIG_H
#define _GAMECONFIG_H
#include <iostream>
#include <string>
#include <vector>
#include "point.h"

static constexpr int MAX_X = 80;  //screen size
static constexpr int MAX_Y = 25;  //screen size
static constexpr int MIN_X = 1;  //screen size
static constexpr int MIN_Y = 1;  //screen size


class Mario;

class GameConfig
{
	std::vector<Point> GhostsPos;         //a vector containing all of ghosts positions
	std::vector<std::string> screenFiles; //a vector containing all the screen files names
	size_t currentGhostIndex = 0;         //ghosts vector index
	size_t currentScreenIndex = 0;        //screen files vector index
	static Point marioPos;      //mario's position
	static Point donkeyPos;     //donkeyKong's position
	static Point hammerPos;     //hammer's position
	static Point legendPos;     //legend starting position (top left)
	int ghostCounter;      //amount of 'x' on screen given
	int marioCounter;      //amount of '@' on screen given
	int donkeyCounter;     //amount of '&' on screen given
	int hammerCounter;     //amount of 'p' on screen given
	int legendCounter;     //amount of 'L' on screen given
	int PaulineCounter;    //amount of '$' on screen given
	bool ghostPosError = false;  //checks if ghost isn't on floor
	bool legendError = false;    //checks if legen have enough space in screen
	bool oversizeScreen = false; //checks if screen given is larger than approved screen size
	char originalBoard[MAX_Y][MAX_X + 1] = {};  //original board
	char currentBoard[MAX_Y][MAX_X + 1] = {};   //current board
public:
	GameConfig() : marioCounter(0), donkeyCounter(0), ghostCounter(0), hammerCounter(0), legendCounter(0), PaulineCounter(0) {} //constructor
	enum class eKeys { LEFT = 'a', LEFT2 = 'A', RIGHT = 'd', RIGHT2 = 'D', UP = 'w', UP2 = 'W', DOWN = 'x', DOWN2 = 'X', STAY = 's', STAY2 = 'S', ESC = 27, KILL = 'p', KILL2 = 'P' }; //user's keys
	void initBoard(); //initialize board
    void load(const std::string& filename, bool& error); //load board
	void PrintBoard(bool& ifcolorMode) const; //prints board on screen
	void resetBoard();  //reset current board to original board
	static Point getMarioPos() { return marioPos; }  //returns mario's position
	static Point getDonkeyKongPos() { return donkeyPos; } //returns donkeyKong's position
	static Point getLegendPos() { return legendPos; } //returns legend's start position
	static Point getHammerPos() { return hammerPos; } //returns hammer's start position
	Point getGhostPos();  //returns all ghosts positions
	int getGhostsAmount() const { return ghostCounter; } //returns amount of ghosts
	bool insertLegend(); //inserts legend to board
	void init(); //initiallizes all counters
	void printHearts(Mario& mario, bool& ifcolorMode); //print amount of hearts
	bool isDkongScreenFile(const std::string& filename); //checks if files is a screen file
	std::vector<std::string> getDkongScreens(const std::string& directoryPath); //get screens from file
	void printErrors() ;  //prints errors in screen
	void printHammer(bool& ifcolorMode);  //prints V in legend when mario has a hammer
	void printScore(Mario& mario, bool& ifcolorMode) const; //prints score
	void addFrame(); //add Q frame to screen
	bool isGhostsOnFloor();  //checks if ghosts are in the air

	char GetCurrentChar(int x, int y) const// returns a char that is placed on given point on board
	{
		return currentBoard[y][x];
	}

	char GetOriginalChar(int x, int y)// returns a char that is placed on given point on board
	{
		return originalBoard[y][x];
	}

	void SetChar(int x, int y, char ch)// Prints a char that is placed on given point on board
	{
		if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		{
			currentBoard[y][x] = ch;
		}
	}

};

#endif




