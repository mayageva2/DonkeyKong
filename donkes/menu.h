#ifndef _MENU_H
#define _MENU_H
#include "mario.h"
#include "gameActions.h"
#include "file.h"

class Menu
{
	Menu(const Menu&) = delete;
public:
	Menu() = default;
	static constexpr int MENU_X = 75; //menu size
	static constexpr int MENU_Y = 17; //menu size
	static constexpr int LegendX = 20;  //legend size
	static constexpr int LegendY = 3;   //legend size
	static const char legend[LegendY][LegendX+1]; //legend
	static const char* winLevel[MENU_Y]; //win level screen 
	static const char* pause[MENU_Y];    //pause game screen
	static const char* end_game[MENU_Y]; //end game screen 
	static const char* mainMenu[MENU_Y]; //main menu screen
	static const char* instructions[MENU_Y];  //instructions screen
	static const char* win[MENU_Y];           //win all levels screen
	static const char* choose3Screen[MENU_Y]; //choose a board out of 3 boards screen
	static const char* choose2Screen[MENU_Y]; //choose a board out of 2 boards screen
	static const char* choose1Screen[MENU_Y]; //choose a board out of 1 board screen
	static const char* colorModeScreen[MENU_Y]; //choose a color mode
	static void displayMenu(GameRenderer& renderer, Mario& mario, bool& save, Results& results, Steps& steps, GameActions& game);        // displays main menu
	static void displayEnd_Game(GameRenderer& renderer, Mario& mario);    //ends game
	static void loadScreens(GameRenderer& renderer, size_t i, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario, char colorMode, bool& save, Results& results, Steps& steps,GameActions& game); //load each screen by order
	static void loadChosenScreen(GameRenderer& renderer, char& screenKey, std::vector<std::string>& screens, GameConfig& board, bool& screenError, Mario& mario,char colorMode, bool& save, Results& results, Steps& steps, GameActions& game); //load specific screen
	static char printChooseScreen(GameRenderer& renderer, std::vector<std::string> screens,bool& ifcolorMode); //prints board according to user's choice
	static void addNames(GameRenderer& renderer, int size, char& counter, Point* namePoints, Point* counterPoints, std::vector<std::string>& screens, bool& ifcolorMode); //add names to choose screen
	static char printCModeScreen(GameRenderer& renderer); //print color mode 
	static void chooseColorScreen(GameRenderer& renderer, char& colorModeKey, bool& ifcolorM); //choose play mode: with or without colors
};
#endif