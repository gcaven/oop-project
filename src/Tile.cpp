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
	defenseBonus = 0;
	navigable = true;
	rangedPossible = true;
	switch(type) {
		case PLAIN:
			break;
		case BOULDER:
			navigable = false;
			break;
		case WATER:
			offenseBonus = -1;
			defenseBonus = -1;
			rangedPossible = false;
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
			return "B";
		case 2:
			return "W";
	}
}

bool Tile::isOccupied() {
	if(character != nullptr) {
		return true;
	}
	return false;
}

Human Tile::getCharacter() {
	if(isOccupied()) {
		return character;
	}
}

void Tile::setCharacter(Human guy) {
	character = guy;
}



