#include "BoardManager.h"

BoardManager::BoardManager()
{
	memset(board, 0, HEIGHT * WIDTH);

	spawnX = WIDTH / 2 - 2;
	spawnY = 0;
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
			gotoxy(j * (WIDTH + 1), i);
			cout << shape[WELL];
		}
		//cout << endl;
	}

	for (int i = 0; i < WIDTH + 2; i++)
	{
		gotoxy(i, HEIGHT);
		cout << shape[WELL];
	}
}

void BoardManager::SetSpawn(int block[][4])
{
	//블록스폰 좌표 설정
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board[spawnY + i][spawnX + j] = block[i][j];
		}
	}
}

void BoardManager::DrawBoard()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			gotoxy(j + X_OFFSET, i);
			switch (board[i][j])
			{
			case 0:
				cout << shape[EMPTY];
				break;
			case 1:
				cout << shape[BLOCK];
				break;
			}
		}
	}

}


