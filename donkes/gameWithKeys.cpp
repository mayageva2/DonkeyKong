#include "gameWithKeys.h"
#include "mario.h"
#include "barrel.h"
#include "general.h"
#include "gameConfig.h"
#include "menu.h"
#include "ghost.h"
#include "climbingGhost.h"
#include "nonClimbingGhost.h"
#include "results.h"
#include "steps.h"

#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;

char GameWithKeys::getNextMove(Mario& mario,GameRenderer& renderer, int currentIteration, Steps& steps, bool& flag,GameConfig::eKeys lastKey)
{
	renderer.sleep(50);
	if (_kbhit()) 
	{
		char inputKey = _getch();
		if (GameConfig::isValidKey(inputKey)) 
		{
			steps.addStep(currentIteration, inputKey);
			return inputKey;
		}
	}
	return INVALID_KEY;
}






