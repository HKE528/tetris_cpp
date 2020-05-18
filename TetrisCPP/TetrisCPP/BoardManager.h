#pragma once
#include "Value.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();
	enum Shape
	{
		WELL,
		EMPTY,
		BLOCK,
		GHOST
	};

private:
	

	int board[HEIGHT][WIDTH];
	const char* shape[4] = { "бс", "  ", "в├", "бр" };

	int spawnX;
	int spawnY;
	int calScore;

private:
	void CursorView(char show);
	bool CheckCollision(int curBlock[][4], Point destPoint);
	bool CheckBelow(int curBlock[][4], Point destPoint);
	void RemovePreBlock(int curBlock[][4], Point point);
	void FixBlock(int curBlock[][4], Point point);
	void DrawGhost(int curBlock[][4], Point curPoint, int shapeIndex);
	bool CheckLine(int y);
	void RemoveLine(int y);

public:
	void SetFrame();
	void DrawBoard();
	Point SetSpawn(int block[][4]);
	Point MoveBlock(Point curPoint, Point movePoint, int curBlock[][4]);
	Point GetGhostPoint(int curBlock[][4], Point point);
	bool CheckGameOver();
	void RemoveBlcok(int curBlock[][4], Point point);
	void DrawBlcok(int curBlock[][4], Point point);
	void DrawNextBlock(int curBlock[][4], Point point, int block);
	bool CheckRotatable(int curBlock[][4], Point point);
	void RemoveCompleteLine(Point point);
	int returnScore();
	void DrawPixel(int x, int y, int shape);
	void Restart();
};

