#include "BoardManager.h"

BoardManager::BoardManager()
{
	CursorView(0);

	memset(board, 0, HEIGHT * WIDTH * sizeof(int));

	spawnX = WIDTH / 2 - 2;
	spawnY = 0;
}

BoardManager::~BoardManager()
{
}
void BoardManager::CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
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
	//������ ����
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
	//system("cls");

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
	//��Ͻ��� ��ǥ ����
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
	bool isCollision = CheckWell(curBlock, curPoint + movePoint);
	bool isBlock = CheckBlockCollision(curBlock, curPoint + movePoint);

	Point destPoint = isCollision ? curPoint : curPoint + movePoint;

	//���� ��� �����
	RemovePreBlock(curBlock, curPoint);
	DrawGhost(curBlock, curPoint, EMPTY);

	//��� �浹�� ����
	if (isBlock)
	{
		FixBlock(curBlock, curPoint);

		DrawBoard();

		return { -1, -1 };
	}

	//��� �̵�
	DrawGhost(curBlock, destPoint, GHOST);
	DrawBlock(curBlock, destPoint, BLOCK);
	
	
	return destPoint;
}

//��Ʈ ��ǥ ��ġ ���
Point BoardManager::GetGhostPoint(int curBlock[][4], Point point)
{
	Point down = { 0, 1 };
	Point ghostPoint = point;

	while (!CheckBlockCollision(curBlock, ghostPoint + down))
	{
		ghostPoint = ghostPoint + down;
	}

	return ghostPoint;
}

bool BoardManager::CheckGameOver()
{
	for (int i = 0; i < WIDTH; i++)
	{
		if (board[0][i] == 1)
			return true;
	}

	return false;
}

//��Ʈ �׸���
void BoardManager::DrawGhost(int curBlock[][4], Point curPoint, int shapeIndex)
{
	Point ghostPoint = GetGhostPoint(curBlock, curPoint);

	DrawBlock(curBlock, ghostPoint, shapeIndex);
}

//�� ����
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

//��� �浹 or ������ ���� ����
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
