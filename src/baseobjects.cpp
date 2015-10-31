#include <iostream>
#include <string>
#include "baseobjects.h"
using namespace std;

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
	tiles = new int[width * height];
	generate();
}

void Board::generate() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Tile tile(PLAIN);
			put(tile);
		}
 	}
 	return;
}

Tile Board::get(int x, int y) {
	return tiles[index(x,y)];
}

void Board::put(int x, int y, Tile tile) {
	tiles[index(x,y)] = tile;
	return;
}

int Board::index(int x, int y) const {
	return x + width*y;
}

Tile::Tile(Terrain type) {
	setType(type);
}

void Tile::setType(Terrain type) {
	this->type = type;
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
	return;
}

int Human::initiativeRoll() {
	return rand() % 20 + 1
}

void Enemy::makeAMove() {
	return;
}