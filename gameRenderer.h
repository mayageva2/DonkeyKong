#ifndef _GAME_RENDER_H
#define _GAME_RENDER_H
#include "point.h"
#include <string>

class GameRenderer 
{
public:
    virtual ~GameRenderer() = default; //destructor
    virtual void draw( char ch, Point pos, bool& ifcolorMode) const = 0; //draws a char
    virtual void drawNumber(int num, Point pos, bool& ifcolorMode) const = 0; //draws a num
    virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const = 0; // draws a string
    virtual void clearScreen() = 0; //clears screen
    virtual void sleep(int ms) = 0; //stops game for a while
    virtual void printScreen(const char** print) const = 0; //prints screen
};
#endif
