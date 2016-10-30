#include <iostream>
#include <stdlib.h>
using namespace std;


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
		cout << "Please choose from the following options." << endl;
		cout << "1. Choose default puzzle." << endl << "2. Enter your own puzzle" << endl;
		//User input to vector table function 
	}
}

int main() {
	char userInput;
	/*while(userInput != 'q') {
		if(userInput != 'q' && userInput == '\n') {
			cout << "Enter the first row.";
			cout << "Please enter each number followed by a newline" << endl;
			int a, b, c;
			cin >> a;
			cin >> b;
			cin >> c;
			cout << "Your choices are: " << a << b << c << endl;
			break;
		}
	}*/
	while(1) {
		print_menu();
	}
	return 0;
}