#include <cmath>
#include <queue>
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


class Cost_Comparator {
public:
	bool operator()(Puzzle &P1, Puzzle &P2){
		return ( (P1.hn + P1.gn) > (P2.hn + P2.gn) );
	}
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
void move_left(Puzzle &P) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on left wall*/
	if(!isLeftWall(blank)) {
		cout << "\nMoving left..." << endl;
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(blank-1));
	}
	else {
		cout << endl << "Left wall, cannot move it." << endl;
	}
	print_vector(P.CURRENT_STATE);
}


/* move blank space RIGHT */
void move_right(Puzzle &P) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on right wall*/
	if(!isRightWall(blank)) {
		cout << "\nMoving right..." << endl;
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(blank+1));
	}
	else {
		cout << endl << "Right wall, cannot move it." << endl;
	}
	print_vector(P.CURRENT_STATE);
}


/* move blank space UP */
void move_up(Puzzle &P) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on top wall*/
	if(!isTopWall(blank)) {
		cout << "\nMoving up..." << endl;
		int index_above = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) - 1 ) + (blank % PUZZLE_WIDTH));
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(index_above));
	}
	else {
		cout << endl << "Top wall, cannot move it." << endl;
	}
	print_vector(P.CURRENT_STATE);
}


/* move blank space DOWN */
void move_down(Puzzle &P) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on bottom wall*/
	if(!isBottomWall(blank)) {
		cout << "\nMoving down..." << endl;
		int index_below = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) + 1 ) + (blank % PUZZLE_WIDTH));
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(index_below));
	}
	else {
		cout << endl << "Bottom wall, cannot move it." << endl;
	}
	print_vector(P.CURRENT_STATE);
}


/* ----------------------------------------------------------------------------- */

void misplaced_tile(Puzzle &P) {
	P.hn = 0;
	if(P.CURRENT_STATE.at(0) != 1) { P.hn++; }
	if(P.CURRENT_STATE.at(1) != 2) { P.hn++; }
	if(P.CURRENT_STATE.at(2) != 3) { P.hn++; }
	if(P.CURRENT_STATE.at(3) != 4) { P.hn++; }
	if(P.CURRENT_STATE.at(4) != 5) { P.hn++; }
	if(P.CURRENT_STATE.at(5) != 6) { P.hn++; }
	if(P.CURRENT_STATE.at(6) != 7) { P.hn++; }
	if(P.CURRENT_STATE.at(7) != 8) { P.hn++; }
	//if(P.CURRENT_STATE.at(8) != 0) { P.hn++; }
	cout << "Misplaced Heuristic: " << P.hn << endl;
}


void manhatatan_distance(Puzzle &P) {
	P.hn = 0;
	int x, y;
	for(int index = 0; index < P.CURRENT_STATE.size(); index++) {
		if(index == 0) {
			x = 0;
			y = 0;
		}
		else if(index == 1) {
			x = 0;
			y = 1;
		}
		else if(index == 2) {
			x = 0;
			y = 2;
		}
		else if(index == 3) {
			x = 1;
			y = 0;
		}
		else if(index == 4) {
			x = 1;
			y = 1;
		}
		else if(index == 5) {
			x = 1;
			y = 2;
		}
		else if(index == 6) {
			x = 2;
			y = 0;
		}
		else if(index == 7) {
			x = 2;
			y = 1;
		}
		else if(index == 8) {
			x = 2;
			y = 2;
		}

		int curr_value = P.CURRENT_STATE.at(index);
		if(curr_value != 0) {
			int goal_row = (curr_value - 1) / PUZZLE_WIDTH;
			int goal_col = (curr_value - 1) % PUZZLE_WIDTH;
			P.hn += abs(x - goal_row) + abs(y - goal_col);
			}

	}
	cout << "manhatatan_distance: " << P.hn << endl;
}


void expand_puzzle(Puzzle &puzzle, priority_queue<Puzzle,vector<Puzzle>, Cost_Comparator> &nodes_queue)  {
	/* CP = Child Puzzle */
	Puzzle cp1;
	Puzzle cp2;
	Puzzle cp3;
	Puzzle cp4;

	/* Copy the puzzle's current state in 4 different puzzles */
	cp1.CURRENT_STATE = puzzle.CURRENT_STATE;
	cp2.CURRENT_STATE = puzzle.CURRENT_STATE;
	cp3.CURRENT_STATE = puzzle.CURRENT_STATE;
	cp4.CURRENT_STATE = puzzle.CURRENT_STATE;


	/* find blank space */
	find_blank(puzzle.CURRENT_STATE);


	//IF STATEMENTS

}




/* ----------------------------------------------------------------------------- */



vector<int> default_puzzle() {
	/* dp = the default puzzle*/
	// vector<int> dp = {1, 2, 3, 4, 5, 6, 7, 0, 8};
	vector<int> dp = {3, 2, 8, 4, 5, 6, 7, 1, 0};
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
				P.hn = 0;
				break;
			case 2:
				misplaced_tile(P);
				break;
			case 3:
				manhatatan_distance(P);
				break;
			default:
				cout << "\t\t***** ERROR *****" << endl;
				cout << "\tBad input, quitting..." << endl;
				break;
		}

		priority_queue<Puzzle, vector<Puzzle>, Cost_Comparator> nodes_queue;


		nodes_queue.push(P);

		cout << endl << "Expanding...";
		print_vector(P.CURRENT_STATE);

		/*while(!nodes_queue.empty()) {

		}*/

	}
}

int main() {
	start();
	return 0;
}