#include "barrel.h"
#include "barrel.h"


void Barrel::clearFromScreen(GameConfig& board)
{
	board.SetChar(location.x, location.y, ' '); //resets barrel's previous location
	gotoxy(location.x, location.y);
	//cout << "\xF0\x9F\x92\xA5";  // // BETTER VERSION
	cout << "BOOM";
	Sleep(600);
	for (int i = 3; i >= 0; i--) // CLEANS 'BOOM' from screen
	{
		gotoxy(location.x + i, location.y);
		cout << " ";
	}
}

void Barrel::Print(int x, int y)
{
	cout << this->barrelCh;
	Sleep(100);
	gotoxy(x, y);
	cout << " ";
}

void Barrel::PrintLadder()
{
	cout << this->ladderCh;
}

void Barrel::moveBarrel(GameConfig& board)
{
	board.SetChar(this->location.x, this->location.y, ' '); //resets barrel's previous location
	gotoxy(location.x, location.y);

	if ((dropDirection == false)) // Drop barrel down else drop barrel forward
	{
		location = downstart;
		gotoxy(location.x, location.y);
		dropDirection = true;
	}


	if (pBoard->GetChar(location.x, location.y + 1) != '>' && pBoard->GetChar(location.x, location.y + 1) != '<'
		&& pBoard->GetChar(location.x, location.y + 1) != '=' && pBoard->GetChar(location.x, location.y + 1) != '-')
	{
		Print(location.x, location.y);
		++location.y;
		++fallCount;
	}
	else if (pBoard->GetChar(location.x, location.y + 1) == '>')
	{
		direction = true;
		if (fallCount >= 8)
		{
			barrelNotActive(); //Unactivate barrel
		}
		else
		{
			fallCount = 0;
			if (pBoard->GetChar(location.x, location.y) == 'H')
			{
				Print(location.x, location.y);
				gotoxy(location.x, location.y);
				PrintLadder();
			}
			else
			{
				Print(location.x, location.y);
			}
			++location.x;
		}
	}
	else if (pBoard->GetChar(location.x, location.y + 1) == '<')
	{
		direction = false;
		if (fallCount >= 8)
		{
			barrelNotActive(); //Unactivate barrel
		}
		else
		{
			fallCount = 0;
			if (pBoard->GetChar(location.x, location.y) == 'H')
			{
				Print(location.x, location.y);
				gotoxy(location.x, location.y);
				PrintLadder();
			}
			else
			{
				Print(location.x, location.y);
			}
			--location.x;
		}
	}
	else if (pBoard->GetChar(location.x, location.y + 1) == '=' || pBoard->GetChar(location.x, location.y + 1) == '-')
	{
		if (fallCount >= 8)
		{
			barrelNotActive(); //Unactivate barrel
		}
		else
		{
			fallCount = 0;
			if (direction == true)
			{
				if (pBoard->GetChar(location.x, location.y) == 'H')
				{
					Print(location.x, location.y);
					gotoxy(location.x, location.y);
					PrintLadder();
				}
				else
				{
					Print(location.x, location.y);
				}
				++location.x;
			}
			else
			{
				if (pBoard->GetChar(location.x, location.y) == 'H')
				{
					Print(location.x, location.y);
					gotoxy(location.x, location.y);
					PrintLadder();
				}
				else
				{
					Print(location.x, location.y);
				}
				--location.x;
			}
		}
	}
	if (isActive)
	{
		gotoxy(location.x, location.y);
		cout << this->barrelCh;
	}

	board.SetChar(this->location.x, this->location.y, this->barrelCh);
}
