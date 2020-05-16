#pragma once

#include<iostream>
#include<Windows.h>
#include<vector>
#include<conio.h>
#include<time.h>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include<iomanip>

#define WIDTH 12
#define HEIGHT 21
#define X_OFFSET 2
#define Y_OFFSET 0

using namespace std;

typedef struct _Point
{
	int x;
	int y;
}Point;

typedef struct
{
	int level;
	int score;
	int speed;
}Info;

typedef struct
{
	string name;
	int score;
}Score;

enum KEY
{
	UP = 72,
	DOWN = 80,
	RIGHT = 77,
	LEFT = 75,
	SPACE = 32,
	R = 82,
	r = 114,
	ESC = 27,
	ENTER = 13,
	S = 83,
	s = 115,
	BSPACE = 8
};

Point operator+ (Point A, Point B);
Point operator- (Point A, Point B);
bool operator== (Point A, Point B);
void gotoxy(int x, int y);
bool compare(Score A, Score B);