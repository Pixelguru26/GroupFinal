#include <string>
#include <vector>

#pragma once
// Support functions
void displaySeats(char chart[15][30]);
void loadChart(std::string fileName, char chart[15][30]);
void saveChart(std::string fileName, char chart[15][30]);
void resetChart(std::string fileName, char chart[15][30]);
double loadSales(std::string fileName, std::vector<std::string>& arr);
void saveSales(std::string fileName, std::vector<std::string>& arr);
double getPrice(int row);
bool findSeat(char chart[15][30], int& x, int& y, int sx, int sy);
bool cinFailCheck();
int displayMenu(int state, bool& running, char chart[15][30], std::vector<std::string>& movies, std::vector<std::string>& sales);
double displaySales(std::vector<std::string>& arr);
bool admin();
bool confirm(std::string prompt = "Are you sure?");

// General Utils

void swap(int& a, int& b);
int clamp(int v, int a, int b);