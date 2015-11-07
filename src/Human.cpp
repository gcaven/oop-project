#include "Human.h"

Human::Human() {
	//figure out name picking logic
	/*std::ifstream infile("names.txt");
	std::string line;

	while (std::getline(infile, line)) {
		
	}*/
	this->name = "I. M. Aplaceholder" + std::to_string(qrand()%(100+1));
	this->health = qrand()%(30+1);
	this->speed = qrand()%(3+1);
	this->attack = qrand()%(10+1);
	this->defense = qrand()%(10+1);
	this->dexterity = qrand()%(10+1);
}

int Human::initiativeRoll() {
    qsrand(time(NULL));
    return qrand()%(20+1);
    return 0;
}

void Enemy::makeAMove() {
	return;
}

Ally::Ally() : Human() {

}

Enemy::Enemy() : Human() {

}
