#include "gameActions.h"
#include "nonClimbingGhost.h"
#include "climbingGhost.h"
#include "menu.h"

size_t GameActions::currentIteration;

void GameActions::startGame(GameActions& game, GameRenderer& renderer, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode)   //starts game
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	renderer.clearScreen();
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	board.resetBoard();
	board.PrintBoard(renderer, ifcolorMode);
	board.printHearts(renderer, mario, ifcolorMode);
	board.printScore(renderer, mario, ifcolorMode);
	int interval = 0;
	int moveCounter = 0;
	char key = (char)GameConfig::eKeys::STAY;
	bool sideJump = false;
	vector<Ghost*> ghosts;
	vector<Barrel> barrels;
	ghosts.reserve(board.getGhostsAmount());
	createGhosts(ghosts, board);
	this->currentIteration = 0;

	renderer.draw(MARIO_CH, mario.findMarioLocation(), ifcolorMode);
	if (!mario.isMarioOnFloor(board))  //incase mario is positioned in the air
		mario.state = MarioState::falling;
	else
		mario.state = MarioState::standing;

	flag = true;
	while (flag)
	{
		this->currentIteration++;
		for (int i = 0; i < ghosts.size(); i++)  //Move ghosts
			ghosts[i]->checkMove(game, renderer, board, mario, flag, ghosts, mariowin, ifcolorMode, steps, results,saveMode);

		Barrel::barrelsMovement(game, renderer, barrels, board, interval, mario, flag, mariowin, ifcolorMode, steps, results, saveMode); // Move Barrels

		if (moveCounter == 0) //Move Mario
		{
			char inputKey = game.getNextMove(renderer, currentIteration, steps, flag, lastKey);
			if (!flag) // no more steps for mario
			{
				break;
			}
			if (board.isValidKey(inputKey))
			{
				if ((GameConfig::eKeys)inputKey == GameConfig::eKeys::ESC)
				{
					if (ifcolorMode)
					{
						SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					}
					pauseGame(renderer, board, mario, ifcolorMode);
				}
				else
				{
					key = inputKey;
					if ((GameConfig::eKeys)key == lastKey && lastKey == GameConfig::eKeys::UP)
						lastKey = GameConfig::eKeys::STAY;
					marioMovement(game, renderer, mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode, results, steps,saveMode);
				}
			}
			else if (mario.state != MarioState::standing)
				marioMovement(game, renderer, mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode, results, steps, saveMode);
		}
		else
			marioMovement(game, renderer, mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode, results, steps, saveMode);

		checkCollisions(game, renderer, mario, board, flag, mariowin, ifcolorMode, results, steps,saveMode);
		if (mario.state == MarioState::falling)
		{
			if (flag)
				renderer.sleep(50);
		}

		++interval;
	}
	this->currentIteration = 0;
	gotoxy(0, MAX_Y + 2);
	cleanUp(ghosts, barrels, hConsole);
}

