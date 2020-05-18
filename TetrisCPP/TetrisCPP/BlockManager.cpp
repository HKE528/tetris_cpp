#include "BlockManager.h"

BlockManager::BlockManager()
{
	curBlock = 0;
	nextBlock = GetRandomInt();
}

BlockManager::~BlockManager()
{
}

Point BlockManager::GetCurPoint()
{
	return curPoint;
}

void BlockManager::SetCurPoint(Point point)
{

	curPoint.x = point.x;
	curPoint.y = point.y;
}

//void BlockManager::MoveCurPoint(Point point)
//{
//	curPoint.x += point.x;
//	curPoint.y += point.y;
//}

void BlockManager::SpawnBlock()
{
	SetCurBlock();
}

int BlockManager::GetRandomInt()
{
	int num[7] = { 0, 1, 2, 3, 4, 5, 6 };

	srand(time(0));
	int x, y, temp;

	for (int i = 0; i < 100; i++)
	{
		x = rand() % 7;
		y = rand() % 7;

		temp = num[x];
		num[x] = num[y];
		num[y] = temp;
	}

	return num[0];
	//return 3;
}

void BlockManager::SetCurBlock()
{
	curBlock = nextBlock;
	nextBlock = GetRandomInt();
	int rotate = GetRandomInt();

	while (rotate--)
	{
		rotateBlock();
	}
}

void BlockManager::getBlcok(int temp[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = block[curBlock][i][j];
		}
	}
}

void BlockManager::getNextBlcok(int temp[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = block[nextBlock][i][j];
		}
	}
}

void BlockManager::rotateBlock()
{
	int rotateBlock[4][4] = { 0, };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rotateBlock[j][3 - i] = block[curBlock][i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[curBlock][i][j] = rotateBlock[i][j];
		}
	}
}

void BlockManager::rotateBlock(int temp[][4])
{
	int rotateBlock[4][4] = { 0, };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rotateBlock[j][3 - i] = temp[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp[i][j] = rotateBlock[i][j];
		}
	}
}
