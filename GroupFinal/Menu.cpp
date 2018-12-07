// Menu option implementations

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
#include "Proj.h"
#include "Util.h"

using namespace std;


// menu function implementations
//	displays the main menu, and accepts/returns an input selection
int displayMenu() {
	int ret;
	do {
		system("CLS");
		cout << "Please make a selection from the following menu: " << endl;
		cout << "1 - Request tickets" << endl;
		cout << "2 - Find tickets" << endl;
		cout << "3 - Display seating" << endl;
		cout << "4 - Display sales report" << endl;
		cout << "5 - Reset availability" << endl;
		cout << "6 - Quit" << endl;
		cout << ">> ";
		cin >> ret;
	} while (cinFailCheck());
	return ret;
}
//	performs ticket request action
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
		rows[i] = row - 1;
		columns[i] = column - 1;
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
		cout << "Please confirm this purchase (Y/n): ";
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
}
//	finds ticket locations
void findTickets(char chart[15][30]) {
	int ticketCount;
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
		if (findSeat(chart, rows[i], columns[i], i == 0 ? -1 : rows[i - 1], i == 0 ? 0 : columns[i - 1])) {
			price += getPrice(rows[i]);
		}
		else {
			cout << "Sorry, seat #" << i + 1 << " is unavailable. Try again." << endl;
			return;
		}
	}
	if (available) {
		cout << "Your total price comes out to $" << price << endl;
		cout << "Please confirm this purchase (Y/n): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			for (int i = 0; i < ticketCount; i++) {
				chart[columns[i]][rows[i]] = '*';
			}
			saveChart("SeatAvailability.txt", chart);
			cout << "The purchase has been confirmed, and the seats reserved." << endl;
		}
		else {
			cout << "The purchase has been declined." << endl;
		}
	}
	else {
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
	string pass;
	cout << "Are you sure you wish to clear all seat availability information and sales?\nThis cannot be undone. (Y/n): ";
	cin >> input;
	if (input == 'Y' || input == 'y') {
		cout << "Please enter the password: ";
		cin >> pass;
		if (pass == "admin")
		{
			resetChart("SeatAvailability.txt", chart);
		}
		else {
			cout << "Incorrect password. Returning to main menu." << endl;
		}
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