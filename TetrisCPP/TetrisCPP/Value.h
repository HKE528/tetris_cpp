#pragma once

#include<iostream>
#include<Windows.h>
#include<vector>
#include<conio.h>
#include<time.h>

#define WIDTH 12
#define HEIGHT 21
#define X_OFFSET 1

using namespace std;

typedef struct _Point
{
	int x;
	int y;
}Point;

enum KEY
{
	UP = 72,
	DOWN = 80,
	RIGHT = 77,
	LEFT = 75,
	SPACE = 32
};

Point operator+ (Point A, Point B);
Point operator- (Point A, Point B);
bool operator== (Point A, Point B);