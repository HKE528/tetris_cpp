#pragma once
#include "Value.h"

class BlockManager
{
public:
	BlockManager();
	virtual ~BlockManager();

private:
	int curBlock;
	Point curPoint;
	int nextBlock;

private:
	int GetRandomInt();
	void SetCurBlock();

public:
	void getBlcok(int temp[][4]);
	void getNextBlcok(int temp[][4]);
	void rotateBlock();
	void rotateBlock(int temp[][4]);
	Point GetCurPoint();
	void SetCurPoint(Point point);
	//void MoveCurPoint(Point point);
	void SpawnBlock();


private:
	int block[7][4][4] =
	{
		0,0,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,1,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,1,1,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0,

		0,0,0,0,
		1,1,0,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,0,1,1,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,0,0,
		1,1,1,0,
		0,0,0,0,
	};
};