#include "barrel.h"

void Barrel::clearFromScreen(GameConfig& board)
{
	board.SetChar(location.x, location.y, ' '); //resets barrel's previous location
	//cout << "\xF0\x9F\x92\xA5";  // // BETTER VERSION

	if (location.x == 78)
	{
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
	board.SetChar(this->location.x, this->location.y, ' '); //resets barrel's previous location
	
	char originalChar = board.GetChar(location.x, location.y);
	board.SetChar(location.x, location.y, originalChar);     
	gotoxy(location.x, location.y);                          
	cout << originalChar;                                    

	char floor = board.GetChar(location.x, location.y + 1);

	if ((dropDirection == false)) // Drop barrel down else drop barrel forward
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
		direction = true;
		fallCount = 0;
		++location.x;
	}
	else if (floor == '<')
	{
		direction = false;
		fallCount = 0;
		--location.x;
	}
	else if (floor == '=' || floor == '-')
	{
		fallCount = 0;
		++location.x;
	}
	if (fallCount >= 8)
	{
		deactivate();
	}
	else
	{
		board.SetChar(location.x, location.y, this->barrelCh);
		Print(location.x, location.y);
	}

	//board.SetChar(this->location.x, this->location.y, this->barrelCh);
}
