#include <unistd.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include<iomanip>
#include <fstream>
#include <stdio.h>
using namespace std;

char arr[9][9];
int points = 0;

void movement(int& r, int& c, int key)
{
	//switch (key)
	//{
		// UP
	if(key == 'w' || key == 'W')
	{

		r--;
		if (r < 0)
		{
			r = 8;
		}
		//break;
	}
	// DOWN
	if(key == 's' || key == 'S')
	{

		r++;
		if (r > 8)
		{
			r = 0;
		}
		//break;
	}
	// LEFT
	if(key == 'a' || key == 'A')
	{
		c--;
		if (c < 0)
		{
			c = 8;
		}
		//break;
	}
	// RIGHT
	if(key == 'd' || key == 'D')
	{
		c++;
		if (c > 8)
		{
			c = 0;
		}
		//break;
	}
	//}
}

void candy_animation() {
	cout << "\n\t\t\t   _____                _          _____                _     " << endl;
	cout << "\t\t\t  / ____|              | |        / ____|              | |    " << endl;
	cout << "\t\t\t | |     __ _ _ __   __| |_   _  | |     _ __ _   _ ___| |__  " << endl;
	cout << "\t\t\t | |    / _` | '_ \\ / _` | | | | | |    | '__| | | / __| '_ \\ " << endl;
	cout << "\t\t\t | |___| (_| | | | | (_| | |_| | | |____| |  | |_| \\__ \\ | | |" << endl;
	cout << "\t\t\t  \\_____\\__,_|_| |_|\\__,_|\\__, |  \\_____|_|   \\__,_|___/_| |_|" << endl;
	cout << "\t\t\t                           __/ |                              " << endl;
	cout << "\t\t\t                          |___/                               " << endl;
	system("pause");
	cout << endl << endl << "Press Any Key To Continue!" << endl;
}

void print_grid(int row, int col, char easyboard[9][9]) {

	int i = 0;
	int  j = 0;
	int k = 0;
	system("clear");
	cout << "\t\tPress E to exit." << endl;
	cout << "\n\t\tUse the WASD and enter keys to move." << endl;
	cout << "\n\t\tPress F and enter to select any candy." << endl;
	cout << "\n\t\tPoints : " << points << "\n\n";
	cout << "\t\t";
	for (i = 0; i < 81; i++) {
		cout << static_cast<char>(219);
	}

	cout << endl;

	for (k = 0; k < 3; k++) {
		cout << "\t\t" << static_cast<char>(219) << "\t\t\t\t\t\t\t\t\t\t" << static_cast<char>(219) << endl;
	}
	for (i = 0; i < 9; i++) {
		cout << "\t\t" << static_cast<char>(219) << "\t";
		for (j = 0; j < 9; j++) {
			if (j == col && i == row) {
				cout << easyboard[i][j] << " <--   ";
			}
			else {
				cout << easyboard[i][j] << "\t";
			}
		}
		cout << static_cast<char>(219) << endl;
		for (k = 0; k < 3; k++) {
			cout << "\t\t" << static_cast<char>(219) << "\t\t\t\t\t\t\t\t\t\t" << static_cast<char>(219) << endl;
		}
	}
	cout << "\t\t";


	for (i = 0; i < 81; i++) {
		cout << static_cast<char>(219);
	}
	cout << endl << endl << endl;

}

void display_invalid_move(int r, int c)
{
	system("clear");
	print_grid(r, c, arr);
	cout << "\n\t\t!!!!!!!!!!!!!!!!!!!!!!!!! INVALID MOVE !!!!!!!!!!!!!!!!!!!!!!!!!";
	sleep(1);
}

void swap(int r1, int c1, int r2, int c2)
{
	char temp;

	temp = arr[r1][c1];
	arr[r1][c1] = arr[r2][c2];
	arr[r2][c2] = temp;
}

