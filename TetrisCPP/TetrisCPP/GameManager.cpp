#include "GameManager.h"

GameManager::GameManager()
{
	InitializeCriticalSection(&cs);

	info.level = 1;
	info.score = 0;
	info.speed = 3000;
	isBlock = true;
}

GameManager::~GameManager()
{
	DeleteCriticalSection(&cs);
}

void GameManager::Start()
{
	info.level = 1;
	info.score = 0;
	info.speed = 3000;

	int block[4][4] = { 0, };
	blockManager.getNextBlcok(block);

	ui.GameUI(info, block);

	boardManager.SetFrame();

	boardManager.DrawBoard();

	spawnBlock();

}

void GameManager::spawnBlock()
{
	blockManager.SpawnBlock();

	int tempBlock[4][4] = { 0, };

	blockManager.getBlcok(tempBlock);
	Point curPoint = boardManager.SetSpawn(tempBlock);

	blockManager.SetCurPoint(curPoint);

	SetGameInfo();
	isBlock = true;
}

void GameManager::MoveBlock(char key)
{
	Point movePoint = controller.MoveBlockPoint(key);
	int block[4][4] = { 0, };
	blockManager.getBlcok(block);

	EnterCriticalSection(&cs);
	Point curPoint = blockManager.GetCurPoint();
	curPoint = boardManager.MoveBlock(curPoint, movePoint, block);

	if (curPoint.x < 0 && curPoint.y < 0)
	{
		isBlock = false;
	}
	else
		blockManager.SetCurPoint(curPoint);
	LeaveCriticalSection(&cs);
}

void GameManager::QuickDown()
{
	int block[4][4] = { 0, };
	blockManager.getBlcok(block);

	Point curPoint = blockManager.GetCurPoint();
	Point destPoint = boardManager.GetGhostPoint(block, curPoint);

	curPoint = boardManager.MoveBlock(curPoint, destPoint - curPoint, block);
	boardManager.MoveBlock(curPoint, { 0, 1 }, block);

	isBlock = false;
}

void GameManager::RotateBlock()
{
	Point curPoint = blockManager.GetCurPoint();
	int block[4][4] = { 0, };
	int preBlock[4][4] = { 0, };
	blockManager.getBlcok(block);
	blockManager.getBlcok(preBlock);

	blockManager.rotateBlock(preBlock);
	if (boardManager.CheckRotatable(preBlock, curPoint))
	{
		boardManager.RemoveBlcok(block, curPoint);

		blockManager.rotateBlock();
		blockManager.getBlcok(block);

		boardManager.DrawBlcok(block, curPoint);
	}
}

void GameManager::BlockDown()
{
	while (!boardManager.CheckGameOver())
	{
		Sleep(info.speed);

		if(isBlock)
			MoveBlock(DOWN);
	}
}

void GameManager::SetGameInfo()
{
	info.score += boardManager.returnScore();

	if (info.level >= 10)
		info.level = 10;
	else 
		info.level = info.score < 2000 ? 1 : info.score / 2000 + 1;

	if (info.speed <= 50)
		info.speed = 50;
	else
		info.speed = 3050 - info.level * 300;

	int block[4][4] = { 0, };
	blockManager.getNextBlcok(block);

	ui.UpdateScore(info);
	ui.UpdateNextBlock(block);
}

bool GameManager::GameOver()
{
	int key = NULL;

	do {
		ui.GameOver(info);

		key = _getch();

		if (key == S || key == s)
		{
			InputKey(key);
			continue;
		}
	} while (!(key == R || key == r || key == ESC));
	return InputKey(key);
}

void GameManager::GameStart()
{
	ui.StartUI();

	int key;
	do {
		key = _getch();
	} while (key != ENTER);
}

void GameManager::ShowRank()
{
	ui.ShowRank();
}

bool GameManager::InputKey(char key)
{
	switch (key)
	{
	case DOWN:
	case RIGHT:
	case LEFT:
		MoveBlock(key);
		break;

	case SPACE:
		QuickDown();
		break;

	case UP:
		RotateBlock();
		break;

	case R:
	case r:
		boardManager.Restart();
		ui.SetIsRecord(false);
		return true;

	case ESC:
		return false;

	case ENTER:
		return true;

	case S:
	case s:
		ShowRank();
		break;
	}
}

void GameManager::Run()
{
	GameStart();

	do
	{
		
		Start();

		//BlockDown 스레드 생성
		function<void()> pBlockDown;
		pBlockDown = bind(&GameManager::BlockDown, this);
		thread blockDown(pBlockDown);

		int key;
		while (!boardManager.CheckGameOver())
		{
			if (!isBlock)
			{
				spawnBlock();
			}

			if (_kbhit())
			{
				key = _getch();
				if (key == 224)
				{
					key = _getch();
					InputKey(key);
				}
				else
				{
					InputKey(key);
				}
			}
		}

		blockDown.join();
		
	} while (GameOver());
}
