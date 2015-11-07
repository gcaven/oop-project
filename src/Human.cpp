#include "Human.h"

int Human::initiativeRoll() {
    qsrand(time(NULL));
    return qrand()%(20+1);
    return 0;
}

void Enemy::makeAMove() {
	return;
}