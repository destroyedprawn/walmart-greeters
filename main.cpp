#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>
#include <conio.h>
#include <thread>

//Add a second losing condition, if the board should ever fill up with moles, you should lose
char newUserHit = 0;
char oldUserHit = 0;
bool needUserHit = true;

void ClearScreen() {

	std::cerr << "\033c";

}

void GetUserHitLocation() {

	while (needUserHit) {

		newUserHit = getch();

	}

}

class Board {

public:
	void GenerateBoard();
	void DisplayBoard();
	void DisplayControlBoard();

	void SetSize(int givenSize);
	int GetSize();
	char GetControls(int x, int y);
	char GetBoardValue(int x, int y);
	void UpdateBoardWithMole(int x, int y);
	void UpdateHit(int x, int y);

private:
	int size;
	char board[7][7];
	bool boardUpdated = false;
	char controls[7][7] =	//Guide grid for user reference
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

void Board::UpdateHit(int x, int y) {

	board[x][y] = 'X';
	boardUpdated = true;

}

void Board::UpdateBoardWithMole(int x, int y) {

	board[x][y] = 'O';
	boardUpdated = true;

}

int Board::GetSize() {

	return size;

}

char Board::GetBoardValue(int x, int y) {

	return board[x][y];

}

char Board::GetControls(int x, int y) {

	return controls[x][y];

}

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

void Board::SetSize(int givenDiff) {

	size = (givenDiff + 1) * 2;

}

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

class Mole {
public:
	void SetMoleLocation(int boardSize);
	std::chrono::steady_clock::time_point GetMoleTime();
	int GetMoleLocation(int index);
	void BeenHit(bool hit);
	bool GetHit();
	void ZeroMoleLocation();

private:
	bool beenHit = false;
	int moleLocation[2];
	std::chrono::steady_clock::time_point deployMoleTime;

};

void Mole::ZeroMoleLocation() {

	moleLocation[0] = 0;
	moleLocation[1] = 0;

}

bool Mole::GetHit() {

	return beenHit;

}

void Mole::BeenHit(bool hit) {

	beenHit = hit;

}

int Mole::GetMoleLocation(int index) {

	return moleLocation[index];

}

std::chrono::steady_clock::time_point Mole::GetMoleTime() {

	return deployMoleTime;

}

void Mole::SetMoleLocation(int boardSize) {

	do {

		moleLocation[0] = (rand() % boardSize);

	} while ((moleLocation[0] % 2) != 0);

	do {

		moleLocation[1] = (rand() % boardSize);

	} while ((moleLocation[1] % 2) != 0);

	deployMoleTime = std::chrono::steady_clock::now();

}

class Game {

public:
	void StartGame();
	void Menu();
	void HowToPlay();
	void GameLoop();

	//Game Logic
	void FindUserInputInArray(int inputloc[2]);
	void DidHit();
	void DeployMole();
	bool CheckMoleLocation(Mole mole);
	bool CheckIfBoardFilled();
	bool UserContinue();
	void Countdown();
	void CheckMole();
	void AdvanceLevel();

private:
	int diffculty = 1;
	int moleCount = 0;
	int hits = 0;
	int misses = 0;
	int hitLocation[2];
	int milSecForMoleStay = 3000;
	int milSecForMoleDeploy = milSecForMoleStay / 3;
	std::chrono::steady_clock::time_point lastMoleTime;

	int totalGames = 1;
	int totalHits = 0;
	int totalMisses = 0;

