#include <iostream>     //Functions: cout, cerr
#include <ctime>        //Seed the RNG
#include <chrono>       //Data Types: time_point, milliseconds
#include <thread>       //Functions: thread, this_thread::sleep_for

#include <conio.h>      //Functions: getch | The only thing that is not standard to the C++ library.
						//This does include some of the standard library of the use of the function "rand"

/*
Global Varibles
Needed for Async Input.
*/
char newUserHit = 0;        //Continues to be updated from GetUserHitLocation.
char oldUserHit = 0;        //Updates when the newUserHit is processed.
bool needUserHit = true;    //Allows the loop to end when a round ends.

/*
Clears the screen.
This only works in linux, may works in OSX. Definitely not in Windows.
*/
void ClearScreen() {

	std::cerr << "\033c";

}

/*
Grabs the input from the user in a different thread.
This is how we get pass the input blocking that is created from cin, getch, etc.
--------------> ASYNC INPUT <----------*dab* *dab* *dab* *dab* *dab*
*/
void GetUserHitLocation() {

	while (needUserHit) {

		newUserHit = getch();

	}

}

/*
Handles information related to the board.
*/
class Board {

public:
	void GenerateBoard();                       //Generate the array.
	void DisplayBoard();                        //Displays the board.
	void DisplayControlBoard();                 //Displays the controls.

	void SetSize(int givenSize);                //Sets the size.

	int GetSize();                              //Gets the size
	char GetControls(int x, int y);             //Get control char
	char GetBoardValue(int x, int y);           //Get board char

	void UpdateBoardWithMole(int x, int y);     //O -> X
	void UpdateHit(int x, int y);               //X -> O

private:
	int size;                                   //Based on diffculty
	char board[7][7];                           //Board to display
	bool boardUpdated = false;                  //Used to update the board on the screen.
	char controls[7][7] =                       //Controls for the game.
	{
		{'1','|','2','|','3','|','4'},
		{'-','-','-','-','-','-','-'},
		{'q','|','w','|','e','|','r'},
		{'-','-','-','-','-','-','-'},
		{'a','|','s','|','d','|','f'},
		{'-','-','-','-','-','-','-'},
		{'z','|','x','|','c','|','v'}
	};

};

//Used to update the board from a mole to no moles.
void Board::UpdateHit(int x, int y) {

	board[x][y] = 'X';
	boardUpdated = true;

}

//Used to update the board from no moles to moles.
void Board::UpdateBoardWithMole(int x, int y) {

	board[x][y] = 'O';
	boardUpdated = true;

}

//Returns the size of the board so the program can use it for calculation.
int Board::GetSize() {

	return size;

}

//Return the value in the board array for usage in if statements.
char Board::GetBoardValue(int x, int y) {

	return board[x][y];

}

//Returns the value in controls array to find the index number for the board array.
char Board::GetControls(int x, int y) {

	return controls[x][y];

}

//Shows the controls.
void Board::DisplayControlBoard() {

	int c = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			std::cout << controls[i][j];
			c++;
			if (c % (7) == 0) {
				std::cout << std::endl;
			}
		}
	}

}

/*
Shows the board.
Uses cerr to bypass the internal blocking of cin, getch.
We bypass the program blocking with the uses of threads.
*/
void Board::DisplayBoard() {
	if (boardUpdated) {
		int c = 0;
		ClearScreen();
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - 1; j++) {
				std::cerr << board[i][j];
				c++;
				if (c % (size - 1) == 0) {
					std::cerr << std::endl;
				}
			}
		}
		boardUpdated = false;
	}
}

//Sets the size of the board using the diffculty.
void Board::SetSize(int givenDiff) {

	size = (givenDiff + 1) * 2;

}

//Fills the array with the chars so we can display it.
void Board::GenerateBoard() {

	for (int i = 0; i < size - 1; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < size - 1; j++) {
				if (j % 2 == 0) {
					board[i][j] = 'X';
				}
				else {
					board[i][j] = '|';
				}
			}
		}
		else {
			for (int j = 0; j < size - 1; j++) {
				board[i][j] = '-';
			}
		}
	}

	boardUpdated = true;

}

