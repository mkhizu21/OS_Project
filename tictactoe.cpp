#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

void tictac_animation() {
	string banner = R"(
 ____  __  ___    ____  __    ___    ____  __  ____ 
(_  _)(  )/ __)  (_  _)/ _\  / __)  (_  _)/  \(  __)
  )(   )(( (__     )( /    \( (__     )( (  O )) _) 
 (__) (__)\___)   (__)\_/\_/ \___)   (__) \__/(____)
)";

	cout << banner << endl << endl;
}
void printboard(int board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				cout << "_";
			else if (board[i][j] == 1)
				cout << "X";
			else
				cout << "O";
		}
		cout << endl;
	}
	cout << endl;
}
bool checkwinner(int board[3][3], int& who)
{
	if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != 0)
	{
		who = board[0][0];
		return true;
	}
	else if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != 0)
	{
		who = board[1][0];
		return true;
	}
	else if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != 0)
	{
		who = board[2][0];
		return true;
	}
	else if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != 0)
	{
		who = board[0][0];
		return true;
	}
	else if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != 0)
	{
		who = board[0][1];
		return true;
	}
	else if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != 0)
	{
		who = board[0][2];
		return true;
	}
	else if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0)
	{
		who = board[0][0];
		return true;
	}
	else if (board[0][2] == board[1][1] && board[0][0] == board[2][0] && board[0][2] != 0)
	{
		who = board[0][2];
		return true;
	}
	else
	{
		return false;
	}
}
void findloc(int board[3][3], int& row, int& col, int opp)
{
	bool winner = false;
	int who;
	for (int i = 0; i < 3 && winner == false; i++)
	{
		for (int j = 0; j < 3 && winner == false; j++)
		{
			if (board[i][j] == 0)
			{
				row = i;
				col = j;
				board[i][j] = opp;
				winner = checkwinner(board, who);
				board[i][j] = 0;
			}
		}
	}
}
void tictactoe()
{
	float n = 1;
	tictac_animation();
	bool winner = false;
	int board[3][3] = { 0 };
	printboard(board);
	int player = 1, row, col, who;
	for (int i = 0; i < 9 && winner == false; i++)
	{
		if (player == 1)
		{
			cout << "Enter row and column ::" << endl;
			cin >> row >> col;
			findloc(board, row, col, 2);
			board[row][col] = 1;
			player = 2;
		}
		else
		{
			cout << "Enter row and column ::" << endl;
			cin >> row >> col;
			while (board[row][col] != 0)
			{
				cout << "\nreenter\n";
				cin >> row >> col;
			}
			board[row][col] = 2;
			player = 1;
		}
		system("clear");
		tictac_animation();
		printboard(board);
		winner = checkwinner(board, who);
		if (winner)
		{
			cout << "The Winner Is Player# " << who << endl;
			sleep(5);
			system("clear");
		}
	}
}
int main()
{
	tictactoe();
	return 0;
}