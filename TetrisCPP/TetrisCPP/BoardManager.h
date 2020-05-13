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
	bool CheckCollision(int curBlock[][4], Point destPoint);

public:
	void SetFrame();
	void DrawBoard();
	Point SetSpawn(int block[][4]);
	Point DrawBlock(Point curPoint, Point movePoint, int curBlock[][4]);
};

