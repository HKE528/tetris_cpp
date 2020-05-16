#include "UI.h"

UI::UI()
{
	system("mode con cols=50 lines=24");
}

UI::~UI()
{
}

void UI::ShowScore(Info info)
{
	//레벨 점수 표시 프레임
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//gotoxy(WIDTH + j + 1, i);
			boardManager.DrawPixel(WIDTH + j + 1, HEIGHT / 2 + i - 1, boardManager.WELL);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			boardManager.DrawPixel(WIDTH + j + 2, HEIGHT / 2 + i, boardManager.EMPTY);
		}
		for (int j = 0; j < 6; j++)
		{
			boardManager.DrawPixel(WIDTH + j + 2, HEIGHT / 2 + i + 3, boardManager.EMPTY);
		}
	}

	//레벨 표시
	gotoxy(WIDTH + 2, HEIGHT / 2);
	cout << "    Level";

	//점수 표시
	gotoxy(WIDTH + 2, HEIGHT / 2 + 3);
	cout << "    Score";

	UpdateScore(info);
}

void UI::ShowNextBlock(int nextBlock[][4])
{
	//다음 블럭 표시 프레임
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//gotoxy(WIDTH + j + 1, i);
			boardManager.DrawPixel(WIDTH + j + 1, i, boardManager.WELL);
		}
	}

	//다음 블럭 표시 프레임
	UpdateNextBlock(nextBlock);
}

void UI::FillFrame()
{
	for (int i = 0; i < HEIGHT + 2; i++) 
	{
		for (int j = 0; j < WIDTH * 2 + 1; j++)
		{
			cout << "▩";
		}
		cout << endl;
	}
}

void UI::GameUI(Info info, int nextBlock[][4])
{
	FillFrame();
	ShowNextBlock(nextBlock);
	ShowScore(info);
}

void UI::UpdateScore(Info info)
{
	//레벨 표시
	gotoxy(WIDTH + 2, HEIGHT / 2 + 1);
	printf("%7d", info.level);

	//점수 표시
	gotoxy(WIDTH + 2, HEIGHT / 2 + 4);
	printf("%11d", info.score);
}

void UI::UpdateNextBlock(int nextBlock[][4])
{
	for (int i = 1; i < 7; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			//gotoxy(WIDTH + j + 1, i);
			boardManager.DrawPixel(WIDTH + j + 1, i, boardManager.EMPTY);
		}
	}

	boardManager.DrawNextBlock(nextBlock, { WIDTH + 3, 2 }, boardManager.BLOCK);
}

void UI::GameOver()
{
	system("cls");
	
	cout << "\n \n \n ";
	cout << "       ■■■" << endl
		<< "     ■" << endl
		<< "     ■            ■        ■  ■    ■■■" << endl
		<< "     ■    ■■  ■  ■    ■  ■  ■  ■  ■" << endl
		<< "     ■      ■  ■  ■    ■  ■  ■  ■■" << endl
		<< "       ■■■      ■■■  ■  ■  ■  ■■■" << endl;

	cout << "\n\n";
	cout << "          ■■■" << endl
		<< "         ■      ■" << endl
		<< "         ■      ■  ■  ■  ■■■  ■  ■" << endl
		<< "         ■      ■  ■  ■  ■  ■  ■■" << endl
		<< "         ■      ■  ■  ■  ■■    ■" << endl
		<< "           ■■■      ■    ■■■  ■" << endl;

	cout << "\n\n";
	cout << "            Press the R key to restart!!";
	cout << "                               ESC : Exit";
}