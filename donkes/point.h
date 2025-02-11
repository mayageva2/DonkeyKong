#ifndef _POINT_H
#define _POINT_H
#include <iostream>
#include "Windows.h"


static constexpr char MARIO_CH = '@';        //const for mario
static constexpr char BARREL_CH = 'O';       //const for barrel
static constexpr char LADDER_CH = 'H';       //const for ladder
static constexpr char PAULINE_CH = '$';      //const for mario
static constexpr char NON_CLIMBING_GHOST_CH = 'x';        //const for a NON CLIMBING ghost
static constexpr char CLIMBING_GHOST_CH = 'X';        //const for CLIMBING ghost
static constexpr char DONKEY_KONG_CH = '&';  //const for donkey kong
static constexpr char DELETE_CH = ' ';       //const to clear pos
static constexpr char HAMMER = 'p';          //const for hammer 
static const std::string EXPLOSION = "BOOM"; //const for explosion print


class Point
{
public:
	int x, y;
	int diff_x, diff_y; // new point location
	Point(int _x, int _y) : x(_x), y(_y), diff_x(0), diff_y(0) {}; //constructor
	bool operator==(const Point& other) const { //operator ==
		return (x == other.x && y == other.y);
	}
};
#endif


