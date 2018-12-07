// Utility function implementations

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
#include "Util.h"

using namespace std;

// swaps two ints
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
// returns an int clamped within a range
int clamp(int v, int a, int b) {
	return v < a ? a : v > b ? b : v;
}

// Creates a new extensible array in the passed variables
void newArray(double arr[], int& size, int& maxIndex) {
	arr = new double[2];
	size = 2;
	maxIndex = 0;
}

// Appends an item to the extensible array in the passed variables, extends array if needed
void addItem(double arr[], int& size, int& maxIndex, double item) {
	double* arr2 = arr;
	maxIndex++;
	if (maxIndex > size) {
		arr2 = new double[size * 2];
		for (int i = 0; i < size; i++) {
			arr2[i] = arr[i];
		}
		// broken for some reason, this is now a known memleak.
		//delete[] arr;
		arr = arr2;
		size *= 2;
	}
	arr2[maxIndex-1] = item;
}
// Removes an item from an extensible array in the passed variables
void remItem(double arr[], int& size, int& maxIndex, int index) {
	maxIndex--;
	for (int i = index; i < maxIndex; i++) {
		arr[i] = arr[i + 1];
	}
}
// Appends an item to the extensible array in the passed variables, extends array if needed
void addItem(string* arr, int& size, int& maxIndex, string item) {
	string* arr2 = nullptr;
	maxIndex++;
	if (maxIndex >= size) {
		arr2 = new string[size * 2];
		for (int i = 0; i < size; i++) {
			arr2[i] = arr[i];
		}
		arr2[maxIndex - 1] = item;
		//delete[] arr;
		arr = arr2;
		size *= 2;
	}
	else {
		//arr[maxIndex - 1] = item;
	}
}
// Removes an item from an extensible array in the passed variables
void remItem(string arr[], int& size, int& maxIndex, int index) {
	maxIndex--;
	for (int i = index; i < maxIndex; i++) {
		arr[i] = arr[i + 1];
	}
}