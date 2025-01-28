#include <iostream>
#include <conio.h>
#include <windows.h> 
#include <filesystem>
#include <vector>

#include "menu.h"
#include "point.h"
#include "general.h"
#include "game.h"
#include "file.h"
#include "steps.h"
#include "results.h"

const Point startMenu(8, 5);
bool flag = true;
constexpr char START_GAME = '1';
constexpr char CHOOSE_SCREEN = '2';
constexpr char INSTRUCTIONS = '8';
constexpr char EXIT = '9';
constexpr size_t FIRST_SCREEN = 1;
constexpr size_t SECOND_SCREEN = 2;

const char* Menu::winLevel[Menu::MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	"|---------------------------------------------------------------------------|",//0
		"|    __   _____  _   _   ____   _    ____ ____  _____ ____                  |",//1
		"|    \\ \\ / / _ \\| | | | |  _ \\ / \\  / ___/ ___|| ____|  _ \\                 |",//2
		"|     \\ V / | | | | | | | |_) / _ \\ \\___ \\___ \\| _|  | | | |                |",//3
		"|      | || |_| | |_| | |  __/ ___ \\ ___) |__) | |___| |_| |                |",//4
		"|      |_| \\___/ \\___/  |_| /_/   \\_\\____/____/|_____|____/                 |",//5 
		"|                                                                           |",//6
		"|                   _____ _   _ _____   _     _______     _______ _     _   |",//7
		"|                  |_   _| | | | ____| | |   | ____\\ \\   / / ____| |   | |  |",//8
		"|                    | | | |_| |  _|   | |   |  _ | \\ \\ / /|  _| | |   | |  |",//9
		"|                    | | |  _  | |___  | |___| |___  \\ V / | |___| |___|_|  |",//10
		"|                    |_| |_| |_|_____| |_____|_____|  \\_/  |_____|_____(_)  |",//11
		"|                                                                           |",//12
		"|                                                                           |",//13
		"|                                                                           |",//14
		"|                                                                           |",//15
		"|---------------------------------------------------------------------------|",//16
};

const char* Menu::pause[Menu:: MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	  "|---------------------------------------------------------------------------|",//0
	  "|   _____          __  __ ______   _____       _    _  _____ ______ _____   |",//1
	  "|  / ____|   /\\   |  \\/  |  ____| |  __ \\ /\\  | |  | |/ ____| ____ |  __ \\  |",//2
	  "| | |  __   /  \\  | \\  / | |__    | |__) /  \\ | |  | | (___ | |__  | |  | | |",//3
	  "| | | |_ | / /\\ \\ | |\\/| |  __|   |  ___/ /\\ \\| |  | |\\___ \\| __|  | |  | | |",//4
	  "| | |__| |/ ____ \\| |  | | |____  | |  / ____ \\ |__| |____) | |____| |__| | |",//5
	  "|  \\_____/_/    \\_\\_|  |_|______| |_| /_/    \\_\\____/|_____/|______|_____/  |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|         To continue game press 'ESC'...                                   |",//10
	  "|                                                                           |",//11
	  "|                                                                           |",//12
	  "|                                                                           |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::end_game[Menu::MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	  "|---------------------------------------------------------------------------|",//0
	  "|        _____          __  __ ______    ______      ________ _____         |",//1 
	  "|       / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\        |",//2
	  "|      | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |       |",//3
	  "|      | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /        |",//4
	  "|      | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\        |",//5
	  "|       \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\       |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|                                                                           |",//10
	  "|                                                                           |",//11
	  "|                                                                           |",//12
	  "|                                                                           |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::mainMenu[Menu::MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	  "|---------------------------------------------------------------------------|",//0
	  "|        _____              _                _  __                          |",//1
	  "|       |  __ \\            | |              | |/ /                          |",//2
	  "|       | |  | | ___  _ __ | | _____ _   _  | ' / ___  _ __   __ _          |",//3
	  "|       | |  | |/ _ \\| '_ \\| |/ / _ \\ | | | |  < / _ \\| '_ \\ / _` |         |",//4
	  "|       | |__| | (_) | | | |   <  __/ |_| | | . \\ (_) | | | | (_| |         |",//5
	  "|       |_____/ \\___/|_| |_|_|\\_\\___|\\__, | |_|\\_\\___/|_| |_|\\__, |         |",//6
	  "|                                     __/ |                   __/ |         |",//7
	  "|                                    |___/                   |___/          |",//8
	  "|                                                                           |",//9
	  "|    ============      ==============      ===============      ======      |",//10
	  "|   | Start Game |    | Instructions |    | Choose Screen |    | EXIT |     |",//11
	  "|    ============      ==============      ===============      ======      |",//12
	  "|       Press 1            Press 8             Press 2          Press 9     |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|" //16
};

