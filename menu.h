#ifndef _MENU_H
#define _MENU_H
#include "mario.h"

class Menu
{
	Menu(const Menu&) = delete;
public:
	Menu() = default;
	static constexpr int MENU_X = 75;
	static constexpr int MENU_Y = 17;
	static constexpr int LegendX = 20;
	static constexpr int LegendY = 3;
	static const char legend[LegendY][LegendX+1];
	const char* mainMenu[MENU_Y] = {
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

	const char* instructions[MENU_Y] = {
		// 012345678901a2345678901234567890123456789012345678901234567890123456789012345
		  "|---------------------------------------------------------------------------|",//0
		  "|                             Instructions                                  |",//1 
		  "|                            ==============                                 |",//2
		  "| Climb the platforms, dodge barrels, and rescue the princess!              |",//3
		  "|                                                                           |",//4
		  "| Move Mario using these keys:                                              |",//5
		  "| LEFT = 'a'  RIGHT = 'd'  UP = 'w'  DOWN = 'x'  STAY = 's'                 |",//6
		  "| In order to PAUSE the game press ESC                                      |",//7
		  "|                                                                           |",//8
		  "| Climb ladders and dodge barrels in order to reach Pauline($), and         |",//9
		  "| win the game!                                                             |",//10
		  "|                                                                           |",//11
		  "| Be Careful! falling 5 rows or hitting a barrel will cost you a heart,     |",//12
		  "| lose all 3 hearts ,and the game will end!                                 |",//13
		  "|                                                           GOOD LUCK MARIO!|",//14
		  "|                     Press any key to return to menu                       |",//15
		  "|---------------------------------------------------------------------------|",//16
	};

	const char* end_game[MENU_Y] = {
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

	const char* win[MENU_Y] = {
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

	const char* pause[MENU_Y] = {
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

	const char* choose3Screen[MENU_Y] = {
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

	const char* choose2Screen[MENU_Y] = {
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

	const char* choose1Screen[MENU_Y] = {
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
	const char* colorModeScreen[MENU_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456
		  "|---------------------------------------------------------------------------|",//0
		  "|	                                                                       |",//1
		  "|                                                                           |",//2
		  "|                  CHOOSE MODE //MAYA HELP WITH DESIGN                      |",//3
		  "|                                                                           |",//4
		  "|                                                                           |",//5
		  "|                                                                           |",//6
		  "|                                                                           |",//7
		  "|                                                                           |",//8
		  "|                                                                           |",//9
		  "|           =================                   =================           |",//10
		  "|          |    Color Mode   |                 |   Regular Mode  |          |",//11
		  "|           =================                   =================           |",//12
		  "|               Press C/c                           Press R/r               |",//13
		  "|                                                                           |",//14
		  "|                                                                           |",//15
		  "|---------------------------------------------------------------------------|",//16
	};

	void printScreen(const char** print);  //prints screen
	void displayMenu(Mario& mario);        // displays main menu
	void displayEnd_Game(Mario& mario);    //ends game
	void loadScreens(size_t i, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario, char colorMode);
	void loadChosenScreen(char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario,char colorMode);
	char printChooseScreen(std::vector<std::string> screens,bool& ifcolorMode);
	void addNames(int size, char& counter, Point* namePoints, Point* counterPoints, std::vector<std::string>& screens, bool& ifcolorMode);
	char printCModeScreen();
};
#endif