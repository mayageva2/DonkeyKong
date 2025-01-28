#include "climbingGhost.h"
#include "game.h"

void ClimbingGhost::checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results)
{
    Point p(location.x, location.y);
    Game::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin, ifcolorMode, steps, results);
    char originalChar = board.GetCurrentChar(location.x, location.y);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin, ifcolorMode, steps, results);
    p.draw(originalChar, location, ifcolorMode);

    location.diff_x = direction ? RIGHT : LEFT;

    checkCollision(ghosts, board); // Check if ghosts collide with one another

    // Handle climbing logic based on state
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
        // Normal ghost movement when not climbing
        if (isGhostReachingCliff(board) && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '=') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '<') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '>'))
        {
            if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == NON_CLIMBING_GHOST_CH || board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == CLIMBING_GHOST_CH) 
            {
                direction = !direction;
                location.diff_x = direction ? RIGHT : LEFT;
                if (board.GetCurrentChar(p.x + location.diff_x, p.y) == 'Q')
                    location.diff_x = 0;
            }
            else if (board.GetCurrentChar(p.x + location.diff_x, p.y) != 'Q') 
                randomDirection();
            else 
                direction = !direction;
        }
        else 
        {
            direction = !direction;
            location.diff_x = direction ? RIGHT : LEFT;
            if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == NON_CLIMBING_GHOST_CH || board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == CLIMBING_GHOST_CH) 
                location.diff_x = 0;
        }

        moveGhosts();
        climbingState = NONE;
    }

    Game::setCharCheck(location, board, this->ch, mario, flag, mariowin, ifcolorMode, steps, results);
    p.draw(this->ch, location, ifcolorMode);
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
