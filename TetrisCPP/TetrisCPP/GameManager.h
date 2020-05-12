#pragma once
#include "BoardManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	BoardManager boardManager;

public:
	void Run();
};

