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

	blockManager.getBlcokNum(tempBlock);
	boardManager.SetSpawn(tempBlock);

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			cout << tempBlock[i][j];
		}
		cout << endl;
	}*/
}

void GameManager::Run()
{
	boardManager.DrawFrame();

	spawnBlock();

	boardManager.DrawBoard();
}
