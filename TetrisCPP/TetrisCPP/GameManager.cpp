#include "GameManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
}

void GameManager::spawnBlock()
{
	int tempBlock[4][4] = { 0, };

	blockManager.getBlcok(tempBlock);
	Point curPoint = boardManager.SetSpawn(tempBlock);

	blockManager.SetCurPoint(curPoint);

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			cout << tempBlock[i][j];
		}
		cout << endl;
	}*/
}

void GameManager::InputKey(char key)
{
	switch (key)
	{
	case DOWN:
	case RIGHT:
	case LEFT:

		MoveBlock(key);

		break;

	case SPACE:
		
	}
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

void GameManager::Run()
{
	/*boardManager.SetFrame();

	boardManager.DrawBoard();

	spawnBlock();*/

	int key;
	while (1)
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
}
