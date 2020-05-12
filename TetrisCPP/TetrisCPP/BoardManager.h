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

	int board[WEDIT * HEIGHT];
	const char* shape[3] = { "бс", "  ", "бр" };

private:
	void gotoxy(int x, int y);

public:
	void DrawFrame();
};

