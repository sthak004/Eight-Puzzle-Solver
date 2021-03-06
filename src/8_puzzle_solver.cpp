#include <cmath>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;


#define PUZZLE_WIDTH 3 /* DIMENSION OF PUZZLE (ex. 3 x 3) */


int totalNodes = 0;
int depth = 0;
vector<int> GOAL_STATE = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /* GOAL STATE */

struct Puzzle 
{
	Puzzle() : hn(0), gn(0){}
	vector<int> CURRENT_STATE;

	int hn;
	int gn;

};


vector<Puzzle> visited_puzzles;

class Cost_Comparator {
public:
	bool operator()(Puzzle &P1, Puzzle &P2){
		return ( (P1.hn + P1.gn) > (P2.hn + P2.gn) );
	}
};


bool isGoalState(Puzzle &P) {
	for(int i = 0; i < P.CURRENT_STATE.size(); i++) {
		if(P.CURRENT_STATE.at(i) != GOAL_STATE.at(i)) {
			return false;
		}
	}
	return true;
}


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

/* bp = blank position */
bool isLeftWall(int bp) {	
	if(bp == 0 || bp == 3 || bp == 6) {
		return true;
	}
	return false;
}

bool isRightWall(int bp) {
	if(bp == 2 || bp == 5 || bp == 8) {
		return true;
	}
	return false;
}

bool isTopWall(int bp) {
	if(bp == 0 || bp == 1 || bp == 2) {
		return true;
	}
	return false;
}

bool isBottomWall(int bp) {
	if(bp == 6 || bp == 7 || bp == 8) {
		return true;
	}
	return false;
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
}

/* ----------------------------------------------------------------------------- */

/* Operators */

/* move blank space LEFT  */
Puzzle move_left(Puzzle &P, int choice) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on left wall*/
	if(!isLeftWall(blank)) {
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(blank-1));
	}
	else {
		cout << endl << "Left wall, cannot move it." << endl;
	}

	P.gn += 1;

	if(choice == 1) { P.hn = 0; }
	if(choice == 2) { misplaced_tile(P); }
	if(choice == 3) { manhatatan_distance(P); }

	totalNodes++;

	return P;
}


/* move blank space RIGHT */
Puzzle move_right(Puzzle &P, int choice) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on right wall*/
	if(!isRightWall(blank)) {
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(blank+1));
	}
	else {
		cout << endl << "Right wall, cannot move it." << endl;
	}

	P.gn += 1;

	if(choice == 1) { P.hn = 0; }
	if(choice == 2) { misplaced_tile(P); }
	if(choice == 3) { manhatatan_distance(P); }

	totalNodes++;

	return P;
}


/* move blank space UP */
Puzzle move_up(Puzzle &P, int choice) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on top wall*/
	if(!isTopWall(blank)) {
		int index_above = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) - 1 ) + (blank % PUZZLE_WIDTH));
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(index_above));
	}
	else {
		cout << endl << "Top wall, cannot move it." << endl;
	}

	P.gn += 1;

	if(choice == 1) { P.hn = 0; }
	if(choice == 2) { misplaced_tile(P); }
	if(choice == 3) { manhatatan_distance(P); }

	totalNodes++;

	return P;
	
}

/* move blank space DOWN */
Puzzle move_down(Puzzle &P, int choice) {
	int blank = find_blank(P.CURRENT_STATE);

	/* IF blank space is NOT on bottom wall*/
	if(!isBottomWall(blank)) {
		int index_below = (PUZZLE_WIDTH * ((blank/PUZZLE_WIDTH) + 1 ) + (blank % PUZZLE_WIDTH));
		swap(P.CURRENT_STATE.at(blank), P.CURRENT_STATE.at(index_below));
	}
	else {
		cout << endl << "Bottom wall, cannot move it." << endl;
	}

	P.gn += 1;

	if(choice == 1) { P.hn = 0; }
	if(choice == 2) { misplaced_tile(P); }
	if(choice == 3) { manhatatan_distance(P); }

	totalNodes++;

	return P;
	
}



/* ----------------------------------------------------------------------------- */

bool checkIfVisited(Puzzle &P, vector<Puzzle> &visited) {
	for(int i = 0; i < visited.size(); i++) {
		if(visited.at(i).CURRENT_STATE == P.CURRENT_STATE) {
			return true;
		}
	}
	return false;
}


