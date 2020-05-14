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
	system("cls");

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

			//cout << board[i][j] << " ";
		}
		//cout << endl;
		
	}

}

Point BoardManager::SetSpawn(int block[][4])
{
	//블록스폰 좌표 설정
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MoveBlock({ spawnX, spawnY }, { 0,0 }, block);
		}
	}

	return { spawnX, spawnY };
}

Point BoardManager::MoveBlock(Point curPoint, Point movePoint, int curBlock[][4])
{
	bool isCollision = CheckWell(curBlock, { curPoint.x + movePoint.x, curPoint.y + movePoint.y });
	bool isBlock = CheckBlockCollision(curBlock, { curPoint.x + movePoint.x, curPoint.y + movePoint.y });

	//Point destPoint = isCollision ? curPoint : curPoint + movePoint;

	int destX = isCollision ? curPoint.x : curPoint.x + movePoint.x;
	int destY = isCollision ? curPoint.y : curPoint.y + movePoint.y;

	//이전 블록 지우기
	RemovePreBlock(curBlock, curPoint);
	DrawGhost(curBlock, curPoint, EMPTY);

	//블록 충돌시 고정
	if (isBlock)
	{
		FixBlock(curBlock, curPoint);

		DrawBoard();

		return { -1, -1 };
	}

	//블록 이동
	DrawGhost(curBlock, { destX, destY }, GHOST);
	DrawBlock(curBlock, { destX, destY }, BLOCK);
	
	
	return { destX, destY };
}

void BoardManager::DrawGhost(int curBlock[][4], Point curPoint, int shapeIndex)
{
	Point down = { 0, 1 };
	Point ghostPoint = curPoint;

	while (!CheckBlockCollision(curBlock, ghostPoint + down))
	{
		ghostPoint = ghostPoint + down;
	}

	DrawBlock(curBlock, ghostPoint, shapeIndex);
}

//벽 감지
bool BoardManager::CheckWell(int curBlock[][4], Point destPoint)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1 && board[destPoint.y + i][destPoint.x + j] == 2)
				return true;
		}
	}
	return false;
}

//블록 충돌 or 마지막 라인 감지
bool BoardManager::CheckBlockCollision(int curBlock[][4], Point destPoint)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1 && 
				(board[destPoint.y + i][destPoint.x + j] == 1 || destPoint.y + i == HEIGHT - 1))
				return true;
		}
	}
	return false;
}

void BoardManager::DrawPixel(int x, int y, int figure)
{
	gotoxy(x, y);
	cout << shape[figure];
}

void BoardManager::RemovePreBlock(int curBlock[][4], Point point)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1)
			{
				DrawPixel(point.x + j, point.y + i, EMPTY);
			}
		}
	}
}

void BoardManager::DrawBlock(int curBlock[][4], Point point, int block)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1)
			{
				DrawPixel(point.x + j, point.y + i, block);
			}
		}
	}
}

void BoardManager::FixBlock(int curBlock[][4], Point point)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (curBlock[i][j] == 1)
				board[point.y + i][point.x + j] = 1;
		}
	}

	DrawBoard();
}
