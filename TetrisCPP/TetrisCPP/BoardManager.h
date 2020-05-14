#pragma once
#include "Value.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

private:
	enum Shape
	{
		WELL,
		EMPTY,
		BLOCK
	};

	int board[HEIGHT][WIDTH];
	const char* shape[3] = { "бс", "  ", "бр" };

	int spawnX;
	int spawnY;

private:
	void gotoxy(int x, int y);
	bool CheckWell(int curBlock[][4], Point destPoint);
	void DrawBlock(int x, int y, int shape);

public:
	void SetFrame();
	void DrawBoard();
	Point SetSpawn(int block[][4]);
	Point MoveBlock(Point curPoint, Point movePoint, int curBlock[][4]);
	bool CheckBlockCollision(int curBlock[][4], Point destPoint);
};

