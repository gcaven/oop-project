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

//split the x/yGen bit into separate function
void Human::generateLocation(Board board, Human *humans[]) {
	int xGen = qrand()%(10+1);
	int yGen;
	if (enemy) {
		yGen = qrand()%((11) - 8) + 8;
	} else {
		yGen = qrand()%(2);
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
	for (int i = 0; i < 6; i++) {
		if (humans[i] != nullptr)
			//this could put it back on a spot taken by another
			//need to track others all at once?
			//idk
			while (humans[i]->x == this->x && humans[i]->y == this->x) {
				xGen = qrand()%(10+1);
				int yGen;
				if (enemy) {
					yGen = qrand()%((11) - 8) + 8;
				} else {
					yGen = qrand()%(2);
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