void expand_puzzle(Puzzle &puzzle, priority_queue<Puzzle,vector<Puzzle>, Cost_Comparator> &nodes_queue, int choice)  {
	/* CP = Child Puzzle */
	Puzzle cp1;
	Puzzle cp2;
	Puzzle cp3;
	Puzzle cp4;

	/* Copy the puzzle's current state in 4 different puzzles */
	cp1 = puzzle;
	cp2 = puzzle;
	cp3 = puzzle;
	cp4 = puzzle;


	/* find blank space */
	int blank_position = find_blank(puzzle.CURRENT_STATE);

	/* depending on location of blank, move the blank in each created child node */

	/* TOP LEFT*/
	if(blank_position == 0) {
		// nodes_queue.push(move_right(cp1, choice));
		// nodes_queue.push(move_left(cp2, choice));
		cp1 = move_right(cp1, choice);
		cp2 = move_down(cp2, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
	}
	/* TOP MIDDLE*/
	else if(blank_position == 1) {
		// nodes_queue.push(move_left(cp1, choice));
		// nodes_queue.push(move_down(cp2, choice));
		// nodes_queue.push(move_right(cp3, choice));
		cp1 = move_left(cp1, choice);
		cp2 = move_down(cp2, choice);
		cp3 = move_right(cp3, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
		if(!checkIfVisited(cp3, visited_puzzles)) { nodes_queue.push(cp3); visited_puzzles.push_back(cp3);}
	}
	/* TOP RIGHT */
	else if(blank_position == 2) {
		// nodes_queue.push(move_left(cp1, choice));
		// nodes_queue.push(move_down(cp2, choice));
		cp1 = move_left(cp1, choice);
		cp2 = move_down(cp2, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
	}
	/* MIDDLE LEFT */
	else if(blank_position == 3) {
		// nodes_queue.push(move_up(cp1, choice));
		// nodes_queue.push(move_down(cp2, choice));
		// nodes_queue.push(move_right(cp3, choice));

		cp1 = move_up(cp1, choice);
		cp2 = move_down(cp2, choice);
		cp3 = move_right(cp3, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
		if(!checkIfVisited(cp3, visited_puzzles)) { nodes_queue.push(cp3); visited_puzzles.push_back(cp3);}
	}
	/* CENTER */
	else if(blank_position == 4) {
		// nodes_queue.push(move_up(cp1, choice));
		// nodes_queue.push(move_right(cp2, choice));
		// nodes_queue.push(move_down(cp3, choice));
		// nodes_queue.push(move_left(cp4, choice));


		cp1 = move_up(cp1, choice);
		cp2 = move_right(cp2, choice);
		cp3 = move_down(cp3, choice);
		cp4 = move_left(cp4, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
		if(!checkIfVisited(cp3, visited_puzzles)) { nodes_queue.push(cp3); visited_puzzles.push_back(cp3);}
		if(!checkIfVisited(cp4, visited_puzzles)) { nodes_queue.push(cp4); visited_puzzles.push_back(cp4);}
	}
	/* MIDDLE RIGHT */
	else if(blank_position == 5) {
		// nodes_queue.push(move_up(cp1, choice));
		// nodes_queue.push(move_left(cp2, choice));
		// nodes_queue.push(move_down(cp3, choice));

		cp1 = move_up(cp1, choice);
		cp2 = move_left(cp2, choice);
		cp3 = move_down(cp3, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
		if(!checkIfVisited(cp3, visited_puzzles)) { nodes_queue.push(cp3); visited_puzzles.push_back(cp3);}
	}
	/* BOTTOM LEFT */
	else if(blank_position == 6) {
		// nodes_queue.push(move_up(cp1, choice));
		// nodes_queue.push(move_right(cp2, choice));


		cp1 = move_up(cp1, choice);
		cp2 = move_right(cp2, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
	}
	/* BOTTOM MIDDLE */
	else if(blank_position == 7) {
		// nodes_queue.push(move_left(cp1, choice));
		// nodes_queue.push(move_up(cp2, choice));
		// nodes_queue.push(move_right(cp3, choice));


		cp1 = move_left(cp1, choice);
		cp2 = move_up(cp2, choice);
		cp3 = move_right(cp3, choice);

		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
		if(!checkIfVisited(cp3, visited_puzzles)) { nodes_queue.push(cp3); visited_puzzles.push_back(cp3);}

	}
	/* BOTTOM RIGHT */
	else if(blank_position == 8) {
		// nodes_queue.push(move_up(cp1, choice));
		// nodes_queue.push(move_left(cp2, choice));


		cp1 = move_up(cp1, choice);
		cp2 = move_left(cp2, choice);
		if(!checkIfVisited(cp1, visited_puzzles)) { nodes_queue.push(cp1); visited_puzzles.push_back(cp1);}
		if(!checkIfVisited(cp2, visited_puzzles)) { nodes_queue.push(cp2); visited_puzzles.push_back(cp2);}
	}
}


/* ----------------------------------------------------------------------------- */





vector<int> default_puzzle() {
	/* dp = the default puzzle*/
	vector<int> dp = {1, 2, 3, 4, 8, 0, 7, 6, 5};
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
		}
		else {
			cout << "Please choose option '1' or '2'" << endl;
			return;
		}

		int search_choice = choose_search();

		/*if(search_choice == 1) { P.hn = 0; }
		else if(search_choice == 2) { misplaced_tile(P); }
		else if(search_choice == 3) { manhatatan_distance(P); }*/

		priority_queue<Puzzle, vector<Puzzle>, Cost_Comparator> nodes_queue;


		int max_nodes_in_queue = 0;


		nodes_queue.push(P);
		//mark it as visited
		visited_puzzles.push_back(P);

		while(!nodes_queue.empty()) {

			// if(nodes_queue.empty()) {
			// 	cout << "FAILURE: This puzzle is unsolvable" << endl;
			// 	cout << ":(((" << endl;
			// 	break;
			// }

			Puzzle temp;
			temp = nodes_queue.top();

			nodes_queue.pop();

			if(isGoalState(temp)) {
				cout << endl << "GOAL!!!";
				print_vector(temp.CURRENT_STATE);
				cout << "To solve this problem the search algorithm expanded a total of "
				     << totalNodes << " nodes.\n";
				cout << "The maximum number of nodes in the queue at any one time was "
					 << max_nodes_in_queue << ".\n";
				cout << "The depth of the goal node was " << temp.gn << ".\n";
				return;
			}


			expand_puzzle(temp, nodes_queue, search_choice);

		
			int currMaxQueue = nodes_queue.size();
			max_nodes_in_queue = max(max_nodes_in_queue, currMaxQueue);

			cout << "The best state to expand with g(n)=" << nodes_queue.top().gn << " and h(n)=" << nodes_queue.top().hn << " is..." << endl;

			print_vector(temp.CURRENT_STATE);
			cout << endl << "Expanding..." << endl << endl;
		}

	}
	return;
}

int main() {
	start();
	return 0;
}
