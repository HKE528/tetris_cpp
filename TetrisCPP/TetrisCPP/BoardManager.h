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
		BLOCK,
		GHOST
	};

	int board[HEIGHT][WIDTH];
	const char* shape[4] = { "бс", "  ", "бр", "в├" };

	int spawnX;
	int spawnY;

private:
	void gotoxy(int x, int y);
	bool CheckWell(int curBlock[][4], Point destPoint);
	bool CheckBlockCollision(int curBlock[][4], Point destPoint);
	void DrawPixel(int x, int y, int shape);
	void RemovePreBlock(int curBlock[][4], Point point);
	void DrawBlock(int curBlock[][4], Point point, int block);
	void FixBlock(int curBlock[][4], Point point);
	void DrawGhost(int curBlock[][4], Point curPoint, int shapeIndex);

public:
	void SetFrame();
	void DrawBoard();
	Point SetSpawn(int block[][4]);
	Point MoveBlock(Point curPoint, Point movePoint, int curBlock[][4]);
	Point GetGhostPoint(int curBlock[][4], Point point);
	bool CheckGameOver();
	
};

