#pragma once
#include "BoardManager.h"
#include "BlockManager.h"
#include "Controller.h"
#include "UI.h"
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
	UI ui;
	Info info;

private:
	void Start();
	void spawnBlock();
	void InputKey(char key);
	void MoveBlock(char key);
	void QuickDown();
	void RotateBlock();
	void BlockDown();
	void SetGameInfo();

public:
	void Run();


};

