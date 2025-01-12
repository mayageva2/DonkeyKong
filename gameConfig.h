#ifndef _GAMECONFIG_H
#define _GAMECONFIG_H
#include <iostream>
#include <string>
#include <vector>
#include "point.h"
//class Mario; //Declaration

static constexpr char LADDER_CH = 'H'; //const for ladder
static constexpr char DELETE_CH = ' ';  //const to clear pos
static constexpr char HAMMER = 'p';//const for hammer 
static const std::string EXPLOSION = "BOOM"; //const for explosion print
const Point hammer = { 70,23 };//hammer point on board
static constexpr int MAX_X = 80;
static constexpr int MAX_Y = 25;

class Mario;

class GameConfig
{
	char originalBoard[MAX_Y][MAX_X + 1] = {};
	char currentBoard[MAX_Y][MAX_X + 1] = {};  //current board
	static Point marioPos;
	static Point donkeyPos;
	static Point hammerPos;
	static Point legendPos;
	std::vector<Point> GhostsPos;
	size_t currentGhostIndex = 0;
	std::vector<std::string> screenFiles;
	size_t currentScreenIndex = 0;
	int ghostCounter;
	int marioCounter;
	int donkeyCounter;
	int hammerCounter;
	int legendCounter;
	int PaulineCounter;
	static constexpr int MIN_Y = 1;
	static constexpr int MIN_X = 1;
public:
	GameConfig() : marioCounter(0), donkeyCounter(0), ghostCounter(0), hammerCounter(0), legendCounter(0), PaulineCounter(0) {}
	enum class eKeys { LEFT = 'a', LEFT2 = 'A', RIGHT = 'd', RIGHT2 = 'D', UP = 'w', UP2 = 'W', DOWN = 'x', DOWN2 = 'X', STAY = 's', STAY2 = 'S', ESC = 27, KILL = 'p', KILL2 = 'P' }; 
	void load(const std::string& filename, bool& error);
	void PrintBoard() const;
	void resetBoard();
	static Point getMarioPos() { return marioPos; }
	static Point getDonkeyKongPos() { return donkeyPos; }
	static Point getLegendPos() { return legendPos; }
	Point getGhostPos();
	int getGhostsAmount() { return ghostCounter; }
	void insertLegend();
	void printHearts(Mario& mario);
	void init();
	bool isDkongScreenFile(const std::string& filename);
	std::vector<std::string> getDkongScreens(const std::string& directoryPath);
	void printErrors();

	void printHammer()
	{
		SetChar(hammer.x, hammer.y, HAMMER);
		Point::draw(HAMMER, hammer);
	}

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




