#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;


#define PUZZLE_WIDTH 3 /* DIMENSION OF PUZZLE (ex. 3 x 3) */


void print_vector(vector<int> &arg) {
	for(int i = 0; i < arg.size(); i++) {
		if( (arg.size() % i ) == 0 ) { cout << endl; }
		cout << arg.at(i) <<  " ";
	}
	cout << endl;
}


void default_puzzle() {
	cout << "You chose the deafult puzzle" << endl;
}


void custom_puzzle() {
	cout << "Enter your puzzle. Use 'x' as the blank space" << endl;
	int entry;
	vector<int> row;
	row.clear();
	vector<string> transitions = {"first", "second", "third"};
	string currentTransition;
	for(int k = 0; k < PUZZLE_WIDTH; k++) {
		if(k == 0) { currentTransition = transitions.at(k); }
		else if(k == 1) { currentTransition = transitions.at(k); }
		else if(k == 2) { currentTransition = transitions.at(k); }
		cout << "Enter the " << currentTransition
		     << " row (separate entries by space): ";
		for(int i = 0; i < PUZZLE_WIDTH; i++) {
			cin >> entry;
			if(entry < 1 || entry > 9) {
				cout << "Please enter numbers between 1 and 8" << endl;
				return;
			}
			row.push_back(entry);
		}
	}
	cout << endl << endl;
	cout << "      Puzzle" << endl;
	cout << "---------------------" << endl << "      ";
	print_vector(row);
}


void print_menu() {
	char userInput;
	char newline = '\n';
	cout << "Welcome to the 8-puzzle solver!" << endl;
	cout << "Designed and coded by Stavan Thaker" << endl;
	cout << "Please enter to continue or 'q' to quit.";
	cout << endl << ">> ";
	userInput = cin.get();
	if (userInput == 'q') { exit(0); }
	else if (userInput == '\n') {
		cout << endl;
		int puzzleChoice;
		cout << "Please choose from the following options." << endl;
		cout << "1. Choose default puzzle." << endl
		     << "2. Enter your own puzzle" << endl;
		cout << "Enter '1' or '2'";
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