void GameActions::marioMovement(GameActions& game, GameRenderer& renderer,Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost*>& ghosts, bool& ifcolorMode, Results& results, Steps& steps, bool& saveMode)   //makes sure mario goes as he should 
{
	if (sideJump == true)
	{
			char tmp = game.getNextMove(renderer, currentIteration, steps, flag, lastKey);
			if (board.isValidKey(tmp))
			{
				if ((GameConfig::eKeys)tmp == GameConfig::eKeys::ESC)
					pauseGame(renderer, board, mario, ifcolorMode);
			}
		mario.jumpToSide(renderer,game,(GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, currentIteration,saveMode);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::KILL) || ((GameConfig::eKeys)key == GameConfig::eKeys::KILL2))
	{
		MarioState prevState = mario.state;
		mario.move(game,renderer,GameConfig::eKeys::KILL, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration,saveMode);

		if (prevState == MarioState::moving) // if mario was walking before kill then keep walking after
		{
			key = (char)lastKey;
		}
		else
		{
			key = (char)GameConfig::eKeys::STAY; //mario was staying before killing
		}
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::UP) || ((GameConfig::eKeys)key == GameConfig::eKeys::UP2))
	{
		renderer.sleep(50);
		char tmp = game.getNextMove(renderer, currentIteration, steps, flag, lastKey);
		if (board.isValidKey(tmp) && moveCounter != ENDJUMP)
		{
			if ((GameConfig::eKeys)tmp != GameConfig::eKeys::UP && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP2)
			{
				sideJump = true;
				lastKey = (GameConfig::eKeys)key;
				key = tmp;
				mario.jumpToSide(renderer,game,(GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode, results, steps, currentIteration,saveMode);
				if ((GameConfig::eKeys)key == GameConfig::eKeys::ESC)
				{
					key = (char)GameConfig::eKeys::UP;
					lastKey = GameConfig::eKeys::STAY;
				}
			}
			else
			{
				return;
			}
		}
		else if (moveCounter == ENDJUMP)  //ends jump
		{
			moveCounter = 0;
			key = (char)lastKey;
			mario.move(game, renderer, (GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration,saveMode);
		}
		else //mario is jumping
		{
			mario.move(game, renderer, (GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration, saveMode);
			if (mario.state == MarioState::standing)
				lastKey = GameConfig::eKeys::STAY;
		}
	}
	else if (mario.state != MarioState::jumping)
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling)
		{
			mario.move(game, renderer, (GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration, saveMode);
			lastKey = (GameConfig::eKeys)key;
		}
		else //incase mario is falling
			mario.move(game, renderer, GameConfig::eKeys::DOWN, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode, results, steps, currentIteration, saveMode);
	}

}

void GameActions::cleanUp(vector<Ghost*>& ghosts, vector<Barrel>& barrels, HANDLE hConsole) 
{
	ghosts.clear();
	ghosts.shrink_to_fit();
	barrels.clear();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void GameActions::pauseGame(GameRenderer& renderer,GameConfig& board, Mario& mario, bool& ifcolorMode)  //pause the game
{
	renderer.clearScreen();
	renderer.printScreen(Menu::pause);

	char inputKey2 = 0;
	while (true)
	{
		if (_kbhit())
		{
			inputKey2 = _getch();
			if ((GameConfig::eKeys)inputKey2 == GameConfig::eKeys::ESC)
			{
				break;
			}
		}
	}
	renderer.clearScreen();
	board.PrintBoard(renderer,ifcolorMode);
	board.printHearts(renderer,mario, ifcolorMode);
	board.printScore(renderer,mario, ifcolorMode);
	if (mario.hasHammer())
	{
		board.printHammer(renderer,ifcolorMode);
		renderer.draw(DELETE_CH, GameConfig::getHammerPos(), ifcolorMode);
	}
	renderer.draw(MARIO_CH,mario.findMarioLocation(), ifcolorMode);
	renderer.draw(DELETE_CH, GameConfig::getMarioPos(), ifcolorMode);
}

void GameActions::checkCollisions(GameActions& game,GameRenderer& renderer, Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode, Results& results, Steps& steps,bool& saveMode)
{
	if (mario.state == MarioState::standing && flag) 
	{
		Point p1 = mario.findMarioLocation();
		char currentChar = board.GetCurrentChar(p1.x, p1.y);
		if (currentChar == BARREL_CH || currentChar == NON_CLIMBING_GHOST_CH || currentChar == CLIMBING_GHOST_CH) {
			mario.collide(game,renderer,board, flag, mariowin, ifcolorMode, results, steps, saveMode);
		}
		renderer.sleep(100);
	}
}

void GameActions::createGhosts(vector<Ghost*>& ghosts, GameConfig& board) //this func creates insert all ghosts into a vector
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


bool GameActions::isInLegend(Point& p, GameConfig& currBoard) //checks if mario is running over the legend
{
	Point legend = currBoard.getLegendPos();
	int min_x = legend.x;
	int max_x = legend.x + Menu::LegendX - 1;
	int min_y = legend.y;
	int max_y = legend.y + Menu::LegendY - 1;

	if (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y)
		return true;
	else
		return false;
}

void GameActions::setCharCheck(GameActions& game, GameRenderer& renderer, Point& p, GameConfig& currBoard, char object, Mario& mario, bool& flag, bool& mariowin, bool& ifcolorMode, Steps& steps, Results& results,bool& saveMode) // checks if theres a ladder or floor and then goes to set char on board
{
	char ch = currBoard.GetCurrentChar(p.x, p.y);
	bool returnCh = isInLegend(p, currBoard);
	if (ch == LADDER_CH || ch == '<' || ch == '>' || ch == '=' || ch == 'Q' || ch == PAULINE_CH || ch == DONKEY_KONG_CH || returnCh)
	{
		currBoard.SetChar(p.x, p.y, object);
		Point p1 = mario.findMarioLocation();
		if (currBoard.GetCurrentChar(p1.x, p1.y) == BARREL_CH)
		{
			results.addResult(currentIteration, results.hitBarrel, mario.getScore());
			mario.collide(game, renderer, currBoard, flag, mariowin, ifcolorMode, results, steps,saveMode);
		}
		else if (currBoard.GetCurrentChar(p1.x, p1.y) == NON_CLIMBING_GHOST_CH || currBoard.GetCurrentChar(p1.x, p1.y) == CLIMBING_GHOST_CH)
		{
			results.addResult(currentIteration, results.hitGhost, mario.getScore());
			mario.collide(game, renderer, currBoard, flag, mariowin, ifcolorMode, results, steps, saveMode);
		}
		currBoard.SetChar(p.x, p.y, ch);
	}
	else
		currBoard.SetChar(p.x, p.y, object);
}

