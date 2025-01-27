#include "climbingGhost.h"

void ClimbingGhost::climbUp(bool& climbing, GameConfig& board)
{
	this->location.y--;
	if (isGhostOnFloor(board))
	{
		climbing = false;
	}
	
}