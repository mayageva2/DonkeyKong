#include "consoleRenderer.h"


void ConsoleRenderer::draw(char ch, Point pos, bool& iscolorMode) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(pos.x, pos.y);

	if (iscolorMode)
	{
		if (ch == LADDER_CH || ch == 'V')
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (ch == '<' || ch == '>' || ch == '-' || ch == '=' || ch == 'Q')
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		}
		else if (ch == DONKEY_KONG_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		}
		else if (ch == MARIO_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
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
		else if (ch == PAULINE_CH)
			{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); 
		}
		else if (ch == HAMMER) 
			{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED); 
		}
		else if (ch != DELETE_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
		}
		else 
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Default color
		}

	}
	std::cout << ch;
}

void ConsoleRenderer::drawString(const std::string& str, char ch, Point pos, bool& ifcolorMode) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(pos.x, pos.y);
	if (ifcolorMode)
	{
		if (EXPLOSION == str && ch == BARREL_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			std::cout << EXPLOSION;
		}
		else if (EXPLOSION == str && ch == MARIO_CH)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			std::cout << EXPLOSION;
		}
	}
	else if (EXPLOSION == str)
	{
		std::cout << EXPLOSION;
	}
}

void ConsoleRenderer::printScreen(const char** print) const //prints screen
{
	clrscr();
	Point p = startMenu;
	for (int i = 0; i < START_MENU_Y; i++)
	{
		gotoxy(p.x, p.y);
		std::cout << print[i];
		p.y++;
	}
}

void ConsoleRenderer::drawNumber(int num, Point pos, bool& ifcolorMode) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(pos.x, pos.y);
	if (ifcolorMode)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	std::cout << num;
 }
