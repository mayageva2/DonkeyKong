#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "gameConfig.h"
#include "mario.h"
#include "menu.h"
#include "barrel.h"
#include "steps.h"
using namespace std;

int main(int argc, char** argv)
{
	hideCursor();
	Mario mario;
	bool saveMode = Steps::checkSaveMode(argc, argv);
	Menu::displayMenu(mario, saveMode);
	
}

