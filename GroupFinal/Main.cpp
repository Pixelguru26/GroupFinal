// Main project file

/*
Members:
	Blake
	Caleb Tomlinson
	Ryan

*/

// core headers
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

// project headers
#include "Game.h"

using namespace std;

// constant declarations/definitions

// forward declarations
void displaySeats(char chart[15][30]);
char** loadChart(string fileName);
void saveChart(string fileName, char chart[15][30]);
int displayMenu();
//	menu options
void requestTickets();
void salesReport();
void quitMenu(bool& running);

int main() {
	char chart[15][30];
	int input;
	bool running = true;

	while (running) {
		input = displayMenu();

		switch (input) {
		case 0:
			requestTickets();
			break;
		case 1:
			salesReport();
			break;
		case 2:
			quitMenu(running);
			break;
		}
	}

	system("PAUSE");
	return 0;
}

// menu function implementations
//	displays the main menu, and accepts/returns an input selection
int displayMenu() {
	// TODO
}
//	performs ticket request action, defaults to game if space unavailable
void requestTickets() {
	// TODO
}
//	displays a sales report based on seat information
void salesReport() {
	// TODO
}
//	quit confirmation
void quitMenu(bool& running) {
	// TODO
}

// supporting function implementations
//	takes chart of seats and displays them on screen
void displaySeats(char chart[15][30]) {
	// column number indicator
	//	padding for row indicator space
	cout << string(' ', sizeof("Row #XX: ") - 1);
	//	indicator display
	for (int x = 0; x < 30; x++) {
		cout << x % 10;
	}
	// primary rendering
	for (int y = 0; y < 15; y++) {
		cout << "Row #" << setw(2) << y + 1 << ": "; // row number indicator
		// row display
		for (int x = 0; x < 30; x++) {
			cout << chart[y][x];
		}
		cout << endl;
	}
}
//	takes file name and returns char[15][30] containing a block of seat data, read from the file or populated empty by default.
char** loadChart(string fileName) {
	ifstream reader;
	reader.open(fileName);
	char** ret;
	ret = new char*[15]; // 15-length array of char pointers (arrays)
	// "DNE" case - file will be created later if it does not exist.
	if (!reader.good()) {
		for (int y = 0; y < 15; y++) {
			ret[y] = new char[30]; // declare individual char arrays
			// populate rows with empty seats
			for (int x = 0; x < 30; x++) {
				ret[y][x] = '#';
			}
		}
	}
	else {
		// read file
		for (int y = 0; y < 15; y++) {
			ret[y] = new char[30]; // declare individual char arrays
			// read in to rows
			for (int x = 0; x < 30; x++) {
				reader >> ret[y][x];
			}
		}
	}
	return ret;
}
//	takes file name and chart, writes seat data to file as a block
void saveChart(string fileName, char chart[15][30]) {
	ofstream writer;
	writer.open(fileName);
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 30; x++) {
			writer << chart[y][x];
		}
		writer << endl;
	}
	writer.close();
}