void swap_candies(int& r, int& c, int key)
{
	//switch (key)
	//{
		// UP
	if(key == 'w' || key == 'W')
	{

		if (r != 0)
		{
			swap(r, c, r - 1, c);
		}
		else
		{
			display_invalid_move(r, c);
		}
		//break;
	}
	// DOWN
	if(key == 'S' || key == 's')
	{

		if (r != 8)
		{
			swap(r, c, r + 1, c);
		}
		else
		{
			display_invalid_move(r, c);
		}
		//break;
	}
	// LEFT
	if(key == 'a' || key == 'A')
	{

		if (c != 0)
		{
			swap(r, c, r, c - 1);
		}
		else
		{
			display_invalid_move(r, c);
		}
		//break;
	}
	// RIGHT
	if(key == 'd' || key == 'D')
	{
		if (c != 8)
		{
			swap(r, c, r, c + 1);
		}
		else
		{
			display_invalid_move(r, c);
		}
		//break;
	}
	
}

//The function rnd3 scans the whole board in easy mode repeatedly for any possible matches (3 in a row). This function also shows the matches by a blinking animation and indicates through bool if a match is found or not.

void check3candies(int r, int c, bool& match, char easyboard[9][9]) {

	int i, j;
	char temp1, temp2, temp3;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
		{
			if ((easyboard[i][j] == easyboard[i + 1][j]) && (easyboard[i][j] == easyboard[i + 2][j])) {
				temp1 = easyboard[i][j];
				temp2 = easyboard[i + 1][j];
				temp3 = easyboard[i + 2][j];

				for (int k = 2; k > 0; k--)
				{
					easyboard[i][j] = static_cast<char>(219);
					easyboard[i + 1][j] = static_cast<char>(219);
					easyboard[i + 2][j] = static_cast<char>(219);
					print_grid(r, c, arr);
					cout << "\t\tSweet\n";
					sleep(0.6);
					easyboard[i][j] = temp1;
					easyboard[i + 1][j] = temp2;
					easyboard[i + 2][j] = temp3;
					print_grid(r, c, arr);
					cout << "\t\tSweet\n";
					sleep(0.6);
				}

				easyboard[i][j] = rand() % 8 + 65;

				easyboard[i + 1][j] = rand() % 8 + 65;
				do
				{
					easyboard[i + 2][j] = rand() % 8 + 65;

				} while ((easyboard[i][j] == easyboard[i + 1][j]) && (easyboard[i][j] == easyboard[i + 2][j]));

				match = true;
				points = points + 10;
				i = 0; j = 0;
			}
			else {
				if (j < 7) {
					if ((easyboard[i][j] == easyboard[i][j + 1]) && (easyboard[i][j] == easyboard[i][j + 2])) {
						temp1 = easyboard[i][j];
						temp2 = easyboard[i][j + 1];
						temp3 = easyboard[i][j + 2];

						for (int k = 2; k > 0; k--) {
							easyboard[i][j] = static_cast<char>(219);
							easyboard[i][j + 1] = static_cast<char>(219);
							easyboard[i][j + 2] = static_cast<char>(219);
							print_grid(r, c, arr);
							cout << "\t\tSweet\n";
							sleep(0.6);
							easyboard[i][j] = temp1;
							easyboard[i][j + 1] = temp2;
							easyboard[i][j + 2] = temp3;
							print_grid(r, c, arr);
							cout << "\t\tSweet\n";
							sleep(0.6);
						}

						easyboard[i][j] = rand() % 8 + 65;
						easyboard[i][j + 1] = rand() % 8 + 65;
						do {
							easyboard[i][j + 2] = rand() % 8 + 65;
						} while ((easyboard[i][j] == easyboard[i][j + 1]) && (easyboard[i][j] == easyboard[i][j + 2]));

						match = true;
						points = points + 10;
						i = 0; j = 0;
					}
				}
			}
		}
	}
}

