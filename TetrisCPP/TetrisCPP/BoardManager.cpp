#include "BoardManager.h"

BoardManager::BoardManager()
{
	for (int i = 0; i < WEDIT * HEIGHT; i++)
	{
		board[i] = 0;
	}
}

BoardManager::~BoardManager()
{
}

void BoardManager::gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void BoardManager::DrawFrame()
{
	//프레임 그리기
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			gotoxy(j * (WEDIT + 1), i);
			cout << shape[WELL];
		}
		cout << endl;
	}

	for (int i = 0; i < WEDIT + 2; i++)
	{
		gotoxy(i, HEIGHT);
		cout << shape[WELL];
	}
}
