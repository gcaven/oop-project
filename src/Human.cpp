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
	qsrand(time(NULL));
	this->name = namesVector.at(qrand()%namesVector.size());
	this->health = qrand()%((30+1) - 5) + 5;
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
	//enemy AI will live here
	return;
}

Ally::Ally() : Human() {

}

Enemy::Enemy() : Human() {

}
