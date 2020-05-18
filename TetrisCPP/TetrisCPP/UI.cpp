#include "UI.h"

UI::UI()
{
	system("mode con cols=50 lines=24");
	isRecord = false;
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

	//다음 블럭 표시
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

void UI::StartUI()
{
	int speed = 50;
	cout << "\n\n\n";
	cout << "  ■■■■■                        ■        " << endl;
	Sleep(speed);
	cout << "      ■              ■    ■  ■        ■■" << endl;
	Sleep(speed);
	cout << "      ■    ■■■  ■■■  ■■    ■  ■    " << endl;
	Sleep(speed);
	cout << "      ■    ■  ■    ■    ■      ■    ■  " << endl;
	Sleep(speed);
	cout << "      ■    ■■      ■    ■      ■      ■" << endl;
	Sleep(speed);
	cout << "      ■    ■■■    ■    ■      ■  ■■  " << endl;
	
	cout << "\n\n";
	Sleep(speed);
	cout << "              ■■■  ■■■    ■■■    " << endl;
	Sleep(speed);
	cout << "            ■        ■    ■  ■    ■  " << endl;
	Sleep(speed);
	cout << "            ■        ■■■    ■■■    " << endl;
	Sleep(speed);
	cout << "            ■        ■        ■        " << endl;
	Sleep(speed);
	cout << "              ■■■  ■        ■        " << endl;

	cout << "\n\n";
	Sleep(speed);
	cout << "              Thank yor for Playing!!" << endl;
	cout << "\n                  Enter to Start" << endl;
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

void UI::ShowRank()
{
	system("cls");

	IOManger io;
	vector<Score> score = io.LoadScore();

	sort(score.begin(), score.end(), compare);

	/*for (auto it = score.begin(); it != score.end(); it++)
	{
		cout << (*it).name << " " << (*it).score << endl;
	}*/
	
	for (int i = 0; i < WIDTH - 2; i++)
		cout << "■";
	cout << " Ranking  ";
	for (int i = 0; i < WIDTH - 2; i++)
		cout << "■";
	cout << endl;

	cout << "| Rank |         Name          |      Score      |" << endl;
	for (int i = 0; i < WIDTH * 2 + 1; i++)
		cout << "--";
	cout << endl;
	for (int i = 0; i < score.size() && i < 10; i++)
	{
		//cout << "■ ";
		cout << "| " << setw(3) << i + 1 << ". |";
		cout << setw(20) << score[i].name << "   |";
		cout << setw(14) << score[i].score << "   |" << endl;
		//cout << " ■" << endl;

		for (int i = 0; i < WIDTH * 2 + 1; i++)
			cout << "--";
		cout << endl;
	}
	cout << "                   ← : Return";

	while (1) {
		int key = _getch();
		if (key == BSPACE)
			return;
	}
}

void UI::SetIsRecord(bool flag)
{
	isRecord = flag;
}

void UI::GameOver(Info info)
{
	int speed = isRecord? 0 : 700;
	system("cls");
	
	cout << "\n";
	cout << "       ■■■" << endl
		<< "     ■" << endl
		<< "     ■            ■        ■  ■    ■■■" << endl
		<< "     ■    ■■  ■  ■    ■  ■  ■  ■  ■" << endl
		<< "     ■      ■  ■  ■    ■  ■  ■  ■■" << endl
		<< "       ■■■      ■■■  ■  ■  ■  ■■■" << endl;

	Sleep(speed);
	cout << "\n";
	cout << "           ■■■" << endl
		<< "         ■      ■" << endl
		<< "         ■      ■  ■  ■  ■■■  ■  ■" << endl
		<< "         ■      ■  ■  ■  ■  ■  ■■" << endl
		<< "         ■      ■  ■  ■  ■■    ■" << endl
		<< "           ■■■      ■    ■■■  ■" << endl;

	Sleep(speed);
	cout << "\n";
	cout << "                     Level : " << info.level << endl;
	cout << "                     Score : " << info.score << endl;

	if (!isRecord)
	{
		Sleep(speed);
		string name;
		cout << "\n                     Name : ";
		cin >> name;

		IOManger io;
		if (io.SaveScore(name, info))
		{
			cout << "                   Record complete!" << endl;
			isRecord = true;
		}
		else
		{
			cout << "                  Recording failure.." << endl;
			isRecord = true;
		}
	}

	Sleep(speed);
	cout << "\n            Press the R key to restart!!" << endl;
	cout << "               S : Show Rank  ESC : Exit";
}