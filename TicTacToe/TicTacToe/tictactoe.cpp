#include <iostream>

using namespace std;

class TicTacToe
{
private:
	char player;
	char matrix[3][3];
	int win_player1, win_player2;
public:
	TicTacToe();
	void Draw();
	void Input();
	void TogglePlayer();
	char Win(char wining_player);
	void Run();
	void Restart();
	void Results();
};

TicTacToe::TicTacToe()
{
	player = 'X';
	char numb = '1';
	win_player1 = win_player2 = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = numb;
			numb++;
		}
}

void TicTacToe::Draw()
{
	system("cls");
	cout << "\tTic Tac Toe" << endl;
	cout << "Player1 -> X\nPlayer2 -> Y\n" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "\t";
		for (int j = 0; j < 3; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void TicTacToe::Input()
{
	int number;
	cout << "It's " << player << " turn. Press the number of the field: ";
	cin >> number;

	switch (number)
	{
	case 1:
		if (matrix[0][0] == '1')
			matrix[0][0] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 2:
		if (matrix[0][1] == '2')
			matrix[0][1] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 3:
		if (matrix[0][2] == '3')
			matrix[0][2] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 4:
		if (matrix[1][0] == '4')
			matrix[1][0] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 5:
		if (matrix[1][1] == '5')
			matrix[1][1] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 6:
		if (matrix[1][2] == '6')
			matrix[1][2] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 7:
		if (matrix[2][0] == '7')
			matrix[2][0] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 8:
		if (matrix[2][1] == '8')
			matrix[2][1] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	case 9:
		if (matrix[2][2] == '9')
			matrix[2][2] = player;
		else
		{
			cout << "Feild is already in use try again!" << endl;
			Input();
		}
		break;
	default:
		cout << "Incorrect input, try again!!!" << endl;
		Input();
		break;
	}
}

void TicTacToe::TogglePlayer()
{
	if (player == 'X')
		player = 'O';
	else
		player = 'X';
}

char TicTacToe::Win(char wining_player)
{
	//Rows
	if (matrix[0][0] == wining_player && matrix[0][1] == wining_player && matrix[0][2] == wining_player)
		return wining_player;
	if (matrix[1][0] == wining_player && matrix[1][1] == wining_player && matrix[1][2] == wining_player)
		return wining_player;
	if (matrix[2][0] == wining_player && matrix[2][1] == wining_player && matrix[2][2] == wining_player)
		return wining_player;

	//Columns
	if (matrix[0][0] == wining_player && matrix[1][0] == wining_player && matrix[2][0] == wining_player)
		return wining_player;
	if (matrix[0][1] == wining_player && matrix[1][1] == wining_player && matrix[2][1] == wining_player)
		return wining_player;
	if (matrix[0][2] == wining_player && matrix[1][2] == wining_player && matrix[2][2] == wining_player)
		return wining_player;

	//Diagonals
	if (matrix[0][0] == wining_player && matrix[1][1] == wining_player && matrix[2][2] == wining_player)
		return wining_player;
	if (matrix[2][0] == wining_player && matrix[1][1] == wining_player && matrix[0][2] == wining_player)
		return wining_player;

	return 'L';
}

void TicTacToe::Run()
{
	int n;
	char player1, player2;

	Draw();
	n = 0;
	while (1)
	{
		n++;
		Input();
		Draw();
		player1 = Win('X');
		player2 = Win('O');

		if (player1 == 'X')
		{
			cout << "\nPlayer1 WIN!!!" << endl;
			win_player1++;
			break;
		}
		else if (player2 == 'O')
		{
			cout << "\nPlayer2 WIN!!!" << endl;
			win_player2++;
			break;
		}
		else if (player1 == 'L' && player2 == 'L' && n == 9)
		{
			cout << "\nIt's a DRAW!!!" << endl;
			break;
		}
		TogglePlayer();
	}

	cout << "\nSCORE: " << endl;
	cout << "\tPlayer1 " << win_player1 << " vs Player2 " << win_player2 << endl;
}

void TicTacToe::Restart()
{
	TogglePlayer();
	char numb = '1';

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = numb;
			numb++;
		}
}

void TicTacToe::Results()
{
	cout << "\n\tFINAL SCORE:" << endl;
	cout << "\tPlayer1 " << win_player1 << "  Player2 " << win_player2 << endl << endl;
}

int main()
{
	int entry;
	TicTacToe match;
	match.Run();

	while (1)
	{
		cout << "\nDo you want to play again?\n1.YES\n2.NO\nEnter choice 1 or 2: ";
		cin >> entry;
		if (entry == 1)
		{
			match.Restart();
			match.Run();
		}
		else if (entry == 2)
			break;
		else
			cout << "Incorrect input, try again!!!(enter 1 or 2)" << endl << endl;
	}

	system("cls");
	match.Results();
	system("pause");
	return 0;
}