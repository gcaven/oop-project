#include <iostream>
#include <string>
#include <cstdlib>
#include <qglobal.h>
#include "Terrain.h"
#ifndef TILE
#define TILE

class Tile {
private:
	Terrain type;
	//These are bonuses when >0, maluses when <0.
	int offenseBonus;
	int defenseBonus;
	int navigable; //false for boulders
	int rangedPossible;
	bool occupado;

public:
	Tile();
	Tile(Terrain type);
	void setType(Terrain type);
	Terrain getType();
	std::string getTypeAsString();
	bool isOccupado();
};

#endif
