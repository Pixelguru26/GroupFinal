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
#include <filesystem>

// project headers
#include "Proj.h"
#include "Util.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

int main() {
	char chart[15][30];
	//string* sales = new string[2];
	vector<string> sales;
	vector<string> movies;
	int i = 0;
	for (auto& p : fs::directory_iterator("Movies")) {
		movies.push_back(p.path().filename().string());
		loadChart(p.path().string() + "\\SeatAvailability.txt", chart);
		saveChart(p.path().string() + "\\SeatAvailability.txt", chart);
		loadSales(p.path().string() + "\\Sales.txt", sales);
		saveSales(p.path().string() + "\\Sales.txt", sales);
		//cout << "MOVIE " << i << " : " << p.path().string() + "\\SeatAvailability.txt" << endl;
	}

	int input;
	bool running = true;

	// simple standard number display settings for money.
	cout << setprecision(2) << fixed << showpoint;

	// all functionality?
	while (running) {
		input = displayMenu(0, running, chart, movies, sales);
	}

	return 0;
}