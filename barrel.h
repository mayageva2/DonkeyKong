#ifndef _BARREL_H
#define _BARREL_H
#include "gameConfig.h"
#include <vector>
#include <Windows.h>
#include <iostream>
#include "general.h"
#include "point.h"
#include <string>
using namespace std;

const Point upstart = { 5,4 };
const Point downstart = { 3,6 };

class Barrel
{
	GameConfig* pBoard = nullptr;
	const char ladderCh = 'H';
	const char barrelCh = 'O';
	int fallCount;
	Point location;
	bool direction;
	bool isActive;

public:
	bool dropDirection;                                           //true = right ; false = left;
	Barrel(GameConfig& board) :location(upstart), pBoard(&board), direction(true),
		dropDirection(true), isActive(true), fallCount(0) {};

	Barrel& operator=(const Barrel& other) {
		if (this == &other) return *this;
		pBoard = other.pBoard;
		location = other.location;
		direction = other.direction;
		dropDirection = other.dropDirection;
		isActive = other.isActive;
		fallCount = other.fallCount;

		return *this;
	}

	void moveBarrel(GameConfig& board);
	void Print(int x, int y);
	void PrintLadder();
	Point getLocation() const { return location; }
	void clearFromScreen(GameConfig& board);
	bool isBarrelActive() const { return isActive; }
	void barrelNotActive() { isActive = false; }
};

#endif