/*
Handles information related to the mole.
*/
class Mole {
public:
	void SetMoleLocation(int boardSize);					//Set the location of the mole.
	std::chrono::steady_clock::time_point GetMoleTime();	//Get the time when the mole was deployed.
	int GetMoleLocation(int index);							//Get the location of the mole.
	void BeenHit(bool hit);									//Set the bool if the mole was hit.
	bool GetHit();											//Get the bool if the mole was hit.
	void ZeroMoleLocation();								//Reset the mole location.

private:
	bool beenHit = false;									//See if the mole been hit.
	int moleLocation[2];									//Location of the mole.
	std::chrono::steady_clock::time_point deployMoleTime;	//Value of when the mole was deployed.

};

//This fills the moleLocation with zeros.
void Mole::ZeroMoleLocation() {

	moleLocation[0] = 0;
	moleLocation[1] = 0;

}

//This gets the bool of the mole of if the mole has been hit.
bool Mole::GetHit() {

	return beenHit;

}

//This set the bool of the mole of if the mole has been hit.
void Mole::BeenHit(bool hit) {

	beenHit = hit;

}

//This gets the value of the mole location in x or y.
int Mole::GetMoleLocation(int index) {

	return moleLocation[index];

}

//Returns the values of when the mole was first deployed.
std::chrono::steady_clock::time_point Mole::GetMoleTime() {

	return deployMoleTime;

}

/*
Generate the mole location.
The use of mod ensure that the mole is being placed is in the correct index of the board array.
*/
void Mole::SetMoleLocation(int boardSize) {

	do {

		moleLocation[0] = (rand() % boardSize);

	} while ((moleLocation[0] % 2) != 0);

	do {

		moleLocation[1] = (rand() % boardSize);

	} while ((moleLocation[1] % 2) != 0);

	deployMoleTime = std::chrono::steady_clock::now();

}

/*
This is the brains of the program.
This will handle all the logic of the program.
*/
class Game {

public:
	//Functions when the program starts.
	void StartGame();											//Start of the Game
	void Menu();												//The menu of the game
	void HowToPlay();											//Shows the player rules and controls
	void GameLoop();											//Main Program Loop

	//Game Logic
	void FindUserInputInArray(int inputloc[2]);					//Find what the user is trying to hit.
	void DeployMole();											//Places the mole on the board
	bool CheckMoleLocation(Mole mole);							//See if the mole can be overlapping
	bool CheckIfBoardFilled();									//See if the board is filled all the way with moles
	bool UserContinue();										//Shows stats and ask if to continue.
	void Countdown();											//Countdown before gameplay
	void CheckMole();											//See if the mole been hit, or if the time has ran out.
	void AdvanceLevel();										//Reset varibles.

private:
	int diffculty = 1;											//The diffculty of the game.
	int moleCount = 0;											//The amount of moles on the board.		
	int hits = 0;												//The amount of moles you hit.
	int misses = 0;												//The amount of moles that ran out of time.
	int hitLocation[2];											//The location the user is trying to hit.
	int milSecForMoleStay = 3000;								//The amount of time the mole can stay on the board in milliseconds
	int milSecForMoleDeploy = milSecForMoleStay / 3;			//The amount of time between a mole is deployed in milliseconds.
	std::chrono::steady_clock::time_point lastMoleTime;			//The value of when the last mole as deployed.

	int totalGames = 1;											//The amount of games played
	int totalHits = 0;											//The total amount of hits over all the games.
	int totalMisses = 0;										//The total amount of misses over all the games

	Board board;

	//Ten moles possible in each round.
	Mole mole1;
	Mole mole2;
	Mole mole3;
	Mole mole4;
	Mole mole5;
	Mole mole6;
	Mole mole7;
	Mole mole8;
	Mole mole9;
	Mole mole10;

};

