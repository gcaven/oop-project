#ifndef ITEM
#define ITEM

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

#endif