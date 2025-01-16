#include "ghost.h"
#include "mario.h"
#include "game.h"

void Ghost::checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost>& ghosts, bool& mariowin,bool& ifcolorMode)
{
    Point p(location.x, location.y);
    Game::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode);
    char originalChar = board.GetCurrentChar(location.x, location.y);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin,ifcolorMode);
    p.draw(originalChar, location,ifcolorMode);

    location.diff_x = direction ? 1 : -1;

    checkCollision(ghosts, board);

    if (board.GetCurrentChar(p.x + location.diff_x, p.y + 1) == '=' ||( p.x + location.diff_x, p.y + 1) == '<' || board.GetCurrentChar(p.x + location.diff_x, p.y + 1) == '>' || board.GetCurrentChar(p.x + location.diff_x, p.y + 1) == 'Q' && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '=') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '<') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '>'))
    {
        if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == GHOST_CH)
        {
            direction = !direction;
            location.diff_x = direction ? 1 : -1;
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
        location.diff_x = direction ? 1 : -1;
        if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == GHOST_CH)
            location.diff_x = 0;
    }

    moveGhosts();
    Game::setCharCheck(location, board, GHOST_CH, mario, flag, mariowin,ifcolorMode);
    p.draw(GHOST_CH, location,ifcolorMode);
}

void Ghost::checkCollision(std::vector<Ghost>& ghosts, GameConfig& board)
{
    for (Ghost& otherGhost : ghosts)
    {
        if (this != &otherGhost && otherGhost.location.x == this->location.x + location.diff_x && otherGhost.location.y == this->location.y)
        {
            // Check if swapping directions would lead to a wall
            int newDiffX = direction ? -1 : 1;
            int otherNewDiffX = otherGhost.direction ? -1 : 1;
            if (board.GetCurrentChar(location.x + newDiffX, location.y) != '=' && board.GetCurrentChar(location.x + newDiffX, location.y) != '<' && board.GetCurrentChar(location.x + newDiffX, location.y) != '>' && board.GetCurrentChar(location.x + newDiffX, location.y) != 'Q')
            {
                direction = !direction;
                location.diff_x = newDiffX;
            }
            else 
                location.diff_x = 0;

            if (board.GetCurrentChar(otherGhost.location.x + otherNewDiffX, otherGhost.location.y) != '=' && board.GetCurrentChar(otherGhost.location.x + otherNewDiffX, otherGhost.location.y) != '<' && board.GetCurrentChar(otherGhost.location.x + otherNewDiffX, otherGhost.location.y) != '>' && board.GetCurrentChar(otherGhost.location.x + otherNewDiffX, otherGhost.location.y) != 'Q')
            {
                otherGhost.direction = !otherGhost.direction;
                otherGhost.location.diff_x = otherNewDiffX;
            }
            else
                otherGhost.location.diff_x = 0;
        }
    }
}

void Ghost::moveGhosts()
{
	if(location.diff_x != 0)
		location.x += direction ? 1 : -1;
}

void Ghost::randomDirection()
{
    int randomNum = (std::rand() % 100) + 1;
    if (randomNum > 95)
        direction = !direction;
}

void Ghost::clearGhostFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin,bool& ifcolorMode)
{
    char originalChar = board.GetOriginalChar(location.x, location.y);
    Point::draw(originalChar, location,ifcolorMode);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin,ifcolorMode);
}