/*
This cleans up the level.
It returns everything back to like the program has just started running.
Also re-enable the async input.
Once that is done, re-generate the board and clear the screen.
*/
void Game::AdvanceLevel() {

	mole10.BeenHit(false);
	mole9.BeenHit(false);
	mole8.BeenHit(false);
	mole7.BeenHit(false);
	mole6.BeenHit(false);
	mole5.BeenHit(false);
	mole4.BeenHit(false);
	mole3.BeenHit(false);
	mole2.BeenHit(false);
	mole1.BeenHit(false);

	mole1.ZeroMoleLocation();
	mole2.ZeroMoleLocation();
	mole3.ZeroMoleLocation();
	mole4.ZeroMoleLocation();
	mole5.ZeroMoleLocation();
	mole6.ZeroMoleLocation();
	mole7.ZeroMoleLocation();
	mole8.ZeroMoleLocation();
	mole9.ZeroMoleLocation();
	mole10.ZeroMoleLocation();

	oldUserHit = 0;
	newUserHit = 0;
	hits = 0;
	misses = 0;
	moleCount = 0;

	needUserHit = true;

	board.SetSize(diffculty);
	board.GenerateBoard();

	ClearScreen();

}

/*
Checks if the mole need to be remove from the board.
From hits, or not even hitting at all.
*/
void Game::CheckMole() {

	switch (moleCount) {

	case 10:

		if ('O' == board.GetBoardValue(mole10.GetMoleLocation(0), mole10.GetMoleLocation(1)) && !mole10.GetHit()) {

			if (mole10.GetMoleLocation(0) == hitLocation[0] && mole10.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole10.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole10.GetMoleTime()).count()) {

				board.UpdateHit(mole10.GetMoleLocation(0), mole10.GetMoleLocation(1));
				misses++;
				mole10.BeenHit(true);

			}

		}

	case 9:
		if ('O' == board.GetBoardValue(mole9.GetMoleLocation(0), mole9.GetMoleLocation(1)) && !mole9.GetHit()) {

			if (mole9.GetMoleLocation(0) == hitLocation[0] && mole9.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole9.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole9.GetMoleTime()).count()) {

				board.UpdateHit(mole9.GetMoleLocation(0), mole9.GetMoleLocation(1));
				misses++;
				mole9.BeenHit(true);

			}

		}

	case 8:
		if ('O' == board.GetBoardValue(mole8.GetMoleLocation(0), mole8.GetMoleLocation(1)) && !mole8.GetHit()) {

			if (mole8.GetMoleLocation(0) == hitLocation[0] && mole8.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole8.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole8.GetMoleTime()).count()) {

				board.UpdateHit(mole8.GetMoleLocation(0), mole8.GetMoleLocation(1));
				misses++;
				mole8.BeenHit(true);

			}

		}

	case 7:
		if ('O' == board.GetBoardValue(mole7.GetMoleLocation(0), mole7.GetMoleLocation(1)) && !mole7.GetHit()) {

			if (mole7.GetMoleLocation(0) == hitLocation[0] && mole7.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole7.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole7.GetMoleTime()).count()) {

				board.UpdateHit(mole7.GetMoleLocation(0), mole7.GetMoleLocation(1));
				misses++;
				mole7.BeenHit(true);

			}

		}

	case 6:
		if ('O' == board.GetBoardValue(mole6.GetMoleLocation(0), mole6.GetMoleLocation(1)) && !mole6.GetHit()) {

			if (mole6.GetMoleLocation(0) == hitLocation[0] && mole6.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole6.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole6.GetMoleTime()).count()) {

				board.UpdateHit(mole6.GetMoleLocation(0), mole6.GetMoleLocation(1));
				misses++;
				mole6.BeenHit(true);

			}

		}

	case 5:
		if ('O' == board.GetBoardValue(mole5.GetMoleLocation(0), mole5.GetMoleLocation(1)) && !mole5.GetHit()) {

			if (mole5.GetMoleLocation(0) == hitLocation[0] && mole5.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole5.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole5.GetMoleTime()).count()) {

				board.UpdateHit(mole5.GetMoleLocation(0), mole5.GetMoleLocation(1));
				misses++;
				mole5.BeenHit(true);

			}

		}

	case 4:
		if ('O' == board.GetBoardValue(mole4.GetMoleLocation(0), mole4.GetMoleLocation(1)) && !mole4.GetHit()) {

			if (mole4.GetMoleLocation(0) == hitLocation[0] && mole4.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole4.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole4.GetMoleTime()).count()) {

				board.UpdateHit(mole4.GetMoleLocation(0), mole4.GetMoleLocation(1));
				misses++;
				mole4.BeenHit(true);

			}

		}

	case 3:
		if ('O' == board.GetBoardValue(mole3.GetMoleLocation(0), mole3.GetMoleLocation(1)) && !mole3.GetHit()) {

			if (mole3.GetMoleLocation(0) == hitLocation[0] && mole3.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole3.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole3.GetMoleTime()).count()) {

				board.UpdateHit(mole3.GetMoleLocation(0), mole3.GetMoleLocation(1));
				misses++;
				mole3.BeenHit(true);

			}

		}

	case 2:
		if ('O' == board.GetBoardValue(mole2.GetMoleLocation(0), mole2.GetMoleLocation(1)) && !mole2.GetHit()) {

			if (mole2.GetMoleLocation(0) == hitLocation[0] && mole2.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole2.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole2.GetMoleTime()).count()) {

				board.UpdateHit(mole2.GetMoleLocation(0), mole2.GetMoleLocation(1));
				mole2.BeenHit(true);
				misses++;

			}

		}

	case 1:
		if ('O' == board.GetBoardValue(mole1.GetMoleLocation(0), mole1.GetMoleLocation(1)) && !mole1.GetHit()) {

			if (mole1.GetMoleLocation(0) == hitLocation[0] && mole1.GetMoleLocation(1) == hitLocation[1]) {

				board.UpdateHit(hitLocation[0], hitLocation[1]);
				newUserHit = 0;
				oldUserHit = 0;

				std::cerr << "Hit!";
				mole1.BeenHit(true);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				hits++;


			}
			else if (milSecForMoleStay < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mole1.GetMoleTime()).count()) {

				board.UpdateHit(mole1.GetMoleLocation(0), mole1.GetMoleLocation(1));
				mole1.BeenHit(true);
				misses++;

			}

		}

	}

}

