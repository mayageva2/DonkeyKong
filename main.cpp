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
	//SetConsoleOutputCP(CP_UTF8);
	Menu menu;
	Mario mario;
	menu.displayMenu(mario);
	
}
