#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H
#include "point.h"

class movingObject
{
protected:
	Point location; // position on board	
	bool direction; //true = right, false = left

public:
	movingObject (int x, int y, bool dir = true) : location(x, y), direction(dir) {} //Constractor
	virtual ~movingObject() = default; //destructor
	Point getLocation() const { return location; } //gets object's position
};
#endif
