#pragma once
#include "Value.h"
#include "BoardManager.h"

class UI
{
public :
	UI();
	~UI();

private:
	BoardManager boardManager;

private:
	void ShowScore(Info info);
	void ShowNextBlock(int nextBlock[][4]);
	void FillFrame();

public :
	void StartUI();
	void GameUI(Info info, int nextBlock[][4]);
	void GameOver();
	void UpdateScore(Info info);
	void UpdateNextBlock(int nextBlock[][4]);
};

