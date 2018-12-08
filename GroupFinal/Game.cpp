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
const int SPAWNRATE = 5;

// forward declarations
int attack(int enemies[WWIDTH][WHEIGHT], int x, int y, int dir, int type, int power, bool knockback);
void displayWorld(char world[WWIDTH][WHEIGHT], int playerX, int playerY, int playerDirection);
void readWorld(char world[WWIDTH][WHEIGHT], string file);
bool movePlr(char world[WWIDTH][WHEIGHT], int& plrX, int& plrY, int newX, int newY);

// main function
void game() {
	srand(time(NULL));

	// world and entity data
	char mainWorld[WWIDTH][WHEIGHT];
	int enemies[WWIDTH][WHEIGHT];
	int spawnTimer = 0;

	// player data
	int plrX = WWIDTH/2;
	int plrY = WHEIGHT/2;
	int plrD = 0; // Direction: lrud | 0123
	int plrH = 10;
	int gil = 0;
	int wood = 0;
	int art = 0;
	double plrLvl = 0;


	// game state vars
	bool running = true;
	string input;
	string msg;

	readWorld(mainWorld, "Overworld.txt");
	while (running) {
		system("CLS");
		displayWorld(mainWorld, plrX, plrY, plrD);
		// display game stats
		cout << "LVL: " << (int)plrLvl << " || " << string(fmod(plrLvl, 1) * 10, '=') << string(10 - fmod(plrLvl, 1) * 10, ' ') << " || " << endl;
		cout << "HP: " << string(plrH, '+') << endl;
		cout << "Gil $: " << gil << "\tWood T: " << wood << "\tArt @: " << art << endl;
		cout << '[' << msg << ']' << endl;
		cout << ((plrLvl >= 5) ? "x: Drk Strike" : "LVL 5") << ((plrLvl >= 10) ? ", z: Elc Storm" : ", LVL 10") << ((plrLvl >= 15) ? ", c: Frz Arc" : ", LVL 15") << ((plrLvl >= 20) ? ", v: Dfc Wrath" : ", LVL 20") << endl;
		// get input
		cout << "\n>>>";
		cin >> input;
		for (int i = 0; i < input.length(); i++) {
			input[i] = __ascii_toupper(input[i]);
		}

		// the dreaded IFS
		switch (input[0]) {
		case 'W':
			movePlr(mainWorld, plrX, plrY, plrX, plrY - 1);
			break;
		case 'A':
			movePlr(mainWorld, plrX, plrY, plrX - 1, plrY);
			break;
		case 'S':
			movePlr(mainWorld, plrX, plrY, plrX, plrY + 1);
			break;
		case 'D':
			movePlr(mainWorld, plrX, plrY, plrX + 1, plrY);
			break;
		case 'X':
			if (plrLvl >= 5) {

			}
			break;
		case 'Z':
			if (plrLvl >= 10) {

			}
			break;
		case 'C':
			if (plrLvl >= 15) {

			}
			break;
		case 'V':
			if (plrLvl >= 20) {

			}
			break;
		default:
			if (input == "QUIT")
				running = false;
		}
	}
}

