#include "nonClimbingGhost.h"
#include "game.h"

void NonClimbingGhost::checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin, bool& ifcolorMode)  //move ghost according to conditions
{
    Point p(location.x, location.y);
    Game::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin, ifcolorMode);
    char originalChar = board.GetCurrentChar(location.x, location.y);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin, ifcolorMode);
    p.draw(originalChar, location, ifcolorMode);

    location.diff_x = direction ? RIGHT : LEFT;

    checkCollision(ghosts, board); //check if ghosts collide with one another

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
        {
            randomDirection();
        }
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
    Game::setCharCheck(location, board, this->ch, mario, flag, mariowin, ifcolorMode);
    p.draw(this->ch, location, ifcolorMode);
}