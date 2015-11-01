enum Terrain{
	PLAIN = 0,
	HILL = 1, //defensive bonus, ranged bonus
	TREES = 2, //defensive bonus, no ranged attacks
	DITCH = 3, //defensive malus, especially ranged
	BOULDER = 4, //impassible
	WATER = 5, //speed, offensive malus, no ranged attacks. defensive malus to ranged
};

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

class Board {
private:
	Tile* tiles;
	int width;
	int height;
	void generate();

public:
	Board(int width, int height);
	Tile get(int x, int y);
	void put(int x, int y, Tile tile);
	int index(int x, int y);
	void destroy();
};

class Human {
private:
	std::string name;
	unsigned int health;
	unsigned int speed;
	unsigned int attack;
	unsigned int defense;
	//dexterity describes range of ranged attacks
	unsigned int dexterity;
public:
	int initiativeRoll();
};

class Ally : public Human {

};

class Enemy : public Human {
public:
	void makeAMove();
};

class Item {
private:
	std::string name;
	//these describe the effects they have on characters
	int health;
	int speed;
	int attack;
	int defense;
	int dexterity;
	int duration; // length of effect in turns. if negative, is infinite
};