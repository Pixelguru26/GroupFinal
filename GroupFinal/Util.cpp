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

// Creates a new extensible array in the passed variables
void newArray(double arr[], int& size, int& maxIndex) {
	arr = new double[2];
	size = 2;
	maxIndex = 0;
}
// Appends an item to the extensible array in the passed variables, extends array if needed
void addItem(double arr[], int& size, int& maxIndex, double item) {
	double* arr2;
	maxIndex++;
	if (maxIndex > size) {
		arr2 = new double[size * 2];
		for (int i = 0; i < size; i++) {
			arr2[i] = arr[i];
		}
		delete[] arr;
		arr = arr2;
		size *= 2;
	}
	arr[maxIndex] = item;
}
// Removes an item from an extensible array in the passed variables
void remItem(double arr[], int& size, int& maxIndex, int index) {
	maxIndex--;
	for (int i = index; i < maxIndex; i++) {
		arr[i] = arr[i + 1];
	}
}