void check4candies(int r, int c, bool& match, char easyboard[9][9]) {

	int i, j;
	char temp1, temp2, temp3, temp4;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++)
		{
			if ((easyboard[i][j] == easyboard[i + 1][j]) && (easyboard[i][j] == easyboard[i + 2][j]) && (easyboard[i][j] == easyboard[i + 3][j])) {
				temp1 = easyboard[i][j];
				temp2 = easyboard[i + 1][j];
				temp3 = easyboard[i + 2][j];
				temp4 = easyboard[i + 3][j];

				for (int k = 2; k > 0; k--)
				{
					easyboard[i][j] = static_cast<char>(219);
					easyboard[i + 1][j] = static_cast<char>(219);
					easyboard[i + 2][j] = static_cast<char>(219);
					easyboard[i + 3][j] = static_cast<char>(219);
					print_grid(r, c, arr);
					cout << "\t\tSweet\n";
					sleep(0.6);
					easyboard[i][j] = temp1;
					easyboard[i + 1][j] = temp2;
					easyboard[i + 2][j] = temp3;
					easyboard[i + 3][j] = temp4;
					print_grid(r, c, arr);
					cout << "\t\tSweet\n";
					sleep(0.6);
				}

				easyboard[i][j] = rand() % 8 + 65;

				easyboard[i + 1][j] = rand() % 8 + 65;
				do
				{
					easyboard[i + 2][j] = rand() % 8 + 65;

				} while ((easyboard[i][j] == easyboard[i + 1][j]) && (easyboard[i][j] == easyboard[i + 2][j]));

				match = true;
				points = points + 20;
				i = 0; j = 0;
			}
			else {
				if (j < 7) {
					if ((easyboard[i][j] == easyboard[i][j + 1]) && (easyboard[i][j] == easyboard[i][j + 2]) && (easyboard[i][j] == easyboard[i][j + 3])) {
						temp1 = easyboard[i][j];
						temp2 = easyboard[i][j + 1];
						temp3 = easyboard[i][j + 2];
						temp4 = easyboard[i][j + 3];

						for (int k = 2; k > 0; k--) {
							easyboard[i][j] = static_cast<char>(219);
							easyboard[i][j + 1] = static_cast<char>(219);
							easyboard[i][j + 2] = static_cast<char>(219);
							easyboard[i][j + 3] = static_cast<char>(219);
							print_grid(r, c, arr);
							cout << "\t\tSweet\n";
							sleep(0.6);
							easyboard[i][j] = temp1;
							easyboard[i][j + 1] = temp2;
							easyboard[i][j + 2] = temp3;
							easyboard[i][j + 3] = temp3;
							print_grid(r, c, arr);
							cout << "\t\tSweet\n";
							sleep(0.6);
						}

						easyboard[i][j] = rand() % 8 + 65;
						easyboard[i][j + 1] = rand() % 8 + 65;
						do
						{
							easyboard[i][j + 2] = rand() % 8 + 65;
						} while ((easyboard[i][j] == easyboard[i][j + 1]) && (easyboard[i][j] == easyboard[i][j + 2]));

						do
						{
							easyboard[i][j + 3] = rand() % 8 + 65;
						} while ((easyboard[i][j + 1] == easyboard[i][j + 2]) && (easyboard[i][j + 1] == easyboard[i][j + 3]));



						match = true;

						points = points + 20;
						i = 0; j = 0;
					}
				}
			}
		}
	}
}


void candy_runner()
{
	int key, r = 0, c = 0;
	bool match = false, flag = true;
	string name;
	char choice;

	candy_animation();
	system("clear");
	cin.ignore();
	cout << "Enter Your Name : ";
	getline(cin, name);
	system("clear");
	do {
		cout << "Press P To Play : ";
		cin >> choice;
		system("clear");
	} while (choice != 'P' && choice != 'p');
	for (int s = 5; s != 0; s--)
		cout << "		Maximize Your Screen         ";
	system("clear");
	srand(time(0));

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr[i][j] = rand() % 8 + 65;
		}
	}

	check3candies(r, c, match, arr);
	check4candies(r, c, match, arr);
	points = 0;


	// INFINITELY CHECKS KEYBOARD INPUT
	while (flag)
	{
		match = false;
		print_grid(r, c, arr);

		key = getchar();

		if (key == 'f')
		{

			system("clear");
			print_grid(r, c, arr);
			cout << "\n\t\tUse the WASD and enter keys to swap the candy." << endl;
			key = getchar();
			if (key == 'g')
			{
				key = getchar();
				swap_candies(r, c, key);
				check4candies(r, c, match, arr);
				if (match == false)
				{
					check3candies(r, c, match, arr);
					if (match == false)
					{
						swap_candies(r, c, key);
					}
				}
			}
		}
		if (key == 's' || key == 'w' || key == 'a' || key == 'd')
		{
			key = getchar();
			movement(r, c, key);
		}
		if (key == 'e' || key == 'E') {
			flag = false;
		}
	}
	system("clear");
	cout << fixed << setw(20) << "You Scored : " << points << endl;
	sleep(5);
	system("clear");
}

int main()
{
	candy_runner();
	return 0;
}