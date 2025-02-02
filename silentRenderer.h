#ifndef _SILENT_RENDER_H
#define _SILENT_RENDER_H
#include "gameRenderer.h"

class SilentRenderer : public GameRenderer 
{
public:
  virtual void draw(char ch, Point pos,  bool& ifcolorMode) const override {}; //draws char
  virtual void drawNumber(int num, Point pos, bool& ifcolorMode) const override {}; //draws number
  virtual void clearScreen() override {}; //clears screen
  virtual void sleep(int ms) override {}; //stops game for a while
  virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const override {}; //draws string
  virtual void printScreen(const char** print) const override {}; //prints screen
};
#endif
