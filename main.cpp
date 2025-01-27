#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "gameConfig.h"
#include "mario.h"
#include "menu.h"
#include "barrel.h"
#include "loadGame.h"
using namespace std;

              /// ARANGE SLEEPING MODE///
int main(int argc, char** argv) ///ARRANGE LOAD FROM FILES///
{
	hideCursor();
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	Mario mario;
	loadGame loadGame;
	if (isLoad)
	{
		loadGame.recorded_game(isSilent, mario);
	}
	else
	{
		Menu::displayMenu(mario);
	}
}
