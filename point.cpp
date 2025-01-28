#include "point.h"
#include "general.h"
#include <iostream>


void Point::draw(char ch, Point pos,bool& iscolorMode) //draws point on screen
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(pos.x, pos.y);

	if (iscolorMode)
	{
		if (ch == LADDER_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (ch == '<' || ch == '>' || ch == '-')
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		}
		else if (ch == DONKEY_KONG_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		}
		else if (ch == BARREL_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		}
		else if (ch == NON_CLIMBING_GHOST_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else if (ch == CLIMBING_GHOST_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Default color
		}

	}
	std::cout << ch;
}