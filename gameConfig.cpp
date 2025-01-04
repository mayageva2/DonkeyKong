#include "gameConfig.h"
#include "general.h"
#include "point.h"

#include <fstream>
#include <iostream>
using namespace std;

void GameConfig::load(const std::string& filename, bool& flag) 
{
	ifstream screen_file(filename);
	//cout << screen_file.is_open() << std::endl;
	// TODO: handle errors (all sort of...) - do not submit it like that :)
	int curr_row = 0;
	int curr_col = 0;
	char c;
	while (!screen_file.get(c).eof() && curr_row < MAX_Y) 
	{
		if (c == '\n') {
			if (curr_col < MAX_X) 
			{
				// add spaces for missing cols
#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, std::string(MAX_X - curr_col - 1, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}
		if (curr_col < MAX_X) {
			// handle special chars
			if (c == '@') {
				marioPos = { curr_col, curr_row };
				marioCounter++;
				if (marioCounter > 1 || marioCounter < 1)
				{
					cout << "error message";
					flag = false;
					return;
				}
			}
			else if (c == '&') {
				donkeyPos = { curr_col, curr_row };
				donkeyCounter++;
				if (donkeyCounter > 1 || donkeyCounter < 1)
				{
					cout << "error message";
					flag = false;
					return;
				}
			}
			else if (c == 'x')
			{
				Point p = { curr_col, curr_row };
				GhostsPos.push_back(p);
				ghostCounter++;
			}
			else if (c == 'L')
			{
				//add
			}

			originalBoard[curr_row][curr_col++] = c;
		}
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
}

void GameConfig::PrintBoard() const//prints board
{
	gotoxy(0, 0);
	for (int i = 0; i < MAX_Y - 1; i++) {
		cout << originalBoard[i] << '\n';
	}
	cout << originalBoard[MAX_Y - 1];
}

void GameConfig::resetBoard() //resets to original board
{
	for (int i = 0; i < MAX_Y; i++)
	{
		memcpy(currentBoard[i], originalBoard[i], MAX_X);
	}
}



