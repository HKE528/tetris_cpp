#include "BoardManager.h"

BoardManager::BoardManager()
{
	memset(board, 0, HEIGHT * WIDTH * sizeof(int));

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

void BoardManager::SetFrame()
{
	//프레임 설정
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			board[i][j * (WIDTH - 1)] = 2;
		}
		//cout << endl;
	}

	for (int i = 0; i < WIDTH; i++)
	{
		board[HEIGHT - 1][i] = 2;
	}
}

void BoardManager::DrawBoard()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			gotoxy(j, i);
			switch (board[i][j])
			{
			case 0:
				cout << shape[EMPTY];
				//cout << 0;
				break;
			case 1:
				cout << shape[BLOCK];
				//cout << 1;
				break;
			case 2:
				cout << shape[WELL];
				//cout << 1;
				break;
			}

			/*cout << board[i][j] << " ";
		}
		cout << endl;*/
		}
	}

}

Point BoardManager::SetSpawn(int block[][4])
{
	//블록스폰 좌표 설정
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			DrawBlock({ spawnX, spawnY }, { 0,0 }, block);
		}
	}

	return { spawnX, spawnY };
}

void BoardManager::DrawBlock(Point curPoint, Point movePoint, int curBlock[][4])
{
	int destX = curPoint.x + movePoint.x;
	int destY = curPoint.y + movePoint.y;

	//이전 블록 지우기
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1)
			{
				gotoxy(curPoint.x + j, curPoint.y + i);
				cout << shape[EMPTY];
			}
		}
	}

	//블록 이동
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1)
			{
				gotoxy(destX + j, destY + i);
				cout << shape[BLOCK];
			}
		}
	}
}

