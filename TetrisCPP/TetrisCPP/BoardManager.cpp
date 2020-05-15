#include "BoardManager.h"

BoardManager::BoardManager()
{
	CursorView(0);

	memset(board, 0, HEIGHT * WIDTH * sizeof(int));

	spawnX = WIDTH / 2 - 2;
	spawnY = 0;
	calScore = 0;
}

BoardManager::~BoardManager()
{
}

//Ŀ�� ����
void BoardManager::CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//��ǥ �̵�
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

//���� ���� �׸���
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

//��� ������
Point BoardManager::MoveBlock(Point curPoint, Point movePoint, int curBlock[][4])
{
	bool isCollision = CheckCollision(curBlock, curPoint + movePoint);
	bool isBlock = CheckBelow(curBlock, curPoint + movePoint);

	Point destPoint = isCollision ? curPoint : curPoint + movePoint;

	//���� ��� �����
	RemoveBlcok(curBlock, curPoint);

	//��� �浹�� ����
	if (isBlock && movePoint == Point{ 0, 1 })
	{
		FixBlock(curBlock, curPoint);

		DrawBoard();

		return { -1, -1 };
	}

	//��� �̵�
	DrawBlcok(curBlock, destPoint);
		
	return destPoint;
}

//��Ʈ ��ǥ ��ġ ���
Point BoardManager::GetGhostPoint(int curBlock[][4], Point point)
{
	Point down = { 0, 1 };
	Point ghostPoint = point;

	while (!CheckBelow(curBlock, ghostPoint + down))
	{
		ghostPoint = ghostPoint + down;
	}

	return ghostPoint;
}

//���� ���� üũ
bool BoardManager::CheckGameOver()
{
	for (int i = 0; i < WIDTH; i++)
	{
		if (board[0][i] == 1)
			return true;
	}

	return false;
}

//��� + ��Ʈ ����
void BoardManager::RemoveBlcok(int curBlock[][4], Point point)
{
	RemovePreBlock(curBlock, point);
	DrawGhost(curBlock, point, EMPTY);
}

//��� + ��Ʈ �׸���
void BoardManager::DrawBlcok(int curBlock[][4], Point point)
{
	DrawGhost(curBlock, point, GHOST);
	DrawNextBlock(curBlock, point, BLOCK);
}

//ȸ�� ���� üũ
bool BoardManager::CheckRotatable(int curBlock[][4], Point point)
{
	return !(CheckCollision(curBlock, point) || CheckBelow(curBlock, point));
}

//��Ʈ �׸���
void BoardManager::DrawGhost(int curBlock[][4], Point curPoint, int shapeIndex)
{
	Point ghostPoint = GetGhostPoint(curBlock, curPoint);

	DrawNextBlock(curBlock, ghostPoint, shapeIndex);
}

//�ϼ��� ���� ó��
void BoardManager::RemoveCompleteLine(Point point)
{
	int check = 3;
	int score = 0;
	int count = 1;

	while (check >= 0)
	{
		if (CheckLine(point.y + check))
		{
			RemoveLine(point.y + check);
			score += 100 * count++;
		}
		else
			check--;
	}

	calScore = score;
}

//���� �˻�
bool BoardManager::CheckLine(int y)
{
	bool isCompleteLine = true;

	for (int i = 1; i < WIDTH - 1; i++)
	{
		if (board[y][i] != 1)
		{
			isCompleteLine = false;
			break;
		}
	}
	
	return isCompleteLine;
}

//���� ���� & �̵�
void BoardManager::RemoveLine(int y)
{
	for (int i = y; i > 0; i--)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			board[i][j] = board[i - 1][j];
		}
	}
}

int BoardManager::returnScore()
{
	int score = calScore;
	calScore = 0;

	return score;
}

//�� ����
bool BoardManager::CheckCollision(int curBlock[][4], Point destPoint)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//if (curBlock[i][j] == 1 && board[destPoint.y + i][destPoint.x + j] == 2)
			//	return true;
			if (curBlock[i][j] == 1 && 
				(board[destPoint.y + i][destPoint.x + j] == 2 || board[destPoint.y + i][destPoint.x + j] == 1))
				return true;
		}
	}
	return false;
}

//��� �浹 or ������ ���� ����
bool BoardManager::CheckBelow(int curBlock[][4], Point destPoint)
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

//��Ͽ� ���Ǵ� �ڽ� �ϳ� �׸���
void BoardManager::DrawPixel(int x, int y, int figure)
{
	gotoxy(x, y);
	cout << shape[figure];
}

//���� ��� �����
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

//��� �׸���
void BoardManager::DrawNextBlock(int curBlock[][4], Point point, int block)
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

//�浹�� ��� ����
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

	RemoveCompleteLine(point);
	DrawBoard();
}
