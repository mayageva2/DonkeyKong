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
   virtual void draw(char ch, Point pos,  bool& iscolorMode) const override;
   virtual void drawNumber(int num, Point pos, bool& ifcolorMode) const override;
   virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const override;
   virtual void clearScreen() override { clrscr(); }
   virtual void sleep(int ms) override { Sleep(ms-20);}
   virtual void printScreen(const char** print) const override;
};
#endif
