#include "loadGame.h"
#include "ghost.h"
#include "barrel.h"

std::list<std::pair<size_t, char>> loadGame::loadResults(const std::string& filename)
{
	std::ifstream results_file(filename);
	std::list<std::pair<size_t, char>> results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.push_back({ iteration, result });
	}
	return results;
}

loadGame loadGame::loadSteps(const std::string& filename) {
	loadGame steps;
	std::ifstream steps_file(filename);
	steps_file >> steps.randomSeed; //read randomSeed
	steps_file >> steps.colorModeGame; //read colorMode
	size_t size;
	steps_file >> size;// read number of steps
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

void loadGame::getAllBoardFileNames(std::vector<std::string>& vec_to_fill)
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") 
		{
			vec_to_fill.push_back(filenameStr);
		}
	}
}

void loadGame::marioMovement(Mario& mario, GameConfig& board, GameConfig::eKeys& lastKey, char& key, int& moveCounter, bool& sideJump, bool& flag, bool& mariowin, vector<Barrel>& barrels, vector<Ghost>& ghosts, bool& ifcolorMode)
{
	if (steps.empty()) //no more commands, end game
	{
		flag = false; 
		return;
	}

	if (sideJump == true) 
	{
		mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode);
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::KILL) || ((GameConfig::eKeys)key == GameConfig::eKeys::KILL2)) 
	{
		MarioState prevState = mario.state;
		mario.move(GameConfig::eKeys::KILL, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode);

		if (prevState == MarioState::moving) 
		{
			key = (char)lastKey;
		}
		else 
		{
			key = (char)GameConfig::eKeys::STAY;
		}
	}
	else if (((GameConfig::eKeys)key == GameConfig::eKeys::UP) || ((GameConfig::eKeys)key == GameConfig::eKeys::UP2))
	{
		if (isNextStepOnIteration(this->currentIteration + 1) && moveCounter != ENDJUMP)
		{
			char tmp = popStep();
			if ((GameConfig::eKeys)tmp != GameConfig::eKeys::UP && (GameConfig::eKeys)tmp != GameConfig::eKeys::UP2)
			{
				sideJump = true;
				lastKey = (GameConfig::eKeys)key;
				key = tmp;
				mario.jumpToSide((GameConfig::eKeys)key, board, moveCounter, sideJump, flag, mariowin, ifcolorMode);
			}
			else
			{
				return;
			}
		}
		else if (moveCounter == ENDJUMP) 
		{
			moveCounter = 0;
			key = (char)lastKey;
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode);
		}
		else 
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode);
			if (mario.state == MarioState::standing) 
			{
				lastKey = GameConfig::eKeys::STAY;
			}
		}
	}
	else if (mario.state != MarioState::jumping) 
	{
		if (mario.isMarioOnFloor(board) && mario.state != MarioState::falling) 
		{
			mario.move((GameConfig::eKeys)key, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode);
			lastKey = (GameConfig::eKeys)key;
		}
		else 
		{
			mario.move(GameConfig::eKeys::DOWN, board, moveCounter, flag, mariowin, ghosts, barrels, ifcolorMode);
		}
	}
}


void loadGame::recorded_game(bool& _silent, Mario& mario )
{
	std::vector<std::string> fileNames;
	getAllBoardFileNames(fileNames);
	bool screenError = false;
	bool flag = true;
	bool mariowin = false;
	

	for (const auto& filename : fileNames) //load files
	{
		GameConfig board;
		board.load(filename, screenError);
		mario.resetMarioPos();
		std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";
		bool colorMode = false;
	
		*this = loadSteps(stepsFilename); //load steps
		this->results = loadResults(resultsFilename); // load results
		if (this->colorModeGame == 'c' || this->colorModeGame == 'C')
		{
			colorMode = true;
		}
		
		this->startGame(mario, board, flag, mariowin, colorMode);//start recorded game
	}
}

void loadGame::startGame(Mario& mario, GameConfig& board, bool& flag, bool& mariowin, bool& ifcolorMode)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clrscr();
	vector<Ghost> ghosts;
	vector<Barrel> barrels;
	ghosts.reserve(board.getGhostsAmount());
	Ghost::createGhosts(ghosts, board);
	int interval = 0;
	int moveCounter = 0;
	
	GameConfig::eKeys lastKey = GameConfig::eKeys::STAY;
	char key = (char)lastKey;
	bool sideJump = false;
	board.resetBoard();

	board.PrintBoard(ifcolorMode);
	board.printHearts(mario, ifcolorMode);
	board.printScore(mario, ifcolorMode);
	mario.draw(mario.findMarioLocation(), ifcolorMode);

	if (!mario.isMarioOnFloor(board))  //incase mario is positioned in the air
		mario.state = MarioState::falling;
	else
		mario.state = MarioState::standing;

	flag = true;
	while (flag && !steps.empty())
	{
		for (int i = 0; i < ghosts.size(); i++)  //Move ghosts
			ghosts[i].checkMove(board, mario, flag, ghosts, mariowin, ifcolorMode);
		Barrel::barrelsMovement(barrels, board, interval, mario, flag, mariowin, ifcolorMode); // Move Barrels

		if (moveCounter == 0)
		{
			//move mario according to steps file in this iteration
			if (isNextStepOnIteration(this->currentIteration))
			{
				key = popStep();
				if ((GameConfig::eKeys)key == lastKey && lastKey == GameConfig::eKeys::UP)
					lastKey = GameConfig::eKeys::STAY;
				marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);
			}
			else if(mario.state != MarioState::standing)
			{
			   marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);
			}
		}
		else
			marioMovement(mario, board, lastKey, key, moveCounter, sideJump, flag, mariowin, barrels, ghosts, ifcolorMode);
		
		if (mario.state == MarioState::standing)
		{
			if (flag)
			{
				Point p1 = mario.findMarioLocation();
				if (board.GetCurrentChar(p1.x, p1.y) == BARREL_CH || board.GetCurrentChar(p1.x, p1.y) == GHOST_CH)
					mario.collide(board, flag, mariowin, ifcolorMode);
				Sleep(100);
			}
		}
		this->currentIteration++;
		interval++;
	}
	this->currentIteration = 0;
	gotoxy(0, MAX_Y + 2);
	ghosts.clear();  //Clear ghosts 
	ghosts.shrink_to_fit();
	barrels.clear(); //Clear barrels array
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//set default screen color
}