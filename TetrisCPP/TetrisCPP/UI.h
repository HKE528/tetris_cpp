#pragma once
#include "Value.h"
#include "BoardManager.h"
#include "IOManger.h"

class UI
{
public :
	UI();
	~UI();

private:
	BoardManager boardManager;
	bool isRecord;

private:
	void ShowScore(Info info);
	void ShowNextBlock(int nextBlock[][4]);
	void FillFrame();

public :
	void StartUI();
	void GameUI(Info info, int nextBlock[][4]);
	void GameOver(Info info);
	void UpdateScore(Info info);
	void UpdateNextBlock(int nextBlock[][4]);
	void ShowRank();
	void SetIsRecord(bool flag);
};

