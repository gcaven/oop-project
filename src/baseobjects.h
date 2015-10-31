class Board {
private:
	int* tiles;
	int width;
	int height;

	void generate();

public:
	Board(int width, int height);

	Tile get(int x, int y);

	void put(int x, int y, Tile tile);

	int index(int x, int y);

};

class Tile {
private:
	Terrain type;
	//These are bonuses when >0, maluses when <0.
	int offenseBonus = 0;
	int rangedOffenseBonus = 0;
	int defenseBonus = 0;
	int rangedDefenseBonus = 0;
	int speedBonus = 0;
	int navigable = true; //false for boulders
	int rangedPossible = true;

	void setType(Terrain type);

public:
	Tile(Terrain type);
};

enum Terrain{
	PLAIN = 'plain',
	HILL = 'hill', //defensive bonus, ranged bonus
	TREES = 'trees', //defensive bonus, no ranged attacks
	DITCH = 'ditch', //defensive malus, especially ranged
	BOULDER = 'boulder', //impassible
	WATER = 'water', //speed, offensive malus, no ranged attacks. defensive malus to ranged
};

class Human {
private:
	string name;
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
	makeAMove();
};

class Item {
private:
	string name;
	//these describe the effects they have on characters
	int health;
	int speed;
	int attack;
	int defense;
	int dexterity;
	int duration // length of effect in turns. if negative, is infinite
}