const char* Menu::instructions[Menu::MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	  "|---------------------------------------------------------------------------|",//0
	  "|                             Instructions                                  |",//1 
	  "|                            ==============                                 |",//2
	  "|                                                                           |",//3
	  "|Move Mario using these keys:                                               |",//4
	  "|LEFT = 'a'  RIGHT = 'd'  UP = 'w'  DOWN = 'x'  STAY = 's'                  |",//5
	  "|Collect a hammer (p), press 'p' to smash barrels and ghosts,               |",//6
	  "|and earn points by defeating enemies!                                      |",//7
	  "|In order to PAUSE the game press ESC                                       |",//8
	  "|                                                                           |",//9
	  "|Climb ladders, dodge or defeat enemies to reach Pauline ($), and           |",//10
	  "|win the game! But you must be careful, Falling 5 rows, hitting a barrel    |",//11
	  "|or a ghost will cost you a heart! lose all 3 hearts ,and the game will end!|",//12  
	  "|                                                                           |",//13
	  "|                             GOOD LUCK MARIO!                              |",//14
	  "|                                           Press any key to return to menu |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::win[Menu::MENU_Y] = {
	// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
	  "|---------------------------------------------------------------------------|",//0
	  "|           __     ______  _    _  __          ______  _   _   _            |",//1
	  "|           \\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | | | |           |",//2
	  "|            \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| | | |           |",//3
	  "|             \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` | | |           |",//4
	  "|              | | | |__| | |__| |    \\  /\\  / | |__| | |\\  | |_|           |",//5
	  "|              |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_| (_)           |",//6
	  "|                                                                           |",//7
	  "|       \\ / _          __ _     __  _      ___    __                        |",//8
	  "|        Y / \\| |     (_ |_|\\ /|_  | \\      | |_||_                         |",//9
	  "|        | \\_/|_|     __)| | V |__ |_/      | | ||__                        |",//10       
	  "|                                                                           |",//11
	  "|                                         _  _ ___    __ __ __ __   | |     | ",//12
	  "|                                        |_)|_) | |\\|/  |_ (_ (_    | |     |",//13
	  "|                                        |  | \\_|_| |\\__|____)__)   o o     |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::choose3Screen[Menu::MENU_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456
	  "|---------------------------------------------------------------------------|",//0
	  "|	   _                                                                |",//1
	  "|         | |                                                               |",//2
	  "|       __| |__   ___   ___  ___  ___   ___  ___ _ __ ___  ___ _ __         |",//3
	  "|     / __| '_ \\ / _ \\ / _ \\/ __|/ _ \\ / __|/ __| '__/ _ \\/ _ \\ '_ \\        |",//4
	  "|    | (__| | | | (_) | (_) \\__ \\  __/ \\__ \\ (__| | |  __/  __/ | | |       |",//5
	  "|     \\___|_| |_|\\___/ \\___/|___/\\___| |___/\\___|_|  \\___|\\___|_| |_|       |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|    =================        =================        =================    |",//10
	  "|   |                 |      |                 |      |                 |   |",//11
	  "|    =================        =================        =================    |",//12
	  "|         Press                    Press                    Press           |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::choose2Screen[Menu::MENU_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456
	  "|---------------------------------------------------------------------------|",//0
	  "|	   _                                                                |",//1
	  "|         | |                                                               |",//2
	  "|       __| |__   ___   ___  ___  ___   ___  ___ _ __ ___  ___ _ __         |",//3
	  "|     / __| '_ \\ / _ \\ / _ \\/ __|/ _ \\ / __|/ __| '__/ _ \\/ _ \\ '_ \\        |",//4
	  "|    | (__| | | | (_) | (_) \\__ \\  __/ \\__ \\ (__| | |  __/  __/ | | |       |",//5
	  "|     \\___|_| |_|\\___/ \\___/|___/\\___| |___/\\___|_|  \\___|\\___|_| |_|       |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|           =================                   =================           |",//10
	  "|          |                 |                 |                 |          |",//11
	  "|           =================                   =================           |",//12
	  "|                Press                               Press                  |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::choose1Screen[Menu::MENU_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456
	  "|---------------------------------------------------------------------------|",//0
	  "|	   _                                                                |",//1
	  "|         | |                                                               |",//2
	  "|       __| |__   ___   ___  ___  ___   ___  ___ _ __ ___  ___ _ __         |",//3
	  "|     / __| '_ \\ / _ \\ / _ \\/ __|/ _ \\ / __|/ __| '__/ _ \\/ _ \\ '_ \\        |",//4
	  "|    | (__| | | | (_) | (_) \\__ \\  __/ \\__ \\ (__| | |  __/  __/ | | |       |",//5
	  "|     \\___|_| |_|\\___/ \\___/|___/\\___| |___/\\___|_|  \\___|\\___|_| |_|       |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|                             =================                             |",//10
	  "|                            |                 |                            |",//11
	  "|                             =================                             |",//12
	  "|                                  Press                                    |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|",//16
};

