#include "climbingGhost.h"
#include "gameWithKeys.h"

void ClimbingGhost::handleClimbing(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps)
{
    if (climbingState == NONE)
    {
        if (board.GetCurrentChar(location.x, location.y + 2) == LADDER_CH)
            climbingState = CLIMBING_DOWN;
        else if (board.GetCurrentChar(location.x, location.y) == LADDER_CH)
            climbingState = CLIMBING_UP;
    }

    if (climbingState == CLIMBING_UP)
    {
        climbUp(board);
    }
    else if (climbingState == CLIMBING_DOWN)
    {
        climbDown(board);
    }
    else
    {
        handleMovement(board, p, ghosts,steps);
        climbingState = NONE;
    }
}

void ClimbingGhost::climbUp(GameConfig& board) 
{
    this->location.y--;
    this->location.diff_x = 0;

    if (isGhostOnFloor(board))
        climbingState = FINISHED_CLIMBING;
}

void ClimbingGhost::climbDown(GameConfig& board)
{
    this->location.y++;
    this->location.diff_x = 0;

    if (isGhostOnFloor(board))
        climbingState = FINISHED_CLIMBING;
}
