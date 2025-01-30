#include "gameActions.h"
#include "nonClimbingGhost.h"
#include "climbingGhost.h"

size_t gameActions::currentIteration = 0;

void gameActions::createGhosts(vector<Ghost*>& ghosts, GameConfig& board) //this func creates insert all ghosts into a vector
{
	int amountOfGhosts = board.getGhostsAmount();
	for (int i = 0; i < amountOfGhosts; i++)
	{
		Point p1 = board.getGhostPos();
		char ch = board.getGhostType();

		if (ch == NON_CLIMBING_GHOST_CH)
			ghosts.push_back(new NonClimbingGhost(p1.x, p1.y));
		else
			ghosts.push_back(new ClimbingGhost(p1.x, p1.y));

	}
}