const char* Menu::colorModeScreen[Menu::MENU_Y] = {
	// 01234567890123456789012345678901234567890123456789012345678901234567890123456
	  "|---------------------------------------------------------------------------|",//0
	  "|   _____ _    _  ____   ____   _____ ______   __  __  ____  _____  ______  |",//1
	  "|  / ____| |  | |/ __ \\ / __ \\ / ____|  ____| |  \\/  |/ __ \\|  __ \\|  ____| |",//2
	  "| | |    | |__| | |  | | |  | | (___ | |__    | \\  / | |  | | |  | | |__    |",//3
	  "| | |    |  __  | |  | | |  | |\\___ \\|  __|   | |\\/| | |  | | |  | |  __|   |",//4
	  "| | |____| |  | | |__| | |__| |____) | |____  | |  | | |__| | |__| | |____  |",//5
	  "|  \\_____|_|  |_|\\____/ \\____/|_____/|______| |_|  |_|\\____/|_____/|______| |",//6
	  "|                                                                           |",//7
	  "|                                                                           |",//8
	  "|                                                                           |",//9
	  "|           =================                   =================           |",//10
	  "|          |    Color Mode   |                 |   Regular Mode  |          |",//11
	  "|           =================                   =================           |",//12
	  "|               Press C/c                           Press R/r               |",//13
	  "|                                                                           |",//14
	  "|                                                                           |",//15
	  "|---------------------------------------------------------------------------|"//16
};

void Menu::printScreen(const char** print) //prints screen
{
	clrscr();
	Point p = startMenu;
	for (int i = 0; i < MENU_Y; i++)
	{
		gotoxy(p.x, p.y);
		std::cout << print[i];
		p.y++;
	}
}

void Menu::displayMenu(Mario& mario, bool& save) // displays main menu
{
	GameConfig board;
	bool exitMenu = false; //chatGPT solution
	bool flag = true;
	bool screenError = false;
	char screenKey = DELETE_CH;
	char colorModeKey= DELETE_CH;
	bool ifcolorM = false;
	std::string path = ".";
	std::vector<std::string> screens = board.getDkongScreens(path);
	long random_seed;

	while (!exitMenu)
	{
		clrscr();
		printScreen(mainMenu);
		board.init();
		char key = _getch();
		switch (key)
		{
		case START_GAME:
			if (screens.size() == 0)
			{
				clrscr();
				std::cout << "Error Message: no screen files found";
				Sleep(2000);
			}
			else
			{
				chooseColorScreen(colorModeKey, ifcolorM);
				loadScreens(0, screens, board, screenError, mario, colorModeKey, save);
			}
			break;
		case INSTRUCTIONS:
			printScreen(instructions);
			while (!_kbhit()) {}
			break;
		case CHOOSE_SCREEN:
			chooseColorScreen(colorModeKey, ifcolorM);
			screenKey = printChooseScreen(screens, ifcolorM);
			loadChosenScreen(screenKey, screens, board, screenError, mario, colorModeKey, save);
			break;
		case EXIT:
			exitMenu = true;
			break;
		}
	}
}

void Menu::chooseColorScreen(char& colorModeKey, bool& ifcolorM)
{
	colorModeKey = printCModeScreen();
	while (colorModeKey != 'c' && colorModeKey != 'C' && colorModeKey != 'R' && colorModeKey != 'r')
	{
		switch (colorModeKey)
		{
		case 'c':
		case 'C':
		{
			ifcolorM = true;
			break;
		}
		case 'r':
		case 'R':
		{
			ifcolorM = false;
			break;
		}
		default:
		{
			colorModeKey = _getch();
			break;
		}
		}
	}
}

