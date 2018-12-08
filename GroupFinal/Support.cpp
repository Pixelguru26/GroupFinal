#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Util.h"

using namespace std;

// supporting function implementations
//	takes chart of seats and displays them on screen
void displaySeats(char chart[15][30]) {
	// column number indicator
	//	padding for row indicator space
	cout << endl;
	cout << string(sizeof("Row #XX: ") / sizeof(char) - 1, ' ');
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
	reader.clear();
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
	reader.close();
}
//	takes file name and chart, writes seat data to file as a block
void saveChart(string fileName, char chart[15][30]) {
	ofstream writer;
	writer.clear();
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
//	???
double loadSales(string fileName, vector<string>& arr) {
	ifstream reader;
	string buffer;
	reader.clear();
	reader.open(fileName);
	arr.clear();
	if (reader.good()) {
		while (getline(reader, buffer)) {
			arr.push_back(buffer);
		}
	}
	reader.close();
	return 0; // legacy, I can't change it now.
}
//	???
void saveSales(string fileName, vector<string>& arr) {
	ofstream writer;
	writer.clear();
	writer.open(fileName);
	for (int i = 0; i < arr.size(); i++) {
		writer << arr[i] << endl;
	}
	writer.close();
}
//	???
double displaySales(vector<string>& arr) {
	stringstream ss;
	double total = 0;
	double price;
	int x, y;
	for (int i = 0; i < arr.size(); i++) {
		ss << arr[i];
		ss >> price;
		ss.ignore();
		ss >> x;
		ss.ignore();
		ss >> y;
		ss.ignore();
		if (x == -1) {
			cout << "PURCHASE #" << i + 1 << ": multipurchase. Seats: " << y << ", cost: $" << price << endl;
			total += price;
		}
		else {
			total += price;
			cout << "PURCHASE #" << i + 1 << ": row #" << y << " column #" << x << " cost: $" << price << endl;
		}
	}
	return total;
}
//	takes row of a seat and returns the price of that seat
double getPrice(int row) {
	return 16 - row;
}
//	finds the first available seat past [sx,sy] in reading order.
bool findSeat(char chart[15][30], int& x, int& y, int sx, int sy)
{
	x = -1;
	y = -1;
	for (int i = (sy * 30 + sx) + 1; i < 15 * 30; i++) {
		sy = i / 30;
		sx = i % 30;
		cout << sx << " " << sy << endl;
		if (chart[sy][sx] == '#') {
			x = sx;
			y = sy;
			return true;
		}
	}
	return false;
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