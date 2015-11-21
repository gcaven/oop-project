#include <string>
#include <qglobal.h>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include <vector>
#include "Item.h"

class Human {
public:
	std::string name;
	bool alive;
	bool enemy;
	unsigned int health;
	unsigned int currentHealth;
	unsigned int speed;
	unsigned int attack;
	unsigned int defense;
	unsigned int x;
	unsigned int y;
	//dexterity describes range of ranged attacks
	unsigned int dexterity;
	Human();
	void useItem(Item item);
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