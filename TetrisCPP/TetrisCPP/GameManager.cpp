#include "GameManager.h"

GameManager::GameManager()
{
	info.level = 1;
	info.score = 0;
	info.speed = 2000;
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	int block[4][4] = { 0, };
	blockManager.getBlcok(block);

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
}

void GameManager::MoveBlock(char key)
{
	Point movePoint = controller.MoveBlockPoint(key);
	Point curPoint = blockManager.GetCurPoint();

	int block[4][4] = { 0, };
	blockManager.getBlcok(block);

	curPoint = boardManager.MoveBlock(curPoint, movePoint, block);

	if (curPoint.x < 0 && curPoint.y < 0)
	{
		spawnBlock();
	}
	else
		blockManager.SetCurPoint(curPoint);

}

void GameManager::QuickDown()
{
	int block[4][4] = { 0, };
	blockManager.getBlcok(block);

	Point curPoint = blockManager.GetCurPoint();
	Point destPoint = boardManager.GetGhostPoint(block, curPoint);

	curPoint = boardManager.MoveBlock(curPoint, destPoint - curPoint, block);
	boardManager.MoveBlock(curPoint, { 0, 1 }, block);

	spawnBlock();
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

		MoveBlock(DOWN);
		/*cout << info.level << endl;
		cout << info.score << endl;
		cout << info.speed << endl;*/
	}
}

void GameManager::SetGameInfo()
{
	info.score += boardManager.returnScore();
	info.level = info.score < 2000 ? 1 : info.score / 2000 + 1;
	if (info.speed < 100)
		info.speed = 100;
	else
		info.speed = 2200 - info.level * 300;

	ui.UpdateScore(info);
}

void GameManager::InputKey(char key)
{
	switch (key)
	{
	case DOWN:
	case RIGHT:
	case LEFT:
		MoveBlock(key);
		SetGameInfo();
		break;

	case SPACE:
		QuickDown();
		SetGameInfo();
		break;

	case UP:
		RotateBlock();
		break;
	}
}

void GameManager::Run()
{
	Start();
	
	//BlockDown 스레드 생성
	function<void()> pBlockDown;
	pBlockDown = bind(&GameManager::BlockDown, this);
	thread blockDown(pBlockDown);

	int key;
	while (!boardManager.CheckGameOver())
	{
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
}
