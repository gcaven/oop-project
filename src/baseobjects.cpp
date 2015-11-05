#include <iostream>
#include <string>
#include <cstdlib>
#include "baseobjects.h"

Board::Board(int width, int height) {
	this->width = width;
	this->height = height;
	Tile **tiles = new Tile*[width];
	for(int i = 0; i < width; ++i) {
    	tiles[i] = new Tile[height];
	}
	//this works here
	Tile tile(WATER);
	tiles[0][0] = tile;
	generate();
}

Tile::Tile() {
	setType(PLAIN);
}

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

Terrain Tile::getType() {
	return this->type;
}

std::string Tile::getTypeAsString() {
	switch(this->type) {
		case 0:
			return "P";
		case 1:
			return "H";
		case 2:
			return "T";
		case 3:
			return "D";
		case 4:
			return "B";
		case 5:
			return "W";
	}
}

void Board::generate() {
	for (int x = 0; x < width; ++x) {
		std::cout << "x: " << x << "\n";
		for (int y = 0; y < height; ++y) {
			std::cout << "y: " << y << "\n";
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
			}
			Tile tile(type);
			//gives segmentation fault here
			tiles[x][y] = tile;
		}
 	}
 	return;
}


Tile Board::get(int x, int y) {
	return tiles[x][y];
}

void Board::put(int x, int y, Tile tile) {
	tiles[x][y] = tile;
	return;
}

void Board::destroy() {
	delete [] tiles;
}

int Human::initiativeRoll() {
	return rand() % 20 + 1;
}

void Enemy::makeAMove() {
	return;
}