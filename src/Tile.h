#include "Terrain.h"

class Tile {
private:
	Terrain type;
	//These are bonuses when >0, maluses when <0.
	int offenseBonus;
	int rangedOffenseBonus;
	int defenseBonus;
	int rangedDefenseBonus;
	int speedBonus;
	int navigable; //false for boulders
	int rangedPossible;

public:
	Tile();
	Tile(Terrain type);
	void setType(Terrain type);

	Terrain getType();
	std::string getTypeAsString();
};