char Menu::printCModeScreen() //prints screen in color mode
{
	clrscr();
	printScreen(colorModeScreen);
	char key = _getch();
	return key;
}

char Menu::printChooseScreen(std::vector<std::string> screens,bool& ifcolorMode) //prints chosen screen 
{
	size_t size = screens.size();
	if (size == 0)
	{
		clrscr();
		std::cout << "Error Message: no screen files found";
		Sleep(2000);
		return DELETE_CH;
	}
	int i = 0, j = 0;
	char counter = '1';
	while (size != 0)
	{
		switch (size)
		{
		case FIRST_SCREEN: {
			Point namePoints[1] = { Point(38, 16) };
			Point counterPoints[1] ={ Point(49, 18) }; //check place
			j = 0;
			printScreen(choose1Screen);
			addNames(1, counter, namePoints, counterPoints, screens,ifcolorMode);
			size--;
			break;
		}
		case SECOND_SCREEN: {
			Point namePoints[2] = { Point(20, 16), Point(56, 16) }; //check place
			Point counterPoints[2] = { Point(31, 18),  Point(67, 18) }; //check place
			j = 0;
			printScreen(choose2Screen);
			addNames(2, counter, namePoints, counterPoints, screens, ifcolorMode);
			size = size - 2;
			break;
		}
		default: {
			Point namePoints[3] = { Point(13, 16), Point(38, 16), Point(63, 16) };
			Point counterPoints[3] = { Point(24, 18), Point(49, 18), Point(74, 18) }; //check place
			j = 0;
			printScreen(choose3Screen);
			namePoints[i].draw(screens[i][j], namePoints[i], ifcolorMode);
			addNames(3, counter, namePoints, counterPoints, screens, ifcolorMode);
			size = size - 3;
			break;
		}
		}
		if (size != 0)
		{
			gotoxy(61, 20);
			std::cout << "press 0 to next screens";
		}
		char key = _getch();
		if (key != '0')
			return key;
	}
}

void Menu::addNames(int size, char& counter, Point* namePoints, Point* counterPoints, std::vector<std::string>& screens,bool& ifcolorMode) //add file names to choosing screen 
{
	int j = 0;

	for (int i = 0; i < size; i++)
	{
		while (screens[i][j] != '\0')
		{
			namePoints[i].draw(screens[i][j], namePoints[i], ifcolorMode);
			namePoints[i].x++;
			j++;
		}
		counterPoints[i].draw(counter, counterPoints[i], ifcolorMode);
		counter++;
		j = 0;
	}

	for (int i = 0; i < size; i++)
	{
		screens.erase(screens.begin());
	}
}


void Menu::loadScreens(size_t i, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario,char colorMode, bool& save) //load screens one by one
{
	bool mariowin = true;
	bool ifcolorMode = false;
	Steps steps;
	Results results;
	for (i; i < screens.size(); i++)
	{
		board.init();
		if (mariowin)
		{
			board.load(screens[i], screenError);
			std::string filename_prefix = screens[i].substr(0, screens[i].find_last_of('.'));
			std::string stepsFilename = filename_prefix + ".steps";
			std::string resultsFilename = filename_prefix + ".result";

			if (!screenError)
			{
				mariowin = false;
				mario.resetMarioPos();
				if (colorMode == 'c' || colorMode == 'C')
				{
					ifcolorMode = true;
				}
				Game::startGame(mario, board, flag, mariowin, ifcolorMode);
			}
			else 
			{
				board.printErrors();
				screenError = false;
			}

			if (save)
			{
				steps.saveSteps(stepsFilename);
				results.saveResults(resultsFilename);
			}
		}
	}
	mario.resetMario();
	if (mariowin && screens.size() != 0)
	{
		clrscr();
		printScreen(Menu::win);
		Sleep(2000);
	}
}

void Menu::loadChosenScreen(char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario,char colorMode, bool& save) //load chosen screen
{
	int i = screenKey - '0' -1;
	loadScreens(i, screens, board, screenError, mario,colorMode, save);
}

void Menu::displayEnd_Game(Mario& mario)  //ends game
{
	printScreen(end_game);
	Sleep(2500);
	clrscr();
}

const char Menu::legend[Menu::LegendY][Menu::LegendX + 1] = {
	// 012345678901234567890
	  " lives              ",//0
	  " score              ",//1
	  " hammer             "//2
};