#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include "Tile.h"

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
	return type;
}

std::string Tile::getTypeAsString() {
	switch(type) {
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