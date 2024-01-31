#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

using namespace std;

void saveToFile(const string& filename, const string& content, bool append = false) {
	ofstream outfile;
	if (append) {
		outfile.open(filename, ios::app);
	}
	else {
		outfile.open(filename);
	}
	if (!outfile.is_open()) {
		cerr << "Unable to open file " << filename << endl;
		exit(EXIT_FAILURE);
	}
	outfile << content;
	outfile.close();
}

void openFile(const string& filename, bool editMode) {
	if (editMode) {
		system(("notepad " + filename).c_str());
	}
	else {
		ifstream infile(filename);
		if (!infile.is_open()) {
			cerr << "Unable to open file " << filename << endl;
			return;
		}
		string line;
		while (getline(infile, line)) {
			cout << line << endl;
		}
		infile.close();
	}
}

void deleteFile(const string& filename) {
	if (remove(filename.c_str()) != 0) {
		cerr << "Unable to delete file " << filename << endl;
		exit(EXIT_FAILURE);
	}
}

void printMenu() {
	cout << "\n";
	cout << "1. Create a new file and write to it\n";
	cout << "2. Open an existing file in view mode\n";
	cout << "3. Open an existing file in edit mode\n";
	cout << "4. Delete a file\n";
	cout << "5. Exit\n";
}

int main() {
	int choice;
	string filename, content;

	do {
		system("clear");
		printMenu();
		cout << "Enter Your Choice : ";
		cin >> choice;
		system("clear");

		switch (choice) {
		case 1:
			// Receive text input from the console
			cout << "Enter Some Text : ";
			cin.ignore();
			getline(cin, content);

			// Save the text to a new file
			cout << "Enter The File Name : ";
			getline(cin, filename);
			saveToFile(filename, content);
			break;
		case 2:
			// Open an existing file in view mode
			cout << "Enter The File Name To Open : ";
			cin >> filename;
			openFile(filename, false);
			cout << "Press Enter to continue..... " << endl;
            cin>> filename;
			break;
		case 3:
			// Open an existing file in edit mode
			cout << "Enter The File Name To Open : ";
			cin >> filename;
			openFile(filename, true);
			sleep(5);
			break;
		case 4:
			// Delete a file
			cout << "Enter The File Name To Be Delete : ";
			cin >> filename;
			deleteFile(filename);
			break;
		case 5:
			// Exit the program
			cout << "Exiting Program...\n";
			break;
		default:
			cerr << "Invalid Choice!" << endl;
		}
	} while (choice != 5);

	return 0;
}