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
#include <filesystem>

// project headers
#include "Proj.h"
#include "Util.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

const string ADMINPASS = "*****";
const int PROMOCOUNT = 5;
const string PROMOCODES[] = { "ZIMBABWE", "MOTHERLODE", "EA", "DYGNHP", "SECRET" };
const double PROMOMULTS[] = { 20000, -1, 2, 0.5, .42 };

// menu function implementations
//	displays the main menu, and accepts/returns an input selection
int displayMenu(int state, bool& running, char chart[15][30], string movies[], int & movieSize, int& movieCount, string* sales, int& saleSize, int& saleCount) {
	static int movie = 0;
	double multiplier = 1;
	int ret;
	string buffer;
	bool menuRunning = true;
	bool found = false;
	double total = 0;
	while (menuRunning) {
		do {
			system("CLS");
			switch (state) {
			case 0: // movie selection
				cout << "~= MOVIE SELECT =~" << endl;
				cout << "1 - Admin Menu" << endl;
				for (int i = 0; i < movieCount; i++) {
					cout << i + 2 << " - " << movies[i] << endl;
				}
				break;
			case 1: // admin menu 1
				cout << "A D M I N - 1" << endl;
				cout << "1 - Add a movie" << endl;
				cout << "2 - Remove a movie" << endl;
				cout << "3 - Cancel" << endl;
				break;
			case 2: // main menu
				cout << "~= MAIN MENU =~" << endl;
				cout << "1 - Make a purchase" << endl;
				cout << "2 - Display Seating" << endl;
				cout << "3 - Display Purchases" << endl;
				cout << "4 - Admin Menu" << endl;
				cout << "5 - Quit" << endl;
				break;
			case 3: // purchase menu
				cout << "~= PURCHASE MENU =~" << endl;
				cout << "1 - Purchase a single seat" << endl;
				cout << "2 - Purchase multiple seats" << endl;
				cout << "3 - Find seating" << endl;
				cout << "4 - Apply Discount Code" << endl;
				cout << "5 - Cancel / Finish" << endl;
				break;
			case 4: // admin menu 2
				cout << "A D M I N - 2" << endl;
				cout << "1 - Clear All" << endl;
				cout << "2 - Refund Purchase" << endl;
				cout << "3 - Sales Report" << endl;
				cout << "4 - Cancel / Finish" << endl;
				break;
			}
			cout << ">> ";
			cin >> ret;
		} while (cinFailCheck() && (cout << "Please enter a valid option." << endl));
		switch (state) {
		case 0: // movie list menu
			switch (ret - 1) {
			case 0: // admin menu
				if (admin()) {
					displayMenu(1, running, chart, movies, movieSize, movieCount, sales, saleSize, saleCount);
				}
			default: // loads a theatre and enters the menu with it
				if (ret - 2 >= 0 && ret - 2 < movieCount) {
					movie = ret - 2;
					loadChart("Movies\\" + movies[movie] + "\\SeatAvailability.txt", chart);
					saleCount = 0;
					loadSales("Movies\\" + movies[movie] + "\\SeatAvailability.txt", sales, saleSize, saleCount);
					displayMenu(2, running, chart, movies, movieSize, movieCount, sales, saleSize, saleCount);
				}
				else {
					cout << ret << " is not a valid menu option." << endl;
				}
			}
			break;
		case 1: // movie list admin
			switch (ret - 1) {
			case 0: // add a movie
				cout << "Please enter a name for the new movie: ";
				cin.ignore();
				getline(cin, buffer);
				addItem(movies, movieSize, movieCount, buffer);
				buffer = "Movies\\" + buffer;
				if (!fs::is_directory(buffer) || !fs::exists(buffer)) { // Check if folder exists
					fs::create_directory(buffer); // create folder
				}
				loadChart(buffer + "\\SeatAvailability.txt", chart);
				saveChart(buffer + "\\SeatAvailability.txt", chart);
				break;
			case 1: // remove a movie
				for (int i = 0; i < movieCount; i++) {
					cout << i+1 << " : " << movies[i] << endl;
				}
				cout << "Please select the deletion candidate: ";
				cin >> ret;
				ret--;
				if (!cinFailCheck() && ret >= 0 && ret < movieCount) {
					if (confirm("Are you sure? This cannot be undone.")) {
						cout << "DELETING MOVIE" << endl;
						remItem(movies, movieSize, movieCount, ret);
						fs::remove_all("Moves\\" + movies[ret]);
					}
				}
				break;
			case 2: // cancel
				if (confirm()) {
					menuRunning = false;
					return 0;
				}
				break;
			default:
				cout << ret << " is not a valid menu option." << endl;
			}
			break;
		case 2: // movie menu
			switch (ret - 1) {
			case 0: // purchase menu
				displayMenu(3, running, chart, movies, movieSize, movieCount, sales, saleSize, saleCount);
				break;
			case 1: // display seating
				system("CLS");
				cout << "The seating chart is as follows, with seats marked # being available: " << endl;
				displaySeats(chart);
				break;
			case 2: // display purchases
				system("CLS");
				cout << "The sales history for this movie is as follows, with promo codes hidden:" << endl;
				displaySales(sales, saleSize, saleCount);
				break;
			case 3: // admin menu
				if (admin()) {
					displayMenu(4, running, chart, movies, movieSize, movieCount, sales, saleSize, saleCount);
				}
				break;
			case 4: // cancel
				if (confirm()) {
					menuRunning = false;
					return 0;
				}
				break;
			default:
				cout << ret << " is not a valid menu option." << endl;
			}
			break;
		case 3: // purchase menu
			switch (ret - 1) {
			case 0: // purchase single seat
				system("CLS");
				cout << "The seating chart is as follows, with seats marked # being available: " << endl;
				displaySeats(chart);
				requestTicket(chart, sales, saleSize, saleCount, multiplier);
				saveChart("Movies\\" + movies[movie] + "\\SeatAvailability.txt", chart);
				saveSales("Movies\\" + movies[movie] + "\\Sales.txt", sales, saleSize, saleCount);
				break;
			case 1: // purchase multiple seats
				system("CLS");
				cout << "The seating chart is as follows, with seats marked # being available: " << endl;
				displaySeats(chart);
				requestTickets(chart, sales, saleSize, saleCount, multiplier);
				saveChart("Movies\\" + movies[movie] + "\\SeatAvailability.txt", chart);
				saveSales("Movies\\" + movies[movie] + "\\Sales.txt", sales, saleSize, saleCount);
				break;
			case 2: // find seats
				system("CLS");
				cout << "The seating chart is as follows, with seats marked # being available: " << endl;
				displaySeats(chart);
				findTickets(chart, sales, saleSize, saleCount, multiplier);
				saveChart("Movies\\" + movies[movie] + "\\SeatAvailability.txt", chart);
				saveSales("Movies\\" + movies[movie] + "\\Sales.txt", sales, saleSize, saleCount);
				break;
			case 3: // apply discount
				cout << "Do you have a promo code? If so, enter it below:" << endl;
				cin >> buffer;
				found = false;
				for (int i = 0; i < PROMOCOUNT; i++) {
					if (PROMOCODES[i] == buffer) {
						found = true;
						multiplier *= PROMOMULTS[i];
						cout << "Your promo code has been verified!" << endl;
						cout << "(Please do not enter it again, we will cry)" << endl;
						break;
					}
				}
				if (!found) {
					cout << "Invalid code, please try again." << endl;
				}
				break;
			case 4: // cancel
				if (confirm()) {
					menuRunning = false;
					return 0;
				}
			}
			break;
		case 4: // admin menu
			switch (ret - 1) {
			case 0: // clear all
				if (confirm("Are you sure? This cannot be undone.")) {
					resetChart("Movies\\" + movies[movie] + "\\SeatAvailability.txt", chart);
					saleCount = 0;
					saveSales("Movies\\" + movies[movie] + "\\SeatAvailability.txt", sales, saleSize, saleCount);
				}
				break;
			case 1: // refund a purchase
				displaySales(sales, saleSize, saleCount);
				cout << "Which would you like to refund? >> ";
				cin >> ret;
				ret--;
				if (!cinFailCheck() && ret >= 0 && ret < saleCount) {
					remItem(sales, saleSize, saleCount, ret);
				}
				else {
					cout << "Invalid option. Try again." << endl;
				}
				break;
			case 2: // sales report
				cout << "Sales history is as follows, with promo codes hidden:" << endl;
				total = displaySales(sales, saleSize, saleCount);
				cout << "Total sales from this theatre : " << saleCount << endl;
				cout << "Gross income from this theatre: $" << total << endl;
				break;
			case 3: // cancel
				if (confirm()) {
					menuRunning = false;
					return 0;
				}
			}
			break;
		}
		system("PAUSE");
	}
	return 0;
}