/* 
This shows the stats of the player performance.
This test if the game needs to increase its diffculty.
This is also a way the program can end.
*/
bool Game::UserContinue() {

	totalHits += hits;		//Add hits to total amount
	totalMisses += misses;	//Add misses to total amount

	ClearScreen();
	std::cerr << "End Of Game " << totalGames << "!" << std::endl << std::endl;
	std::cerr << "Round Hits: \t" << hits << std::endl;
	std::cerr << "Round Misses: \t" << misses << std::endl;
	std::cerr << "Hit Ratio: \t" << ((hits / 10.0) * 100) << "%" << std::endl << std::endl;

	if (((hits / 10.0) * 100) > 50) {

		std::cerr << "You did well enough to advance!" << std::endl << std::endl;

		if (diffculty < 3) {

			diffculty++;

		}
		else {

			if (milSecForMoleStay >= 500) {

				milSecForMoleStay -= 500;

			}

		}

	}
	else {

		std::cerr << "Nice try, better luck next time." << std::endl << std::endl;

	}

	std::cerr << "Overall Hits: \t\t" << totalHits << std::endl;
	std::cerr << "Overall Misses: \t" << totalMisses << std::endl;
	std::cerr << "Overall Hit Ratio: \t" << ((totalHits / (10.0*totalGames)) * 100) << "%" << std::endl << std::endl;

	std::cerr << "Would you like to continue? (y/n)" << std::endl;
	totalGames++;

	do {

		newUserHit = getch();

		if (newUserHit == 'y') {

			return true;

		}
		else if (newUserHit == 'n') {

			return false;

		}
		else {

			std::cerr << "That is not a valid answer.";

		}

	} while (true);
}

/*
Checks if the board is filled with moles
This allows us to make sure that moles are not being deployed in spots that are filled.
*/
bool Game::CheckIfBoardFilled() {

	int numberOfSpaces = (diffculty + 1) * (diffculty + 1);	//The number of spaces that the moles can be.
	int molesOnBoard = 0;									//The number of moles on the board.

	for (int i = 0; i < board.GetSize() - 1; i++) {

		for (int j = 0; j < board.GetSize() - 1; j++) {

			//IF on the board theres a O, Then thats a mole.
			if (board.GetBoardValue(i, j) == 'O') {

				molesOnBoard++;

			}

		}

	}

	//If the spaces = moles, then board is entirely filled.
	if (numberOfSpaces == molesOnBoard) {

		return true;

	}
	else {

		return false;

	}

}

