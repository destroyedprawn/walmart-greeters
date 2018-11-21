#include "pch.h"
#include <windows.h>
#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
using namespace std;

class Game {
	//public class makes variables accessable throughout the program
public:

	int difficulty = 6;	//Sets the size of the board
	int xLocation;		//Colum the mole is in
	int yLocation;		//Row the mole is in
	char grid[7][7];	//Holds the game board
	int guess[7][7];	//The user guessuuuuuuuuu
	int size;			//Size of the game board
	char control[7][7];	//user games 
	char guide[7][7] =	//Guide grid for user reference
	{
		{'1','|','2','|','3','|','4'},
		{'-','-','-','-','-','-','-'},
		{'q','|','w','|','e','|','r'},
		{'-','-','-','-','-','-','-'},
		{'a','|','s','|','d','|','f'},
		{'-','-','-','-','-','-','-'},
		{'z','|','x','|','c','|','v'}
	};


		//The various modifier functions (getters & setters)
	void setY(int y);
	void setX(int x);
	void setSize(int diff);
	void setGrid();
	void displayGrid(string a);
	char getGrid(int i, int j);
	void setMole();
	void defineGuess();
	int playRules();
	string checkInput(char g);
};

//defines the rules
int Game::playRules() {
	cout << "Welcome to wac a mole!" << endl;
	cout << "what level difficulty do you want? (1 to 3)" << endl;
	cin >> difficulty;
	cout << "How to play: " << endl << "look at the table below, each square contains a character that represents a location on " << endl;
	cout << "the mole hill. when you see a \"O\" press the corresponding character, then press enter." << endl;
	cout << "This needs to be done in 3 seconds or less. The farther you make it, the shorter that time will be, good luck!" << endl;
	return difficulty;
}

//checks the guess to the game board
string Game::checkInput(char g) {
	string output;
	switch (g) {
	case '1': if (grid[0][0] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case '2': if (grid[0][2] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case '3': if (grid[0][4] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case '4': if (grid[0][6] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case 'q': if (grid[2][0] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case 'w': if (grid[2][2] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'e': if (grid[2][4] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case 'r': if (grid[2][6] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'a': if (grid[4][0] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 's': if (grid[4][2] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'd': if (grid[4][4] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'f': if (grid[4][6] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'z': if (grid[6][0] == 'O') {
		output = "GOT EM!";
		return output;
	} break;
	case 'x': if (grid[6][2] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'c': if (grid[6][4] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	case 'v': if (grid[6][6] == 'O') {
		output = "GOT EM!";
		return output; 
	} break;
	default: output = "Missed";
		return output; break;
	}
	output = "Missed";
	return output;
}

//Sets the value of the guess
void Game::defineGuess() {

}

//Sets position of the mole on the game grid
void Game::setMole() {
	grid[yLocation][xLocation] = 'O';
}

// Displays the grid on the output screen
void Game::displayGrid(string a) {
	if (a == "grid") {
		int c = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << grid[i][j];
				c++;
				if (c % size == 0) {
					cout << endl;
				}
			}
		}
	}
	else if (a == "intro") {
		int c = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << guide[i][j];
				c++;
				if (c % size == 0) {
					cout << endl;
				}
			}
		}
	}

}

// Return value of specific grid value 
char Game::getGrid(int i, int j) {
	return grid[i][j];
}

// Sets the value of size in the public class
void Game::setSize(int diff) {
	size = diff;
}

// Sets the value of yLocation in the public class
void Game::setY(int y) {
	yLocation = y;
}

// Sets the value of xLocation in the public class
void Game::setX(int x) {
	xLocation = x;
}

// Populates the grid with needed values
void Game::setGrid() 
{
	int i;
	int j;
	for (i = 0; i < size; i++) {
		if (i % 2 == 0) {
			for (j = 0; j < size; j++) {
				if (j % 2 == 0) {
					grid[i][j] = 'X';
				}
				else {
					grid[i][j] = '|';
				}
			}
			cout << endl;
		}
		else {
			for (j = 0; j < size; j++) {
				grid[i][j] = '-';
			}
			cout << endl;
		}
	}
}

int main()
{
	// Declare game object
	Game game1;

	//Starts time in the game
	clock_t window;

	// declare variables 
	int diff;						//holds the user input difficulty 
	int size;						//Holds hte size of the board
	int score;						//keeps track of the user score
	int wins;						//tracks how many wins you have 
	char guess;						//user input for mole location
	string cont = "yes";			//Used to continue playing

	//welcomes the user to the game and calls and sets the size of the board size
	diff = game1.playRules() + 1;
	size = (diff * 2) - 1;
	game1.setSize(size);
	game1.setGrid();

	//displays the reference grid for the user 
	game1.displayGrid("intro");

	//asks user when they want to continue
	while (cin.get() == '\n') {
		cout << endl << "Enter any key to continue" << endl;
	}

	// used to play again 
	while (cont == "yes") {

		//Resets the score and win counter every new game
		score = 0;
		wins = 0;

		//Runs the game for 3 rounds of 10 games
		for (int j = 1; j <= 3; j++) {
			for (int i = 0; i < 10; i++) {

				//resets grid from last round
				game1.setGrid();

				//Set mole location
				srand(time(NULL));
				game1.setX(2 * rand() % (diff * 2));
				game1.setY(2 * rand() % (diff * 2));
				game1.setMole();

				// display the game board
				game1.displayGrid("grid");

				//Gets the guess and checks it against the game board
				//Tracks the time ot takes to whack the mole
				window = clock();
				cin >> guess;
				window = clock() - window;
				if (window <= 3000 / j) {
					cout << game1.checkInput(guess) << endl;

					//Increments the score
					if (game1.checkInput(guess) == "GOT EM!") {
						wins++;
						score = score + (10 * j * diff);
					}
					Sleep(750);
				}
				else {
					cout << "Miss! Too slow..." << endl;
					Sleep(750);
				}
			}
			if (wins < 6 * j) {
				break;
			}
			else {

				//Displays the results of the game so far
				cout << endl << endl;
				cout << "	Round " << j << " results: " << endl << "	--------------" << endl;
				cout << "	Wins: " << wins << endl;
				cout << "	losses:" << (10 * j - wins) << endl;
				cout << "	score: " << score << endl << endl << endl;

				if (j == 3) {
					break;
				}
				for (int k = 8; k > 0; k--) {
					cout << "Next round in " << k << endl;
					Sleep(1000);
				}
			}
			if (j == 3 && wins > 18) {
				cout << "Congradulations, you finished! your score is: " << score << endl;
			}
		}
		cout << "Your final score is: " << score << endl << endl;

		cout << "Do you want to play again? (yes / no)" << endl;
		cin >> cont;
	}
}	
	
