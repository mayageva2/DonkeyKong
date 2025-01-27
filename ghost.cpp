#include "ghost.h"
#include "mario.h"
#include "game.h"

void Ghost::checkCollision(std::vector<Ghost*>& ghosts, GameConfig& board) //check if ghosts meet each other
{
    for (Ghost* otherGhost : ghosts)
    {
        if (this != otherGhost && otherGhost->location.x == this->location.x + location.diff_x && otherGhost->location.y == this->location.y)
        {
            // Check if swapping directions would lead to a wall
            int newDiffX = direction ? LEFT : 1;
            int otherNewDiffX = otherGhost->direction ? LEFT : 1;
            if (board.GetCurrentChar(location.x + newDiffX, location.y) != '=' && board.GetCurrentChar(location.x + newDiffX, location.y) != '<' && board.GetCurrentChar(location.x + newDiffX, location.y) != '>' && board.GetCurrentChar(location.x + newDiffX, location.y) != 'Q')
            {
                direction = !direction;
                location.diff_x = newDiffX;
            }
            else 
                location.diff_x = 0;

            if (board.GetCurrentChar(otherGhost->location.x + otherNewDiffX, otherGhost->location.y) != '=' && board.GetCurrentChar(otherGhost->location.x + otherNewDiffX, otherGhost->location.y) != '<' && board.GetCurrentChar(otherGhost->location.x + otherNewDiffX, otherGhost->location.y) != '>' && board.GetCurrentChar(otherGhost->location.x + otherNewDiffX, otherGhost->location.y) != 'Q')
            {
                otherGhost->direction = !otherGhost->direction;
                otherGhost->location.diff_x = otherNewDiffX;
            }
            else
                otherGhost->location.diff_x = 0;
        }
    }
}

void Ghost::moveGhosts() //moves ghost according to direction
{
	if(location.diff_x != 0)
		location.x += direction ? RIGHT : LEFT;
}

void Ghost::randomDirection() //gives a random direction
{
    int randomNum = (std::rand() % 100) + 1;
    if (randomNum > 95)
        direction = !direction;
}

void Ghost::clearGhostFromScreen(GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin,bool& ifcolorMode) //this func clears ghosts from screen
{
    char originalChar = board.GetOriginalChar(location.x, location.y);
    Point::draw(originalChar, location,ifcolorMode);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin,ifcolorMode);
}

bool Ghost::isGhostOnFloor(GameConfig& board)
{
    if (board.GetCurrentChar(location.x, location.y + 1) == '=' || board.GetCurrentChar(location.x, location.y + 1) == '<' || board.GetCurrentChar(location.x, location.y + 1) == '>' || board.GetCurrentChar(location.x, location.y + 1) == 'Q')
        return true;
    else
        return false;
}