//Allows the user to get ready.
void Game::Countdown() {

	for (int i = 5; i > 0; i--) {

		std::cerr << "Starting in " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}

}

/*
The main program loop
*/
void Game::GameLoop() {

	//The program loop.
	do {

		std::thread userInput(GetUserHitLocation);	//Starts the thread for async input
		Countdown();

		//The loop when playing.
		do {

			DeployMole();
			board.DisplayBoard();
			FindUserInputInArray(hitLocation);
			CheckMole();
			board.DisplayBoard();

		} while (hits + misses < 10);

		ClearScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));	//Timing so the player does not input char for no reason.

		//This forces the player to press a button to close the thread.
		std::cerr << "End Of Game " << totalGames << "!" << std::endl << std::endl;
		std::cout << "Press any key to continue." << std::endl;
		needUserHit = false;	//Allows the input to stop for async.
		userInput.join();		//join thread with main, is blocking, and does close when finish.

		//Ask the user if they want to quit.
		if (UserContinue()) {

			AdvanceLevel();

		}
		else {

			ClearScreen();
			std::cerr << "Goodbye! Thanks For Playing!";
			exit(0);

		}

	} while (true);
}

/*
Check to see if the mole location is filled with a mole.
This is to prevent overlapping moles.
*/
bool Game::CheckMoleLocation(Mole mole) {

	//If the mole is in the spot, tell the program to generate a new location
	if ('O' == board.GetBoardValue(mole.GetMoleLocation(0), mole.GetMoleLocation(1))) {

		return false;

	}
	else {

		return true;

	}

}

/*
This Deploys the moles over time.
This uses the elapsed time to find if a mole can be deployed.

First: Generates a location for the mole.
Second: Checks if the mole can be placed there.
Third: Place the mole on the board
Fourth: Set the timer of the mole so the moles are not deployed to fast.
Fifth: Increase mole counter.

*/
void Game::DeployMole() {

	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastMoleTime).count() >= milSecForMoleDeploy && !CheckIfBoardFilled()) {
		switch (moleCount) {

		case 0:

			do {

				mole1.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole1));

			board.UpdateBoardWithMole(mole1.GetMoleLocation(0), mole1.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 1:

			do {

				mole2.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole2));

			board.UpdateBoardWithMole(mole2.GetMoleLocation(0), mole2.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 2:

			do {

				mole3.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole3));

			board.UpdateBoardWithMole(mole3.GetMoleLocation(0), mole3.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 3:

			do {

				mole4.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole4));

			board.UpdateBoardWithMole(mole4.GetMoleLocation(0), mole4.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 4:

			do {

				mole5.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole5));

			board.UpdateBoardWithMole(mole5.GetMoleLocation(0), mole5.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 5:

			do {

				mole6.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole6));

			board.UpdateBoardWithMole(mole6.GetMoleLocation(0), mole6.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 6:

			do {

				mole7.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole7));

			board.UpdateBoardWithMole(mole7.GetMoleLocation(0), mole7.GetMoleLocation(1));
			moleCount++;
			lastMoleTime = std::chrono::steady_clock::now();

			break;
		case 7:

			do {

				mole8.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole8));

			board.UpdateBoardWithMole(mole8.GetMoleLocation(0), mole8.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 8:

			do {

				mole9.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole9));

			board.UpdateBoardWithMole(mole9.GetMoleLocation(0), mole9.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		case 9:

			do {

				mole10.SetMoleLocation(board.GetSize());

			} while (!CheckMoleLocation(mole10));

			board.UpdateBoardWithMole(mole10.GetMoleLocation(0), mole10.GetMoleLocation(1));

			lastMoleTime = std::chrono::steady_clock::now();
			moleCount++;
			break;
		default:
			break;
		}

	}
}

