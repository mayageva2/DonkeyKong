#ifndef _CONSOLE_RENDER_H
#define _CONSOLE_RENDER_H
#include "gameRenderer.h"
#include "general.h"

const Point startMenu(8, 5);
static constexpr int START_MENU_X = 75; //menu size
static constexpr int START_MENU_Y = 17; //menu size

class ConsoleRenderer : public GameRenderer 
{
public:
   virtual void draw(char ch, Point pos,  bool& iscolorMode) const override;  //draws char
   virtual void drawNumber(int num, Point pos, bool& ifcolorMode) const override;  //draws number
   virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const override; //draws string
   virtual void clearScreen() override { clrscr(); } //clears screen
   virtual void sleep(int ms) override { Sleep(ms-20);} //make game stop for a while
   virtual void printScreen(const char** print) const override; //prints screen
};
#endif
