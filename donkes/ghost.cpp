#include "ghost.h"
#include "mario.h"
#include "gameWithKeys.h"


void Ghost::checkMove(GameActions& game, GameRenderer& renderer, GameConfig& board, Mario& mario, bool& flag, std::vector<Ghost*>& ghosts, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results,bool& saveMode)  //move ghost according to conditions
{
    Point p(location.x, location.y);
    game.setCharCheck(game,renderer,this->location, board, DELETE_CH, mario, flag, mariowin, ifcolorMode, steps, results,saveMode);
    char originalChar = board.GetCurrentChar(location.x, location.y);
    game.setCharCheck(game,renderer,location, board, originalChar, mario, flag, mariowin, ifcolorMode, steps, results, saveMode);
    renderer.draw(originalChar, location, ifcolorMode);
    if (saveMode && steps.getRandomSeed() == 0)
    {
        steps.setSeed();
    }
    location.diff_x = direction ? RIGHT : LEFT;

    checkCollision(ghosts, board); //check if ghosts collide with one another
    bool isClimbing = canClimbLadders();
    if (isClimbing)
    {
        handleClimbing(board, p, ghosts,steps);
    }
    else
    {
        handleMovement(board, p, ghosts,steps);
    }

    moveGhosts();
    game.setCharCheck(game,renderer,location, board, this->ch, mario, flag, mariowin, ifcolorMode, steps, results, saveMode);
    renderer.draw(this->ch, location, ifcolorMode);
}

void Ghost::handleMovement(GameConfig& board, Point& p, std::vector<Ghost*>& ghosts, Steps& steps)
{
    if (isGhostReachingCliff(board) && board.GetCurrentChar(p.x + location.diff_x, p.y) != '=' &&
        board.GetCurrentChar(p.x + location.diff_x, p.y) != '<' && board.GetCurrentChar(p.x + location.diff_x, p.y) != '>')
    {
        if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == NON_CLIMBING_GHOST_CH ||
            board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == CLIMBING_GHOST_CH)
        {
            direction = !direction;
            location.diff_x = direction ? RIGHT : LEFT;
            if (board.GetCurrentChar(p.x + location.diff_x, p.y) == 'Q')
                location.diff_x = 0;
        }
        else if (board.GetCurrentChar(p.x + location.diff_x, p.y) != 'Q')
        {
            randomDirection(steps.getRandomSeed());
        }
        else
        {
            direction = !direction;
        }
    }
    else
    {
        direction = !direction;
        location.diff_x = direction ? RIGHT : LEFT;
        if (board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == NON_CLIMBING_GHOST_CH ||
            board.GetCurrentChar(this->location.x + location.diff_x, this->location.y) == CLIMBING_GHOST_CH)
        {
            location.diff_x = 0;
        }
    }
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

void Ghost::randomDirection(long seed) //gives a random direction
{
    std::srand(seed);
    long randomNum=std::rand() % 100 + 1;
    if (randomNum > 95)
        direction = !direction;
}

void Ghost::clearGhostFromScreen(GameActions& game, GameRenderer& renderer, GameConfig& board, Mario& mario, bool& flag, bool& marioKilled, bool& mariowin,bool& ifcolorMode, Steps& steps, Results& results,bool& saveMode) //this func clears ghosts from screen
{
    char originalChar = board.GetOriginalChar(location.x, location.y);
    renderer.draw(originalChar, location,ifcolorMode);
    game.setCharCheck(game,renderer,location, board, originalChar, mario, flag, mariowin,ifcolorMode, steps, results, saveMode);
}

bool Ghost::isGhostOnFloor(GameConfig& board)
{
    if (board.GetCurrentChar(location.x, location.y + 1) == '=' || board.GetCurrentChar(location.x, location.y + 1) == '<' || board.GetCurrentChar(location.x, location.y + 1) == '>' || board.GetCurrentChar(location.x, location.y + 1) == 'Q')
        return true;
    else
        return false;
}

bool Ghost::isGhostReachingCliff(GameConfig& board)
{
    if (board.GetCurrentChar(location.x + location.diff_x, location.y + 1) == '=' || board.GetCurrentChar(location.x + location.diff_x, location.y + 1) == '<' || board.GetCurrentChar(location.x + location.diff_x, location.y + 1) == '>' || board.GetCurrentChar(location.x + location.diff_x, location.y + 1) == 'Q')
        return true;
    else
        return false;
}

