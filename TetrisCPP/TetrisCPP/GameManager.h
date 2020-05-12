#pragma once
#include "BoardManager.h"
#include "BlockManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	BoardManager boardManager;
	BlockManager blockManager;

private:
	void spawnBlock();

public:
	void Run();
};

