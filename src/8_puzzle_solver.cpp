#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;


#define PUZZLE_WIDTH 3 /* DIMENSION OF PUZZLE (ex. 3 x 3) */

void print_v(vector<int> v) {
	cout << endl;
	for(int i = 0; i < v.size(); i++) {
		cout << v.at(i) << " ";
	}
	cout << endl;
}


void print_vector(vector<int> &arg) {
	string spaceBetweenEntries = "  ";

	cout << endl << endl;
	cout << "SIZE OF PUZZLE: " << arg.size() << endl << endl;
	cout << "\tPuzzle" << endl;
	cout << "-----------------------" << endl << "\t";
	for(int i = 0; i < arg.size(); i++) {
		if( ( i != 0 ) && ((i % PUZZLE_WIDTH) == 0) ) { cout << endl << "\t"; }
		cout << arg.at(i) << spaceBetweenEntries;
	}
	cout << endl;
}


void default_puzzle() {
	cout << "You chose the deafult puzzle" << endl;
}


void custom_puzzle() {
	cout << "Enter your puzzle. Use '0' as the blank space" << endl;
	int entry;
	vector<int> table;
	table.clear();
	vector<int> buffer;
	buffer.clear();
	vector<string> transitions = {"first", "second", "third"};
	string currentTransition;


	for(int row = 0; row < PUZZLE_WIDTH; row++) {
		if(row == 0) { currentTransition = transitions.at(row); }
		else if(row == 1) { currentTransition = transitions.at(row); }
		else if(row == 2) { currentTransition = transitions.at(row); }
		cout << "Enter the " << currentTransition
		     << " row (separate entries by space): ";
		for(int rowBufferIndex = 0; rowBufferIndex < PUZZLE_WIDTH; rowBufferIndex++) {
			cin >> entry;
			buffer.push_back(entry);

			if(rowBufferIndex == 2) {
				for(int i = 0; i < buffer.size(); i++) {
					if(buffer.at(i) < 0 || buffer.at(i) >= 9) {
						cout << endl << endl << "\t\t***** ERROR *****" << endl;
						cout << "\tPlease enter numbers between 1 and 8." << endl;
						cout << "\tRemember to use '0' as the blank space." << endl << endl;

						rowBufferIndex = PUZZLE_WIDTH;
						row -= 1;
						buffer.clear();
					}
				}
			}
		}
		table.insert(table.end(), buffer.begin(), buffer.end() );
		buffer.clear();
	}

	print_vector(table);
}


void print_menu() {
	char userInput;
	char newline = '\n';
	cout << "Welcome to the 8-puzzle solver!" << endl;
	cout << "Designed and coded by Stavan Thaker" << endl;
	cout << "Please enter to continue or 'q' to quit. ";
	//cout << endl << ">> ";
	userInput = cin.get();
	if (userInput == 'q') { exit(0); }
	else if (userInput == '\n') {
		cout << endl;
		int puzzleChoice;
		cout << "Please choose from the following options." << endl;
		cout << "1. Choose default puzzle." << endl
		     << "2. Enter your own puzzle" << endl;
		cout << endl << ">> ";

		cin >> puzzleChoice;

		if(puzzleChoice == 1) {
			cout << endl;
			default_puzzle();
		}
		else if (puzzleChoice == 2) {
			cout << endl;
			custom_puzzle();
		}
		else {
			cout << "Please choose option '1' or '2'" << endl;
			return;
		}
	}
}

int main() {
	print_menu();
	return 0;
}