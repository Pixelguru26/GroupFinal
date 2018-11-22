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
void quitMenu();

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
			quitMenu();
			running = false;
			break;
		case 3:
			game();
		}
	}

	system("PAUSE");
	return 0;
}

// supporting function implementations
