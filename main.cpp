#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "general.h"
#include "gameConfig.h"
#include "mario.h"
#include "menu.h"
#include "barrel.h"
using namespace std;

void main()
{
	hideCursor();
	Menu menu;
	Mario mario;
	menu.displayMenu(mario);
}
