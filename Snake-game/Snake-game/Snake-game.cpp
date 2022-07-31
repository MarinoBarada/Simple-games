#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Snake
{
private:
	bool gameOver;
	int score;
	int width, height, headX, headY, fruitX, fruitY, nTail;
	int tailX[100], tailY[100];
	eDirection dir;
public:
	Snake();
	void Draw();
	void Input();
	void Logic();
	int BestScore(int prevScore);
	void Run();
	void Restart();
};

Snake::Snake()
{
	width = 20;
	height = 20;
	gameOver = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
}

void Snake::Draw()
{
	system("cls");
	cout << "\n\tThe snake moves using the buttons w a s d !";
	cout << "\n\tWhen ready click w or a or s or d !";
	cout << "\n\tExit the game by pressing the x button on keyboard!\n\n";
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == headY && j == headX)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "\tSCORE: " << score << endl;
}

void Snake::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Snake::Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;
	tailY[0] = headY;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case STOP:
		break;
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = true;
	if (headX >= width) headX = 0; else if (headX < 0) headX = width - 1;
	if (headY >= height) headY = 0; else if (headY < 0) headY = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == headX && tailY[i] == headY)
			gameOver = true;

	if (headX == fruitX && headY == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int Snake::BestScore(int prevScore)
{
	if (prevScore > score)
		return prevScore;
	else
		return score;
}

void Snake::Run()
{
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
}
void Snake::Restart()
{
	gameOver = false;
	dir = STOP;
	headX = width / 2;
	headY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
}

int main()
{
	Snake game;
	int entry, bestScore = 0;

	game.Run();
	bestScore = game.BestScore(bestScore);

	while (1)
	{
		cout << "\nDo you want to play again?\n1.YES\n2.NO\nEnter choice 1 or 2: ";
		cin >> entry;
		if (entry == 1)
		{
			game.Restart();
			game.Run();
			bestScore = game.BestScore(bestScore);
		}
		else if (entry == 2)
			break;
		else
			cout << "Incorrect input, try again!!!(enter 1 or 2)" << endl << endl;
	}

	system("cls");
	cout << "\n\tBEST SCORE: " << bestScore << endl << endl;;
	system("pause");
	return 0;
}