#ifndef TILE
#define TILE

#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include "Terrain.h"
#include "Human.h"

class Tile {
private:
	Terrain type;
	//These are bonuses when >0, maluses when <0.
	int offenseBonus;
	int defenseBonus;
	int rangedPossible;
	Human *character;

public:
	Tile();
	Tile(Terrain type);
	void setType(Terrain type);
	Terrain getType();
	std::string getTypeAsString();
	bool isOccupied();
	Human* getCharacter();
	void setCharacter(Human *guy);
};

#endif