bool admin() {
	string buffer;
	cout << "PLEASE ENTER ADMIN PASSWORD >> ";
	cin >> buffer;
	if (buffer == ADMINPASS) {
		cout << "ENTERING ADMIN MODE..." << endl;
		return true;
	}
	else {
		cout << "INCORRECT PASSWORD." << endl;
		return false;
	}
}
bool confirm(string prompt) {
	string buffer;
	cout << prompt << "(Y/n): ";
	cin >> buffer;
	return (buffer[0] == 'y' || buffer[0] == 'Y');
}
void newSale(string* sales, int& saleSize, int& saleCount, double amount, int x, int y) {
	addItem(sales, saleSize, saleCount, to_string(amount) + "," + to_string(x) + "," + to_string(y));
}
void requestTicket(char chart[15][30], string* sales, int& saleSize, int& saleCount, double multiplier) {
	int row, column;
	cout << "Where would you like to buy a seat?" << endl;
	cout << "Row: ";
	do {
		cin >> row;
	} while ((cinFailCheck() || row < 1 || row > 30) && (cout << "That's not a valid option." << endl));
	cout << "Column: ";
	do {
		cin >> column;
	} while ((cinFailCheck() || column < 1 || column > 30) && (cout << "That's not a valid option." << endl));
	if (chart[row][column] == '*') {
		cout << "That seat is taken. Please try again." << endl;
	}
	else {
		cout << "Perfect! Your purchase comes out to $" << getPrice(row)*multiplier << endl;
		if (confirm("Is this suitable?")) {
			newSale(sales, saleSize, saleCount, getPrice(row)*multiplier, column, row);
		}
	}
}
//	performs ticket request action
void requestTickets(char chart[15][30], string* sales, int& saleSize, int& saleCount, double multiplier) {
	int count;
	double total = 0;
	cout << "How many tickets would you like to purchase? >> ";
	cin >> count;
	if (!cinFailCheck() && count > 0) {
		int* rows = new int[count];
		int* columns = new int[count];
		for (int i = 0; i < count; i++) {
			cout << "Row: ";
			do {
				cin >> rows[i];
			} while ((cinFailCheck() || rows[i] < 1 || rows[i] > 30) && (cout << "That's not a valid option." << endl));
			cout << "Column: ";
			do {
				cin >> columns[i];
			} while ((cinFailCheck() || columns[i] < 1 || columns[i] > 30) && (cout << "That's not a valid option." << endl));
			if (chart[rows[i]][columns[i]] == '*') {
				cout << "That seat is taken. Please try again." << endl;
				return;
			}
			else {
				total += getPrice(rows[i])*multiplier;
			}
		}
		cout << "Perfect! Your purchase comes out to $" << total << endl;
		if (confirm("Is this suitable?")) {
			newSale(sales, saleSize, saleCount, total, -1, count);
		}
	}
	else {
		cout << "That's not a valid option." << endl;
	}
}
//	finds ticket locations
void findTickets(char chart[15][30], string* sales, int& saleSize, int& saleCount, double multiplier) {
	int ticketCount;
	int* rows;
	int* columns;
	double price = 0;
	bool available = true;
	char confirmation;

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
			cout << "Sorry, seat #" << i + 1 << " is unavailable. Your purchase could not be completed." << endl;
			return;
		}
	}
	if (available) {
		price *= multiplier;
		cout << "Your total price comes out to $" << price << endl;
		cout << "Please confirm this purchase (Y/n): ";
		cin >> confirmation;
		if (confirmation == 'Y' || confirmation == 'y') {
			for (int i = 0; i < ticketCount; i++) {
				chart[columns[i]][rows[i]] = '*';
			}
			newSale(sales, saleSize, saleCount, price, -1, ticketCount);
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
void salesReport(char chart[15][30], string* sales, int& saleSize, int& saleCount) {
	int count = 0;
	double total = 0;
	for (int y = 0; y < 15; y++) {
		for (int x = 0; x < 30; x++) {
			if (chart[y][x] == '*') {
				count++;
				total += getPrice(y);
			}
		}
	}
	cout << "Seats sold: " << count << endl;
	cout << "Revenue: $" << total << endl;
}
//	displays a confirmation, then resets seat availability
void resetAvailability(char chart[15][30], string* sales, int& saleSize, int& saleCount) {
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