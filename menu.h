#ifndef _MENU_H
#define _MENU_H
#include "mario.h"

class Menu
{
	Menu(const Menu&) = delete;
public:
	Menu() = default;
	static constexpr int MENU_X = 75; //menu size
	static constexpr int MENU_Y = 17; //menu size
	static constexpr int LegendX = 20;  //legend size
	static constexpr int LegendY = 3;   //legend size
	static const char legend[LegendY][LegendX+1];
	static const char* winLevel[MENU_Y];
	static const char* pause[MENU_Y];
	static const char* end_game[MENU_Y];
	static const char* mainMenu[MENU_Y];
	static const char* instructions[MENU_Y];
	static const char* win[MENU_Y];
	static const char* choose3Screen[MENU_Y];
	static const char* choose2Screen[MENU_Y];
	static const char* choose1Screen[MENU_Y];
	static const char* colorModeScreen[MENU_Y];
	static void printScreen(const char** print);  //prints screen
	static void displayMenu(Mario& mario);        // displays main menu
	static void displayEnd_Game(Mario& mario);    //ends game
	static void loadScreens(size_t i, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario, char colorMode); //load each screen by order
	static void loadChosenScreen(char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario,char colorMode); //load specific screen
	static char printChooseScreen(std::vector<std::string> screens,bool& ifcolorMode); //prints board according to user's choice
	static void addNames(int size, char& counter, Point* namePoints, Point* counterPoints, std::vector<std::string>& screens, bool& ifcolorMode); //add names to choose screen
	static char printCModeScreen();
	static void chooseColorScreen(char& colorModeKey, bool& ifcolorM);
};
#endif