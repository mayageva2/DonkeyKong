#ifndef _GAMECONFIG_H
#define _GAMECONFIG_H
#include <iostream>

class GameConfig
{
public:
	//Game boarders
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	const char* originalBoard[MAX_Y] = {
		// 012345678901a23456789012345678901234567890123456789012345678901234567890123456789
		   "|------------------------------------------------------------------------------|", // 0
		   "|                                  SCORE:0                                     |", // 1
		   "|               $                                                              |", // 2
		   "|            >>>>>>>>                                                          |", // 3
		   "|   &        H      H                                                          |", // 4
		   "|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>                                      |", // 5
		   "|                                       H              >>>>>>>>>>>>>>          |", // 6
		   "|>>>>>>>>>                              H        >>>>>              H          |", // 7
		   "|H         <<<<<<                       >>>>>>>>                    H          |", // 8
		   "|H                <<<<<<<<<<<<    <<<<<<                            H          |", // 9
		   "|H                H      H            H                             H          |", // 10
		   "|H                H      H            H                           <<<<<<<<<<<<<|", // 11
		   "|>>>>>>>>>>       H      H            H                            H           |", // 12
		   "|    H            H      H            >>>>>>                       H           |", // 13
		   "|    H            H      H                   <<<<<<<<<<<<<   <<<<<<<<<         |", // 14
		   "|    H            H      H                          H                 >>>>>>>>>|", // 15
		   "|    H            H      H                          H                     H    |", // 16
		   "|    H        <<<<<<<<<<<<               >>>>>>>>>>>>                     H    |", // 17
		   "|    H                   >>>>>>>>>>>>>>>                              >>>>>>>>>|", // 18
		   "|    H                                 H                        <<<<<          |", // 19
		   "|    H                                 H                   <<<<<               |", // 20
		   "|>>>>>>>                               H               <<<<<                   |", // 21
		   "|        <<<<<<<                       >>>>>           H                       |", // 22
		   "|               >>>>>>                     H           H                       |", // 23
		   "|------------------------------------------------------------------------------|"  // 24
	};
	char currentBoard[MAX_Y][MAX_X];
	static constexpr int MIN_Y = 1;
	static constexpr int MIN_X = 1;
	enum class eKeys { LEFT = 'a', LEFT2 = 'A', RIGHT = 'd', RIGHT2 = 'D', UP = 'w', UP2 = 'W', DOWN = 'x', DOWN2 = 'X', STAY = 's', STAY2 = 'S', ESC = 27 };
	void PrintBoard();
	void resetBoard();

	char GetChar(int x, int y)// returns a char that is placed on given point on board
	{
		return currentBoard[y][x];
	}

	void SetChar(int x, int y, char ch)// returns a char that is placed on given point on board
	{
		if (x >= 0 && x <= MAX_X && y >= 0 && y <= MAX_Y)
		{
			if (GetChar(x, y) == 'H')
			{
				currentBoard[y][x] = ch;
				currentBoard[y][x] = 'H';
			}
			else if (GetChar(x, y) == '<')
			{
				currentBoard[y][x] = ch;
				currentBoard[y][x] = '<';
			}
			else if (GetChar(x, y) == '>')
			{
				currentBoard[y][x] = ch;
				currentBoard[y][x] = '>';
			}
			else
				currentBoard[y][x] = ch;
		}
	}

	void PrintKong();
};

#endif



