#ifndef HUMAN
#define HUMAN

#include <string>
#include <qglobal.h>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFont>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "Item.h"

class Human {
public:
	unsigned int id;
	std::string name;
	bool alive;
	bool enemy;
	unsigned int health;
	unsigned int currentHealth;
	unsigned int speed;
	unsigned int attack;
	unsigned int defense;
	int x;
	int y;
	//dexterity describes range of ranged attacks
	unsigned int dexterity;
	Human();
	void useItem(Item item);
	void setId(unsigned int id);
};

class Ally : public Human {
public:
	Ally();
};

class Enemy : public Human {
public:
	Enemy();
};
int randomInt(int max, int min);

#endif

