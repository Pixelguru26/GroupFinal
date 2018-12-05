// Game subproject file

/*
Members:
	Blake Johns
	Ryan Morgan
	Caleb Tomlinson
*/

// core headers
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

// project headers
#include "Game.h"
#include "Util.h"

using namespace std;

// constant declarations/definitions
//	world dimensions
const int WWIDTH = 64;
const int WHEIGHT = 16;
const int ENEMYSIZE = 4;
const char PLRCHAR = 'P';
const int SPAWNLIMIT = 5;

// forward declarations
void displayWorld(char world[WWIDTH][WHEIGHT], int* enemies[], int count, char enemyVisuals[], int playerX, int playerY);
void readWorld(char world[WWIDTH][WHEIGHT], string file);
void addEnemy(int* enemies[], int& count, int type, int x, int y, int health);
void remEnemy(int* enemies[], int& count, int i);
bool movePlr(char world[WWIDTH][WHEIGHT], int& plrX, int& plrY, int newX, int newY);

// main function
void game() {
	// world and entity data
	char mainWorld[WWIDTH][WHEIGHT];
	int count = 0;
	int* enemies[1];

	// const stats
	char enemyVisuals[] = {'x'};

	// player data
	int plrX = WWIDTH/2;
	int plrY = WHEIGHT/2;
	int plrH = 20;
	double plrLvl = 0;

	// game state vars
	bool running = true;
	string input;

	readWorld(mainWorld, "Overworld.txt");
	while (running) {
		system("CLS");
		displayWorld(mainWorld, enemies, count, enemyVisuals, plrX, plrY);
		cout << "\n>>>";
		cin >> input;
		for (int i = 0; i < input.length(); i++) {
			input[i] = __ascii_toupper(input[i]);
		}
		// "turn" functionality I didn't actually want to write all the params for

		// the dreaded IFS
		if (input == "W") {
			movePlr(mainWorld, plrX, plrY, plrX, plrY - 1);
		}
		else if (input == "A") {
			movePlr(mainWorld, plrX, plrY, plrX - 1, plrY);
		}
		else if (input == "S") {
			movePlr(mainWorld, plrX, plrY, plrX, plrY + 1);
		}
		else if (input == "D") {
			movePlr(mainWorld, plrX, plrY, plrX + 1, plrY);
		}
		else {
			running = false;
		}
	}
	cout << "The game is currently WIP. Please try again later." << endl;
}

// supporting function implementations
//	add item to dynamic array of enemies
//	takes enemies array (int*[]), enemy count, new enemy type, new enemy x, new enemy y, and new enemy type
void addEnemy(int* enemies[], int& count, int type, int x, int y, int health) {
	int lastCount = count;
	count++;
	int lastPow = (int)log2(lastCount)+1;
	int currPow = (int)log2(count)+1;
	if (currPow > lastPow) {
		int size = (int)pow(2, currPow);
		int** ret = new int*[size];

		for (int i = 0; i < size; i++) {
			if (i < lastCount) {
				ret[i] = enemies[i];
			}
			else {
				ret[i] = new int[ENEMYSIZE];
			}
		}
	}
	else {
		enemies[count] = new int[ENEMYSIZE];
		enemies[count][0] = x;
		enemies[count][1] = y;
		enemies[count][2] = type;
		enemies[count][3] = health;
	}
}
void displayWorld(char world[WWIDTH][WHEIGHT], int* enemies[], int count, char enemyVisuals[], int playerX, int playerY)
{
	static char buffer[WWIDTH][WHEIGHT];
	for (int x = 0; x < WWIDTH; x++) {
		for (int y = 0; y < WHEIGHT; y++) {
			buffer[x][y] = world[x][y];
		}
	}
	for (int i = 0; i < count; i++) {
		buffer[enemies[i][0]][enemies[i][1]] = enemyVisuals[enemies[i][3]];
	}
	buffer[playerX][playerY] = PLRCHAR;
	for (int y = 0; y < WHEIGHT; y++) {
		for (int x = 0; x < WWIDTH; x++) {
			cout << buffer[x][y];
			//cout << '#';
		}
		cout << endl;
	}
}
void readWorld(char world[WWIDTH][WHEIGHT], string file)
{
	ifstream reader;
	reader.open(file);
	reader >> noskipws;
	for (int y = 0; y < WHEIGHT; y++) {
		for (int x = 0; x < WWIDTH; x++) {
			reader >> world[x][y];
		}
		reader.ignore();
	}
}
void remEnemy(int* enemies[], int& count, int i) {
	delete[] enemies[i];
	count--;
}
//	move the player to a new location, or refuse if said location is blocked
bool movePlr(char world[WWIDTH][WHEIGHT], int & plrX, int & plrY, int newX, int newY)
{
	if (newX >= 0 && newY >= 0 && newX < WWIDTH && newY < WHEIGHT) {
		switch (world[newX][newY]) {
		case ' ':
		case '=':
			plrX = newX;
			plrY = newY;
			return true;
		default:
			return false;
		}
	}
	return false;
}