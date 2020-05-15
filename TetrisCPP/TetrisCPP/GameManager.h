#pragma once
#include "BoardManager.h"
#include "BlockManager.h"
#include "Controller.h"
#include "Value.h"
#include <thread>
#include <functional>

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
	void BlockDown();

public:
	void Run();


};