void knock(int ax, int ay, int bx, int by, int enemies[WWIDTH][WHEIGHT]) {
	int cx = bx + (ax - bx);
	int cy = by + (ay - by);
	enemies[cx][cy] += enemies[bx][by];
	enemies[bx][by] = 0;
}
int attack(int enemies[WWIDTH][WHEIGHT], int x, int y, int dir, int type, int power, bool knockback) {
	int tx = x;
	int ty = y;
	int kills = 0;
	switch (dir) {
	case 0:
		tx--;
		break;
	case 1:
		tx++;
		break;
	case 2:
		ty--;
		break;
	case 3:
		ty++;
		break;
	}
	int& enemy = enemies[tx][ty];
	switch (type) {
	case 0:
		if (!enemy > 0) return 0;
		// basic attack
		power += rand() % 5 - 2;
		enemy = clamp(enemy - power + enemy / 5, 0, enemy);
		if (enemy <= 0) {
			kills++;
		}
		if (knockback) {
			knock(x, y, tx, ty, enemies);
		}
		break;
	case 1:
		if (!enemy > 0) return 0;
		// dark strike
		enemy = clamp(enemy - power / 1.5, 0, enemy);
		if (enemy <= 0) {
			kills++;
		}
		if (knockback) {
			knock(x, y, tx, ty, enemies);
		}
		break;
	case 2:
		// electric storm
		enemy = clamp(enemy - power / 2, 0, enemy);
		for (int i = 0; i < rand() % 3 + 1; i++) {
			tx = x + rand() % 3 - 1;
			ty = y + rand() % 3 - 1;
			if (enemies[tx][ty]) {
				enemies[tx][ty] = clamp(enemies[tx][ty] - power / 2, 0, enemies[tx][ty]);
				if (enemies[tx][ty] <= 0) {
					kills++;
				}
			}
		}
	case 3:
		// frozen arc
		if (dir == 0 || dir == 1) {
			for (int i = -1; i < 2; i++) {
				if (enemies[tx][ty+i] > 0 && enemies[tx][ty+i] <= power) {
					kills++;
				}
				enemies[tx][ty + i] = clamp(enemies[tx][ty + i] - power, 0, enemies[tx][ty + i]);
				if (knockback) {
				}
			}
		}
		else {
			for (int i = -1; i < 2; i++) {
				if (enemies[tx + i][ty] > 0 && enemies[tx + i][ty] <= power) {
					kills++;
				}
				enemies[tx+i][ty] = clamp(enemies[tx+i][ty] - power, 0, enemies[tx+i][ty]);
			}
		}
	case 4:
		// deific wrath
		if (enemy && enemy <= power * 2) {
			kills++;
		}
		enemy -= power * 2;
		for (int dx = -1; dx < tx + 1; dx++) {
			for (int dy = -1; dy < ty + 1; dy++) {
				if (enemies[dx][dy] > 0 && enemies[dx][dy] <= power * 2) {
					kills++;
				}
				enemies[dx][dy] -= power * 2;
			}
		}
	}
	return kills;
}
void enemyAI(char world[WWIDTH][WHEIGHT], int enemies[WWIDTH][WHEIGHT], int& playerX, int& playerY, int playerDirection, int& plrLvl, int& plrH, int& spawnTimer) {
	static string enemyTypes = "0123456789?";
	int spawnType;
	int spawnX, spawnY;
	int movX, movY;
	int dist;
	spawnTimer++;
	if (spawnTimer > SPAWNRATE) {
		spawnTimer -= SPAWNRATE;
		spawnType = rand() % (plrLvl/2);
		spawnX = rand() % WWIDTH;
		spawnY = rand() % WHEIGHT;
		switch (world[spawnX][spawnY]) {
		case ' ':
		case '=':
			world[spawnX][spawnY] += spawnType;
		}
	}

	for (int x = 0; x < WWIDTH; x++) {
		for (int y = 0; y < WHEIGHT; y++) {
			if (enemies[x][y] > 0) {
				// basic behavior calculation
				dist = (playerX - x)*(playerX - x) + (playerY - y)*(playerY - y);
				movX = x;
				movY = y;
				if (enemies[x][y] < 5 || dist < 4*4) {
					// player seeking behavior
					if (playerX < x - 1) {
						movX--;
					}
					else if (playerX > x + 1) {
						movX++;
					}
					if (playerY < y - 1) {
						movY--;
					}
					else if (playerY > y + 1) {
						movY++;
					}
				}
				else {
					// random walk behavior
					movX = x + rand() % 3 - 1;
					movY = y + rand() % 3 - 1;
				}
				// apply movement
				switch (world[movX][y]) {
				case ' ':
				case '=':
					break;
				default:
					movX = x;
				}
				switch (world[x][movY]) {
				case ' ':
				case '=':
					break;
				default:
					movY = y;
				}
				switch (world[movX][movY]) {
				case ' ':
				case '=':
					break;
				default:
					movX = x;
					movY = y;
				}
				enemies[movX][movY] += enemies[x][y];
				enemies[x][y] = 0;
				// apply attack behavior
				if (dist <= 1) {
					plrH -= enemies[x][y] / 4;
					// knockback from high levels
					if (enemies[x][y] > plrLvl * 2) {
						playerX += (playerX - x);
						playerY += (playerY - y);
					}
				}
			}
		}
	}
}
void displayWorld(char world[WWIDTH][WHEIGHT], int playerX, int playerY, int playerDirection)
{
	static char buffer[WWIDTH][WHEIGHT];
	for (int x = 0; x < WWIDTH; x++) {
		for (int y = 0; y < WHEIGHT; y++) {
			buffer[x][y] = world[x][y];
		}
	}
	switch (playerDirection) {
	case 0:
		buffer[playerX][playerY] = '<';
	case 1:
		buffer[playerX][playerY] = '>';
	case 2:
		buffer[playerX][playerY] = '^';
	case 3:
		buffer[playerX][playerY] = 'v';
	}
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
	// ignoring weird fuckery at the beginning.
	reader.ignore(3);
	// spaces are important
	reader >> noskipws;
	// read tiles
	for (int y = 0; y < WHEIGHT; y++) {
		for (int x = 0; x < WWIDTH; x++) {
			reader >> world[x][y];
		}
		// ignore endline characters
		reader.ignore();
	}
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