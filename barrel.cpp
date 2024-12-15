#include "barrel.h"


void Barrel::clearFromScreen() 
{
	//cout << "\xF0\x9F\x92\xA5";  // // BETTER VERSION
	if (location.x == 79)
	{
		gotoxy(location.x, location.y);
		cout << "|";
		location.x = 75;
	}
	gotoxy(location.x, location.y);
	cout << "BOOM";
	Sleep(200);
	for (int i = 3; i >= 0; i--) // CLEANS 'BOOM' from screen
	{
		gotoxy(location.x + i, location.y);
		cout << " ";
	}
}

void Barrel::Print(int x, int y)
{
	gotoxy(location.x, location.y);
	cout << barrelCh;
}

void Barrel::PrintLadder()
{
	cout << this->ladderCh;
}

void Barrel::moveBarrel(GameConfig& board)
{
	char originalChar = board.GetChar(location.x, location.y);
	board.SetChar(location.x, location.y, originalChar);
	gotoxy(location.x, location.y);
	cout << originalChar;

	char floor = board.GetChar(location.x, location.y + 1);
	if (dropDirection == false)
	{
		location.y++;
		dropDirection = true;
	}

	if (floor != '>' && floor != '<' && floor != '=' && floor != '-')
	{
		++location.y;
		++fallCount;
	}
	else if (floor == '>')
	{
		if (fallCount >= 8)
		{
			deactivate();
		}
		else
		{
			direction = true;
			fallCount = 0;
			++location.x;
		}
	}
	else if (floor == '<')
	{
		if (fallCount >= 8)
		{
			deactivate();
		}
		else
		{
			direction = false;
		fallCount = 0;
		--location.x;
	}
	}
	else if (floor == '=' || floor == '-')
	{
		if (fallCount >= 8)
		{
			deactivate();
		}
		else
		{
			fallCount = 0;
			++location.x;
		}
	}
		board.SetChar(location.x, location.y, this->barrelCh);
		Print(location.x, location.y);
}





