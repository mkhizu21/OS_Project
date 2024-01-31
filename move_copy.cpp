#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>


using namespace std;

void move_file(const string& source_path, const string& destination_path) {
	if (rename(source_path.c_str(), destination_path.c_str()) == 0) {
		cout << "File Moved Successfuly!" << endl;
	}
	else {
		cout << "File Can Not Be Moved!" << endl;
	}
}


int main() {
	string source_add, dest_add, source_name, dest_name;
	int opt;

	do {
		system("clear");
		cout << "1) Move File" << endl;
		cout << "2) Copy File" << endl;
		cout << "3) Exit" << endl;
		cout << "Enter Here : ";
		cin >> opt;
		system("clear");
		switch (opt) {
		case 1: {
			cin.ignore();
			cout << "Enter Source Address : ";
			getline(cin, source_add);
			cout << "Enter Source Name : ";
			cin >> source_name;
			cout << "Enter Destination Address : ";
			cin.ignore();
			getline(cin, dest_add);
			source_add += "/" + source_name + ".txt";
			dest_add += "/" + source_name + ".txt";
			move_file(source_add, dest_add);
			cout << "Press Any Key To Continue!" << endl;
			string ok;
			cin >> ok;
			break;
		}
		case 2: {
			cin.ignore();
			cout << "Enter Source Address : ";
			getline(cin, source_add);
			cout << "Enter Source Name : ";
			cin >> source_name;
			cout << "Enter Destination Address : ";
			cin.ignore();
			getline(cin, dest_add);
			cout << "Enter Destination Name : ";
			cin >> dest_name;
			source_add += "/" + source_name + ".txt";
			dest_add += "/" + dest_name + ".txt";

			try {
				ifstream source_file(source_add);
				ofstream target_file(dest_add);
				target_file << source_file.rdbuf();
				cout << "File Copied Successfully!" << endl;
			}
			catch (const std::exception& e) {
				cerr << "Error! Copying The File : " << e.what() << std::endl;
				return 1;
			}
            cout << "Press Any Key To Continue!" << endl;
			string ok;
			cin >> ok;
			break;
		}
		case 3: {
			cout << "Exiting..." << endl;
			break;
		}
		default: {
			cout << "Invalid Input!" << endl;
			break;
		}
		}
	} while (opt != 3);

	return 0;
}