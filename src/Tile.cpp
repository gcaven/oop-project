#include "Tile.h"

Tile::Tile() {
	setType(PLAIN);
	character = nullptr;
}

Tile::Tile(Terrain type) {
	setType(type);
	character = nullptr;
}

void Tile::setType(Terrain type) {
	this->type = type;
	offenseBonus = 0;
	defenseBonus = 0;
	rangedPossible = true;
	switch(type) {
		case PLAIN:
			break;
		case BOULDER:
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

bool Tile::isOccupiedByPlayer() {
	if (character != nullptr && !character->enemy) {
		return true;
	}
	return false;
}

Human* Tile::getCharacter() {
	if(isOccupied()) {
		return character;
	}
}

void Tile::setCharacter(Human *guy) {
	character = guy;
}



