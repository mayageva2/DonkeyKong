#ifndef _SILENT_RENDER_H
#define _SILENT_RENDER_H
#include "gameRenderer.h"

class SilentRenderer : public GameRenderer 
{
public:
  virtual void draw(char ch, Point pos,  bool& ifcolorMode) override {};
  virtual void drawNumber(int num, Point pos, bool& ifcolorMode)override {};
  virtual void clearScreen() override {};
  virtual void sleep(int ms) override {};
  virtual void drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) override {};
  virtual void printScreen(const char** print)override {};
};
#endif
