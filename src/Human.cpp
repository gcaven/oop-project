#include "Human.h"

Human::Human() {
	//figure out name picking logic
	QMessageBox error;
	QString filename = QCoreApplication::applicationDirPath() + "/names.txt";
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly) || !file.exists()) {
    	QMessageBox::information(0,"error",file.errorString());
	}
	QTextStream in (&file);
	std::vector<std::string> namesVector;
	while(!in.atEnd()) {
		QString line = in.readLine();
		namesVector.push_back(line.toStdString());
	}
	file.close();
	name = namesVector.at(qrand()%namesVector.size());
	alive = true;
	health = qrand()%((30+1) - 10) + 10;
	currentHealth = health;
	speed = qrand()%((3+1) - 1) + 1;
	attack = qrand()%((10+1) - 2) + 2;
	defense = qrand()%((10+1) - 2) + 2;
	dexterity = qrand()%(3+1);
	x = -1;
	y = -1;
}

int Human::initiativeRoll() {
    return qrand()%(20+1);
    return 0;
}

void Human::useItem(Item item) {
	//do this
	return;
}

void Human::setId(unsigned int id) {
	this->id = id;
}

void Human::generateLocation(Board board, Human **humans, int size) {
	//min + (rand() % (int)(max - min + 1))
	int xGen = 0 + qrand()%(int)(9-0+1);
	int yGen;
	if (enemy) {
		yGen = 8 + qrand()%(int)(9-8+1);
	} else {
		yGen = 0 + qrand()%(int)(1-0+1);
	}
	//gettin them memory errors
	/*while (board.get(x,y).getType() == BOULDER) {
		xGen = qrand()%(10+1);
		int yGen;
		if (enemy) {
			yGen = qrand()%((11) - 8) + 8;
		} else {
			yGen = qrand()%(2);
		}	
	}*/
	bool goodlocation = false;
	while (!goodlocation) {
		goodlocation = true;
		for (int i = 0; i < size; i++) {
			if (humans[i]->x == xGen && humans[i]->y == yGen) {
				goodlocation = false;
			}
		}
		if (!goodlocation) {
			xGen = 0 + qrand()%(int)(9-0+1);
			if (enemy) {
				yGen = 8 + qrand()%(int)(9-8+1);
			} else {
				yGen = 0 + qrand()%(int)(1-0+1);
			}
		}
	}
	x = xGen;
	y = yGen;
	return;
}

void Enemy::makeAMove() {
	//enemy AI will live here
	return;
}

Ally::Ally() : Human() {
	enemy = false;
}

Enemy::Enemy() : Human() {
	enemy = true;
}
