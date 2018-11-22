// Game subproject file

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

// project headers
#include "Game.h"

using namespace std;

// constant declarations/definitions

// forward declarations
void displayWorld(int** world, int width, int height);
int** createWorld(int width, int height);
void modifyWorld(int** world, int width, int height, int x, int y, char v);
char readWorld(int** world, int width, int height, int x, int y);
int* addEntity(int** entities, int* entityCount, int* entityMax, int x, int y, int type, int health);
void removeEntity(int** entities, int* entityCount, int* entityMax, int index);

// main function
void game() {
	// action log, to be displayed in UI
	string log[10];

	// character and world basic data
	int** world;
	int* charX, charY, health;
	int entities[1][4];
	int entityCount = 1, entityMax = 1;

	string statNames[] = {
		"maxHealth"
	};
	int stats[] = {
		10
	};
}

// supporting function implementations
