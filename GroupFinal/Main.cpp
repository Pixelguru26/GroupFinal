// Main project file

/*
Members:
	Blake Johns
	Ryan Morgan
	Caleb Tomlinson
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
void loadChart(string fileName, char chart[15][30]);
void saveChart(string fileName, char chart[15][30]);
void resetChart(string fileName, char chart[15][30]);
double getPrice(int row);
bool cinFailCheck();
int displayMenu();
//	menu options
void requestTickets(char chart[15][30]);
void salesReport(char chart[15][30]);
void resetAvailability(char chart[15][30]);
void quitMenu(bool& running);

int main() {
	char chart[15][30];
	loadChart("SeatAvailability.txt",chart);
	int input;
	bool running = true;

	cout << setprecision(2) << fixed << showpoint;

	while (running) {
		input = displayMenu();

		switch (input-1) {
		case 0:
			requestTickets(chart);
			break;
		case 1:
			displaySeats(chart);
			break;
		case 2:
			salesReport(chart);
			break;
		case 3:
			resetAvailability(chart);
			break;
		case 4:
			quitMenu(running);
			break;
		case 41:
			game();
			break;
		default:
			cout << input << " is not a valid menu option." << endl;
		}
		system("PAUSE");
	}

	return 0;
}

// menu function implementations
//	displays the main menu, and accepts/returns an input selection
int displayMenu() {
	int ret;
	do {
		system("CLS");
		cout << "Please make a selection from the following menu: " << endl;
		cout << "1 - Request tickets" << endl;
		cout << "2 - Display seating" << endl;
		cout << "3 - Display sales report" << endl;
		cout << "4 - Reset availiability" << endl;
		cout << "5 - Quit" << endl;
		cout << ">> ";
		cin >> ret;
	} while (cinFailCheck());
	return ret;
}
//	performs ticket request action, defaults to game if all spaces unavailable
void requestTickets(char chart[15][30]) {
	int ticketCount;
	int row, column;
	int* rows;
	int* columns;
	double price = 0;
	bool available = true;
	char confirmation;

	cout << "The seating chart is as follows, with seats marked # being available: " << endl;
	displaySeats(chart);

	cout << "How many tickets would you like to purchase?\n>> ";
	cin >> ticketCount;

	rows = new int[ticketCount];
	columns = new int[ticketCount];

	// request ticket information
	for (int i = 0; i < ticketCount; i++) {
		// receive and validate ticket
		cout << "Ticket " << i + 1 << " Row: ";
		do {
			cin >> row;
		} while (row < 1 || row > 15);
		cout << "Ticket " << i + 1 << " Column: ";
		do {
			cin >> column;
		} while (column < 1 || column > 30);
		rows[i] = row-1;
		columns[i] = column-1;
	}
	// test results
	for (int i = 0; i < ticketCount; i++) {
		if (chart[rows[i]][columns[i]] == '#') {
			price += getPrice(rows[i]);
		}
		else {
			available = false;
			break;
		}
	}
	if (available) {
		cout << "Your total price comes out to $" << price << endl;
		cout << "Please confirm this puchase (Y/n): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			for (int i = 0; i < ticketCount; i++) {
				chart[rows[i]][columns[i]] = '*';
			}
			saveChart("SeatAvailability.txt", chart);
			cout << "The purchase has been confirmed, and the seats reserved." << endl;
		}
		else {
			cout << "The purchase has been declined." << endl;
		}
	}
	else {
		bool doGame = true;
		for (int y = 0; y < 15; y++) {
			for (int x = 0; x < 30; x++) {
				if (chart[y][x] != '*') {
					doGame = false;
					break;
				}
			}
		}
		if (doGame) {
			game();
		}
	}
}
//	displays a sales report based on seat information
void salesReport(char chart[15][30]) {
	int sales = 0;
	double total = 0;
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 30; x++) {
			if (chart[y][x] == '*') {
				sales++;
				total += getPrice(y);
			}
		}
	}
	cout << "Seats sold: " << sales << endl;
	cout << "Revenue: $" << total << endl;
}
//	displays a confirmation, then resets seat availability
void resetAvailability(char chart[15][30]) {
	char input;
	cout << "Are you sure you wish to clear all seat availability information and sales?\nThis cannot be undone. (Y/n): ";
	cin >> input;
	if (input == 'Y' || input == 'y') {
		resetChart("SeatAvailability.txt", chart);
	}
}
//	quit confirmation
void quitMenu(bool& running) {
	char response;
	cout << "Do you really want to quit? (Y/n)" << endl;
	cin >> response;
	if (response == 'y' || response == 'Y') {
		running = false;
	}
}

// supporting function implementations
//	takes chart of seats and displays them on screen
void displaySeats(char chart[15][30]) {
	// column number indicator
	//	padding for row indicator space
	cout << endl;
	cout << string(sizeof("Row #XX: ")/sizeof(char) - 1, ' ');
	//	indicator display
	for (int x = 1; x <= 30; x++) {
		cout << x % 10 << ' ';
	}
	cout << endl;
	// primary rendering
	for (int y = 0; y < 15; y++) {
		cout << "Row #" << setw(2) << y + 1 << ": "; // row number indicator
		// row display
		for (int x = 0; x < 30; x++) {
			cout << chart[y][x] << ' ';
		}
		cout << endl;
	}
}
//	takes file name and returns char[15][30] containing a block of seat data, read from the file or populated empty by default.
void loadChart(string fileName, char chart[15][30]) {
	ifstream reader;
	reader.open(fileName);
	// "DNE" case - file will be created later if it does not exist.
	if (!reader.good()) {
		for (int y = 0; y < 15; y++) {
			// populate rows with empty seats
			for (int x = 0; x < 30; x++) {
				chart[y][x] = '#';
			}
		}
	}
	else {
		// read file
		for (int y = 0; y < 15; y++) {
			// read in to rows
			for (int x = 0; x < 30; x++) {
				reader >> chart[y][x];
			}
		}
	}
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
//	takes file name and chart, resets chart and file.
void resetChart(string fileName, char chart[15][30]) {
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 30; x++) {
			chart[y][x] = '#';
		}
	}
	saveChart(fileName, chart);
}
//	takes row of a seat and returns the price of that seat
double getPrice(int row) {
	return 16 - row;
}
//	takes no args, fixes cin fails, returns cin.fail()
bool cinFailCheck() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		return true;
	}
	return false;
}