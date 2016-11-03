#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;


#define PUZZLE_WIDTH 3 /* DIMENSION OF PUZZLE (ex. 3 x 3) */

struct Puzzle 
{
	vector<int> CURRENT_STATE;
	vector<int> GOAL_STATE = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /* GOAL STATE */

	int hn;
	int gn;
};



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
	cout << "\tPuzzle" << endl;
	cout << "-----------------------" << endl << "\t";
	for(int i = 0; i < arg.size(); i++) {
		if( ( i != 0 ) && ((i % PUZZLE_WIDTH) == 0) ) { cout << endl << "\t"; }
		cout << arg.at(i) << spaceBetweenEntries;
	}
	cout << endl;
}



/* ----------------------------------------------------------------------------- */

/* bp = position of blank*/
bool isLeftWall(int bp) {	
	if(bp == 0 || bp == 3 || bp == 6) {
		return true;
	}
	else { return false; }
}


bool isRightWall(int bp) {
	if(bp == 2 || bp == 5 || bp == 8) {
		return true;
	}
	else {return false; }
}



bool isTopWall(int bp) {
	if(bp == 0 || bp == 1 || bp == 2) {
		return true;
	}
	else {return false; }
}



bool isBottomWall(int bp) {
	if(bp == 6 || bp == 7 || bp == 8) {
		return true;
	}
	else {return false; }
}


/* ----------------------------------------------------------------------------- */

/* Finds location of blank */
int find_blank(vector<int> &state) {
	for(int i = 0; i < state.size(); i++){
		if(state.at(i) == 0) {
			return i; 
		}
	}
}

/* move blank space LEFT  */
void move_left(vector<int> &state) {
	int blank = find_blank(state);

	/* IF blank space is NOT on left wall*/
	if(!isLeftWall(blank)) {
		cout << "\nMoving left..." << endl;
		swap(state.at(blank), state.at(blank-1));
	}
	else {
		cout << endl << "Left wall, cannot move it." << endl;
	}
	print_vector(state);
}


/* move blank space RIGHT */
void move_right(vector<int> &state) {
	int blank = find_blank(state);

	/* IF blank space is NOT on right wall*/
	if(!isRightWall(blank)) {
		cout << "\nMoving right..." << endl;
		swap(state.at(blank), state.at(blank+1));
	}
	else {
		cout << endl << "Right wall, cannot move it." << endl;
	}
	print_vector(state);
}


/* move blank space UP */
void move_up(vector<int> &state) {
	int blank = find_blank(state);

	/* IF blank space is NOT on top wall*/
	if(!isTopWall(blank)) {
		cout << "\nMoving up..." << endl;
		int index_above = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) - 1 ) + (blank % PUZZLE_WIDTH));
		swap(state.at(blank), state.at(index_above));
	}
	else {
		cout << endl << "Top wall, cannot move it." << endl;
	}
	print_vector(state);
}


/* move blank space DOWN */
void move_down(vector<int> &state) {
	int blank = find_blank(state);

	/* IF blank space is NOT on bottom wall*/
	if(!isBottomWall(blank)) {
		cout << "\nMoving down..." << endl;
		int index_below = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) + 1 ) + (blank % PUZZLE_WIDTH));
		swap(state.at(blank), state.at(index_below));
	}
	else {
		cout << endl << "Bottom wall, cannot move it." << endl;
	}
	print_vector(state);
}


/* ----------------------------------------------------------------------------- */

void uniform_cost(vector<int> &state) {
	move_up(state);
	move_up(state);
	move_left(state);
	move_left(state);
	move_down(state);
	move_down(state);
	move_down(state);
}


void misplaced_tile() {
	cout << endl << "you chose misplaced_tile" << endl;
}


void manhatatan_distance() {
	cout << endl << "you chose manhatatan_distance" << endl;
}

/* ----------------------------------------------------------------------------- */



vector<int> default_puzzle() {
	/* dp = the default puzzle*/
	vector<int> dp = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	cout << "DEFAULT PUZZLE: " << endl;
	print_vector(dp);
	return dp;
}


vector<int> custom_puzzle() {
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
	return table;
}


int choose_search() {
	int algorithm_choice;
	cout << endl << endl;
	cout << "Enter your choice of algorithm" << endl;
	cout << "1. Uniform Cost Search" << endl;
	cout << "2. A* with the Misplaced Tile Heuristic" << endl;
	cout << "3. A* with the Manhattan Distance Heuristic" << endl;
	cout << endl << ">> ";
	cin >> algorithm_choice;
	return algorithm_choice;
}

void start() {
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

		Puzzle P; /* Starting puzzle node */

		int puzzleChoice;
		cout << "Please choose from the following options." << endl;
		cout << "1. Choose default puzzle." << endl
		     << "2. Enter your own puzzle" << endl;
		cout << endl << ">> ";

		cin >> puzzleChoice;

		if(puzzleChoice == 1) {
			cout << endl;
			P.CURRENT_STATE = default_puzzle();
		}
		else if (puzzleChoice == 2) {
			cout << endl;
			P.CURRENT_STATE = custom_puzzle();
			cout << "SIZE OF PUZZLE: " << P.CURRENT_STATE.size() << endl << endl;
		}
		else {
			cout << "Please choose option '1' or '2'" << endl;
			return;
		}

		int search_choice = choose_search();
		switch(search_choice) {
			case 1:
				uniform_cost(P.CURRENT_STATE);
				break;
			case 2:
				misplaced_tile();
				break;
			case 3:
				manhatatan_distance();
				break;
			default:
				cout << "\t\t***** ERROR *****" << endl;
				cout << "\tBad input, quitting..." << endl;
				break;
		}

	}
}

int main() {
	start();
	return 0;
}