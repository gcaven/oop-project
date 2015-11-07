#include <string>
#include <qglobal.h>
#include <fstream>
#include <string>

class Human {
public:
	std::string name;
	unsigned int health;
	unsigned int speed;
	unsigned int attack;
	unsigned int defense;
	//dexterity describes range of ranged attacks
	unsigned int dexterity;
	Human();
	int initiativeRoll();
};

class Ally : public Human {
public:
	Ally();
};

class Enemy : public Human {
public:
	Enemy();
	void makeAMove();
};