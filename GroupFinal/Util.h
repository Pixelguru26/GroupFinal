#include <string>

#pragma once
// Support functions
void displaySeats(char chart[15][30]);
void loadChart(std::string fileName, char chart[15][30]);
void saveChart(std::string fileName, char chart[15][30]);
void resetChart(std::string fileName, char chart[15][30]);
double loadSales(std::string fileName, double arr[], int& size, int& maxIndex);
void saveSales(std::string fileName, double arr[], int& size, int& maxIndex);
double getPrice(int row);
bool findSeat(char chart[15][30], int& x, int& y, int sx, int sy);
bool cinFailCheck();
int displayMenu();

// General Utils
// Extensible double stack/array
//void newArray(double arr[], int& size, int& maxIndex);
void addItem(double arr[], int& size, int& maxIndex, double item);
void remItem(double arr[], int& size, int& maxIndex, int index);