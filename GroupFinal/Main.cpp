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
#include "Game.h"
#include "Proj.h"
#include "Util.h"

using namespace std;
namespace fs = std::experimental::filesystem::v1;

int main() {
	char chart[15][30];
	//string* sales = new string[2];
	vector<string> sales(2);
	int saleSize = 2;
	int saleCount = 0;
	int movieCount = 0;
	int movieSize = 2;
	for (auto& p : fs::directory_iterator("Movies")) {
		movieCount++;
		if (movieCount > movieSize) {
			movieSize *= 2;
		}
	}
	string* movies = new string[movieCount];
	int i = 0;
	for (auto& p : fs::directory_iterator("Movies")) {
		movies[i++] = p.path().filename().string();
		loadChart(p.path().string() + "\\SeatAvailability.txt", chart);
		saveChart(p.path().string() + "\\SeatAvailability.txt", chart);
		saleCount = 0;
		loadSales(p.path().string() + "\\Sales.txt", sales, saleSize, saleCount);
		cout << "MOVIE " << i << " : " << p.path().string() + "\\SeatAvailability.txt" << endl;
	}
	loadChart("SeatAvailability.txt",chart);
	loadSales("Sales.txt", sales, saleSize, saleCount);
	system("PAUSE");

	int input;
	bool running = true;

	// simple standard number display settings for money.
	cout << setprecision(2) << fixed << showpoint;

	// all functionality?
	while (running) {
		input = displayMenu(0, running, chart, movies, movieSize, movieCount, sales, saleSize, saleCount);
		system("PAUSE");
	}

	return 0;
}