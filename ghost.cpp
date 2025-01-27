#include "ghost.h"
#include "mario.h"
#include "game.h"

constexpr int LEFT = -1;
constexpr int RIGHT = 1;

void Ghost::checkMove(GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin,bool& ifcolorMode)  //move ghost according to conditions
{
    Point p(location.x, location.y);
    Game::setCharCheck(this->location, board, DELETE_CH, mario, flag, mariowin,ifcolorMode);
    char originalChar = board.GetCurrentChar(location.x, location.y);
    Game::setCharCheck(location, board, originalChar, mario, flag, mariowin,ifcolorMode);
    p.draw(originalChar, location,ifcolorMode);

    location.diff_x = direction ? RIGHT : LEFT;

    checkCollision(ghosts, board); //check if ghosts collide with one another

    if (canClimbLadders() && board.GetCurrentChar(location.x + location.diff_x, location.y) == LADDER_CH)
    {
        //call for climb func in climbing ghost
    }

    if (isGhostOnFloor(board) && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '=') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '<') && (board.GetCurrentChar(p.x + location.diff_x, p.y) != '>'))
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
    Game::setCharCheck(location, board, this->ch, mario, flag, mariowin,ifcolorMode);
    p.draw(this->ch, location,ifcolorMode);
}

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