#include <iostream>
#include <string>
#include <vector>
#include "baseobjects.h"
using namespace std;

Tile::Tile(Terrain type) {
	setType(type);
}

void Tile::setType(Terrain type) {
	this->type = type;
	offenseBonus = 0;
	rangedOffenseBonus = 0;
	defenseBonus = 0;
	rangedDefenseBonus = 0;
	speedBonus = 0;
	navigable = true;
	rangedPossible = true;
	switch(type) {
		case PLAIN:
			break;
		case HILL:
			defenseBonus = 2;
			rangedOffenseBonus = 2;
			rangedDefenseBonus = 1;
			break;
		case TREES:
			defenseBonus = 3;
			rangedPossible = false;
			rangedDefenseBonus = 3;
			speedBonus = -1;
			break;
		case DITCH:
			defenseBonus = -2;
			rangedDefenseBonus = -3;
			break;
		case BOULDER:
			navigable = false;
			break;
		case WATER:
			speedBonus = -3;
			offenseBonus = -1;
			rangedPossible = false;
			rangedDefenseBonus = -2;
			break;
	}
	return;
}

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
	vector<Tile> tiles(width * height);
	generate();
}

Terrain Tile::getType() {
	return this->type;
}

void Board::generate() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int typenum = rand() % 6;
			Terrain type;
			switch(typenum) {
				case 0:
					type = PLAIN;
					break;
				case 1: 
					type = PLAIN;
					break;
				case 2:
					type = HILL;
					break;
				case 3:
					type = TREES;
					break;
				case 4:
					type = DITCH;
					break;
				case 5:
					type = BOULDER;
					break;
				case 6:
					type = WATER;
					break;
				Tile tile(type);
				put(x,y,tile);
			}
		}
 	}
 	return;
}

Tile Board::get(int x, int y) {
	return tiles.at(index(x,y));
}

void Board::put(int x, int y, Tile tile) {
	tiles.at(index(x,y)] = tile;
	return;
}

int Board::index(int x, int y) {
	return x + width*y;
}

int Human::initiativeRoll() {
	return rand() % 20 + 1;
}

void Enemy::makeAMove() {
	return;
}