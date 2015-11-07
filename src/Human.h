#include <string>
#include <qglobal.h>

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