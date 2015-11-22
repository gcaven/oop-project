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
	this->name = namesVector.at(qrand()%namesVector.size());
	alive = true;
	this->health = qrand()%((30+1) - 10) + 10;
	this->currentHealth = health;
	this->speed = qrand()%((3+1) - 1) + 1;
	this->attack = qrand()%((10+1) - 2) + 2;
	this->defense = qrand()%((10+1) - 2) + 2;
	this->dexterity = qrand()%(3+1);
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

void Human::generateLocation(Board board) {
	int xGen = qrand()%(10+1);
	int yGen;
	if (enemy) {
		yGen = qrand()%((11) - 8) + 8;
	} else {
		yGen = qrand()%(2);
	}
	/*while (board.get(x,y).getType() == BOULDER) {
		xGen = qrand()%(10+1);
		int yGen;
		if (enemy) {
			yGen = qrand()%((11) - 8) + 8;
		} else {
			yGen = qrand()%(2);
		}	
	}*/
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
