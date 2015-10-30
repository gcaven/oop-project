#include <iostream>
#include <string>
#include <ncurses.h>

using namespace std;
//probably none of this works

int main() {
	Board board = Board.initialize(15,15);
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

public:
	void initialize(int width, int height) {
		this->width = width;
		this->height = height;
		tiles = new int[width * height];
		//generate the board
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
	int defenseBonus = 0;
	int speedBonus = 0;
	int navigable = true; //false for boulders
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