/*
This finds the index number of the board that the user is trying to hit.
Uses the control array to find that.
*/
void Game::FindUserInputInArray(int inputloc[2]) {

	bool foundInput = false;

	if (oldUserHit != newUserHit) {
		for (int i = 0; i < 7; i++) {

			if ((i % 2) == 0) {		//Used to save time, The controls are on even index.

				for (int j = 0; j < 7; j++) {

					//Found what the user is trying to hit.
					if (newUserHit == board.GetControls(i, j)) {

						inputloc[0] = i;
						inputloc[1] = j;
						foundInput = true;		//Used to not trigger the if statement that would undo work.

					}

				}

			}

		}

		//Update oldUserHit so we dont trigger the for loops by accidents
		oldUserHit = newUserHit;

	}

	//If the key that the user hit is not on the control array.
	//Also triggered from a key is not pressed.
	if (!foundInput) {

		inputloc[0] = -1;
		inputloc[1] = -1;

	}

}

//The user selects the diffculty.
void Game::StartGame() {

	int diffcultySelection;			//Used for switching.
	bool notVaildSelection = true;	//Used to catch bad selection.

	ClearScreen();					//Clears the screen.

	//Shows the user the options
	std::cout << "What diffculty level would you like to start at?" << std::endl;
	std::cout << "1. Easy" << std::endl;
	std::cout << "2. Normal" << std::endl;
	std::cout << "3. Hard" << std::endl;

	//Do while to catch invalid reponses.
	do {

		diffcultySelection = getch();

		switch (diffcultySelection) {

			//Easy
		case '1':
			notVaildSelection = false;
			diffculty = 1;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;

			//Normal
		case '2':
			notVaildSelection = false;
			diffculty = 2;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;

			//Hard
		case '3':
			notVaildSelection = false;
			diffculty = 3;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;

			//Invalid Selection
		default:
			std::cout << "This is not a valid selection." << std::endl;
			notVaildSelection = true;
			break;
		}
	} while (notVaildSelection);

}

/*
This the front page of the game.
This give the user to play it, learn it, or quits.
*/
void Game::Menu() {

	int menuSelection;				//Used for switching.
	bool notVaildSelection = true;	//Used to catch bad selection.

	ClearScreen();					//Clears the screen.

	//Shows the user the options
	std::cout << "Welcome to Walmart Greeters\' \"Whack a mole\" game!" << std::endl;
	std::cout << "1. Play The Game." << std::endl;
	std::cout << "2. Learn How To Play." << std::endl;
	std::cout << "3. Exit" << std::endl;

	//Do while to catch invalid reponses.
	do {

		std::cout << "Please choose an option." << std::endl;
		menuSelection = getch();

		switch (menuSelection) {
		
			//Play The Game.
		case '1':
			notVaildSelection = false;
			StartGame();
			break;

			//Learn How To Play.
		case '2':
			notVaildSelection = false;
			HowToPlay();
			break;

			//Exit
		case '3':
			notVaildSelection = false;
			ClearScreen();
			std::cout << "Goodbye!";
			exit(0);
			break;

			//Invalid
		default:
			std::cout << "This is not a valid selection." << std::endl;
			notVaildSelection = true;
			break;
		}
	} while (notVaildSelection);
}

/*
This tells the user how the games works.
Also shows the user the controls for the game.
*/
void Game::HowToPlay() {

	ClearScreen();					//Clear the screen.

	//Explains the rules and how the games works.
	std::cout << "How to play: " << std::endl << "Look at the table below, each square contains a character that represents a location on " << std::endl;
	std::cout << "the mole hill. When you see a \"O\", press the corresponding character" << std::endl;
	std::cout << "This needs to be done in 3 seconds or less." << std::endl;
	std::cout << "The farther you make it, the bigger the board and pass the biggest board, the time decreases." << std::endl;

	board.DisplayControlBoard();	//Shows the controls.

	//Prompt the user to press a key.
	std::cout << std::endl;
	std::cout << "Press any key to return back to the menu" << std::endl;

	getch();						//Pauses the program to allow the player to read.
	Menu();							//Returns the player back to the menu.


}

//The entry point of the program
int main() {

	srand(time(0));	//Seed the random number generator.

	Game game;		//Create the game object.

	game.Menu();	//Run the menu of the game.

	return 0;		//Standard.
}
