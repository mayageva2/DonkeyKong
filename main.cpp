#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "gameConfig.h"
#include "mario.h"
#include "menu.h"
#include "barrel.h"
#include "loadGame.h"
#include "steps.h"
using namespace std;

int main(int argc, char** argv)
{
	hideCursor();
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	Mario mario;
	bool saveMode = Steps::checkSaveMode(argc, argv);
	loadGame loadGame;
	if (isLoad)
	{
		loadGame.recorded_game(isSilent, mario);
	}
	else
	{
		Menu::displayMenu(mario, saveMode);
	}
}

