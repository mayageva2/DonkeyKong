#ifndef _GAME_RENDER_H
#define _GAME_RENDER_H
#include "point.h"
#include <string>

class GameRenderer 
{
public:
    virtual void draw( char ch, Point pos, bool& ifcolorMode) const = 0;
    virtual void drawNumber(int num, Point pos, bool& ifcolorMode) const = 0;
    virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const = 0;
    virtual void clearScreen() = 0;
    virtual void sleep(int ms) = 0;
    virtual ~GameRenderer() = default;
    virtual void printScreen(const char** print) const = 0;
};
#endif
