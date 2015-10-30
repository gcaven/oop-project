#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;


int main() {
	Board board(15,15);
	//base game loop
	initscr();
	refresh();
	getch();
	endwin();

	return 0;
}

class Board {
private:
	int* tiles;
	int width;
	int height;

	void generate() {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				//make some logic for random tile types
			}
 		}
	}

public:
	Board(int width, int height) {
		this->width = width;
		this->height = height;
		tiles = new int[width * height];
		generate();
	}

	Tile get(int x, int y) {
		return tiles[index(x,y)];
	}

	int index(int x, int y) const {
		return x + width*y;
	}

};

class Tile {
private:
	Terrain type;
	//These are bonuses when >0, maluses when <0.
	int offenseBonus = 0;
	int rangedOffenseBonus = 0;
	int defenseBonus = 0;
	int rangedDefenseBonus = 0;
	int speedBonus = 0;
	int navigable = true; //false for boulders
	int rangedPossible = true;

	void setType(Terrain type) {
		switch(type) {
			PLAIN:
				break;
			HILL:
				defenseBonus = 2;
				rangedOffenseBonus = 2;
				rangedDefenseBonus = 1;
				break;
			TREES;
				defenseBonus = 3;
				rangedPossible = false;
				rangedDefenseBonus = 3;
				speedBonus = -1;
				break;
			DITCH;
				defenseBonus = -2;
				rangedDefenseBonus = -3;
				break;
			BOULDER;
				navigable = false;
				break;
			WATER;
				speedBonus = -3;
				offenseBonus = -1;
				rangedPossible = false;
				rangedDefenseBonus = -2;
				break;
		}
	}

public:
	Tile(Terrain type) {
		setType(type);
	} 
};

enum Terrain{
	PLAIN = 'plain',
	HILL = 'hill', //defensive bonus, ranged bonus
	TREES = 'trees', //defensive bonus, no ranged attacks
	DITCH = 'ditch', //defensive malus, especially ranged
	BOULDER = 'boulder', //impassible
	WATER = 'water', //speed, offensive malus, no ranged attacks. defensive malus to ranged
};

class Human {
private:
	string name;
	unsigned int health;
	unsigned int speed;
	unsigned int attack;
	unsigned int defense;
	//dexterity describes range of ranged attacks
	unsigned int dexterity;
public:
	int initiativeRoll() {
		return rand() % 20 + 1
	}
};

class Ally : public Human {

};

class Enemy : public Human {
public:
	makeAMove() {
		//ayy lmao
	}
};

class Item {
private:
	string name;
	//these describe the effects they have on characters
	int health;
	int speed;
	int attack;
	int defense;
	int dexterity;
	int duration // length of effect in turns. if negative, is infinite
}