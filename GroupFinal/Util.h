#include <string>

#pragma once
// Support functions
void displaySeats(char chart[15][30]);
void loadChart(std::string fileName, char chart[15][30]);
void saveChart(std::string fileName, char chart[15][30]);
void resetChart(std::string fileName, char chart[15][30]);
double loadSales(std::string fileName, vector<string> arr, int& size, int& maxIndex);
void saveSales(std::string fileName, std::string arr[], int& size, int& maxIndex);
double getPrice(int row);
bool findSeat(char chart[15][30], int& x, int& y, int sx, int sy);
bool cinFailCheck();
int displayMenu(int state, bool& running, char chart[15][30], std::string movies[], int & movieSize, int& movieCount, std::string* sales, int& saleSize, int& saleCount);
double displaySales(std::string arr[], int& size, int& maxIndex);
bool admin();
bool confirm(std::string prompt = "Are you sure?");

// General Utils
// Extensible double stack/array
//void newArray(double arr[], int& size, int& maxIndex);
void addItem(double arr[], int& size, int& maxIndex, double item);
void remItem(double arr[], int& size, int& maxIndex, int index);
void addItem(std::string* arr, int& size, int& maxIndex, std::string item);
void remItem(std::string arr[], int& size, int& maxIndex, int index);

void swap(int& a, int& b);
int clamp(int v, int a, int b);