	Board board;

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

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

bool Game::UserContinue() {

	oldUserHit = 0;
	newUserHit = 0;

	totalHits += hits;
	totalMisses += misses;

	ClearScreen();
	std::cerr << "End Of Game " << totalGames << "!" << std::endl << std::endl;
	std::cerr << "Round Hits: \t" << hits << std::endl;
	std::cerr << "Round Misses: \t" << misses << std::endl;
	std::cerr << "Hit Ratio: \t" << ((hits / 10.0) * 100) << "%" << std::endl << std::endl;

	if (((hits / 10.0) * 100) > 50) {

		std::cerr << "You did well enough to advance!" << std::endl << std::endl;

		if (diffculty < 3) {

			diffculty++;

		}else{
		    
		    if(milSecForMoleStay >= 500){
		        
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

	std::cerr << "Would you like to continue? (y/n)";
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

bool Game::CheckIfBoardFilled() {

	int numberOfSpaces = (diffculty + 1) * (diffculty + 1);
	int molesOnBoard = 0;

	for (int i = 0; i < board.GetSize() - 1; i++) {

		for (int j = 0; j < board.GetSize() - 1; j++) {

			if (board.GetBoardValue(i, j) == 'O') {

				molesOnBoard++;

			}

		}

	}

	if (numberOfSpaces == molesOnBoard) {

		return true;

	}
	else {

		return false;

	}

}

void Game::Countdown() {

	for (int i = 5; i > 0; i--) {

		std::cerr << "Starting in " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}

}

void Game::GameLoop() {

	do {

		std::thread userInput(GetUserHitLocation);
		Countdown();

		do {

			DeployMole();
			board.DisplayBoard();
			FindUserInputInArray(hitLocation);
			CheckMole();
			board.DisplayBoard();

		} while (hits + misses < 10);

		ClearScreen();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		std::cerr << "End Of Game " << totalGames << "!" << std::endl << std::endl;
		std::cout << "Press any key to continue." << std::endl;
		needUserHit = false;
		userInput.join();


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

bool Game::CheckMoleLocation(Mole mole) {

	if ('O' == board.GetBoardValue(mole.GetMoleLocation(0), mole.GetMoleLocation(1))) {

		return false;

	}
	else {

		return true;

	}

}



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

void Game::DidHit() {

	if (hitLocation[0] != -1 && hitLocation[1] != -1) {

		if ('O' == board.GetBoardValue(hitLocation[0], hitLocation[1])) {

			board.UpdateHit(hitLocation[0], hitLocation[1]);
			newUserHit = 0;
			oldUserHit = 0;

			std::cerr << "Hit!";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			hits++;


		}
		else {

			newUserHit = 0;
			oldUserHit = 0;

		}

	}

}

void Game::FindUserInputInArray(int inputloc[2]) {

	bool foundInput = false;

	if (oldUserHit != newUserHit) {
		for (int i = 0; i < 7; i++) {

			if ((i % 2) == 0) {

				for (int j = 0; j < 7; j++) {

					if (newUserHit == board.GetControls(i, j)) {

						inputloc[0] = i;
						inputloc[1] = j;
						foundInput = true;

					}

				}

			}

		}

		oldUserHit = newUserHit;

	}

	if (!foundInput) {

		inputloc[0] = -1;
		inputloc[1] = -1;

	}

}

void Game::StartGame() {

	int diffcultySelection;
	bool notVaildSelection = true;

	ClearScreen();

	std::cout << "What diffculty level would you like to start at?" << std::endl;
	std::cout << "1. Easy" << std::endl;
	std::cout << "2. Normal" << std::endl;
	std::cout << "3. Hard" << std::endl;

	do {

		diffcultySelection = getch();

		switch (diffcultySelection) {

		case '1':
			notVaildSelection = false;
			diffculty = 1;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;
		case '2':
			notVaildSelection = false;
			diffculty = 2;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;
		case '3':
			notVaildSelection = false;
			diffculty = 3;

			board.SetSize(diffculty);
			board.GenerateBoard();

			ClearScreen();
			GameLoop();
			break;
		default:
			std::cout << "This is not a vaild selection." << std::endl;
			notVaildSelection = true;
			break;
		}
	} while (notVaildSelection);

}

void Game::Menu() {

	int menuSelection;
	bool notVaildSelection = true;

	ClearScreen();

	std::cout << "Welcome to Walmart Greeters\' \"Whack a mole\" game!" << std::endl;
	std::cout << "1. Play The Game." << std::endl;
	std::cout << "2. Learn How To Play." << std::endl;
	std::cout << "3. Exit" << std::endl;

	do {

		std::cout << "Please choose an option." << std::endl;
		menuSelection = getch();

		switch (menuSelection) {

		case '1':
			notVaildSelection = false;
			StartGame();
			break;
		case '2':
			notVaildSelection = false;
			HowToPlay();
			break;
		case '3':
			notVaildSelection = false;
			ClearScreen();
			std::cout << "Goodbye!";
			exit(0);
			break;
		default:
			std::cout << "This is not a vaild selection." << std::endl;
			notVaildSelection = true;
			break;
		}
	} while (notVaildSelection);
}

void Game::HowToPlay() {

	ClearScreen();

	std::cout << "How to play: " << std::endl << "Look at the table below, each square contains a character that represents a location on " << std::endl;
	std::cout << "the mole hill. When you see a \"O\", press the corresponding character" << std::endl;
	std::cout << "This needs to be done in 3 seconds or less." << std::endl;
	std::cout << "The farther you make it, the shorter that time will be, good luck!" << std::endl;

	board.DisplayControlBoard();

	std::cout << std::endl;
	std::cout << "Press any key to return back to the menu" << std::endl;

	getch();
	Menu();


}

int main() {

	srand(time(0));

	Game game;

	game.Menu();

	return 0;
}
