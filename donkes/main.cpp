#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "gameConfig.h"
#include "mario.h"
#include "menu.h"
#include "barrel.h"
#include "loadGame.h"
#include "gameWithKeys.h"
#include "steps.h"
#include "consoleRenderer.h"
using namespace std;

int main(int argc, char** argv)
{
	hideCursor();
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	Mario mario;
	bool saveMode = Steps::checkSaveMode(argc, argv);
	GameActions* game;
	GameRenderer* renderer=new ConsoleRenderer();
	Results results;
	Steps steps;
	if (isLoad)
	{
		game = new loadGame();
		static_cast<loadGame*>(game)->load_game(*game,isSilent, mario, results, steps,saveMode);
	
	}
	else
	{
		game = new GameWithKeys();
		Menu::displayMenu(*renderer,mario, saveMode, results, steps, *game);
	}
	
}

