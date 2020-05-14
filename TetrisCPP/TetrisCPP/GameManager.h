#pragma once
#include "BoardManager.h"
#include "BlockManager.h"
#include "Controller.h"
#include "Value.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	BoardManager boardManager;
	BlockManager blockManager;
	Controller controller;

private:
	void Start();
	void spawnBlock();
	void InputKey(char key);
	void MoveBlock(char key);
	void QuickDown();
	void RotateBlock();

public:
	void Run();


};

