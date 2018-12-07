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
#include "Proj.h"
#include "Util.h"

using namespace std;

int main() {
	char chart[15][30];
	double* sales = new double[2];
	int saleSize = 2;
	int saleCount = 0;
	loadChart("SeatAvailability.txt",chart);
	loadSales("Sales.txt", sales, saleSize, saleCount);
	int input;
	bool running = true;

	// simple standard number display settings for money.
	cout << setprecision(2) << fixed << showpoint;

	// core loop and interaction functionality.
	while (running) {
		input = displayMenu();

		switch (input-1) {
		case 0:
			requestTickets(chart, sales, saleSize, saleCount);
			break;
		case 1:
			findTickets(chart, sales, saleSize, saleCount);
			break;
		case 2:
			displaySeats(chart);
			break;
		case 3:
			salesReport(chart, sales, saleSize, saleCount);
			break;
		case 4:
			resetAvailability(chart, sales, saleSize, saleCount);
			break;
		case 5:
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