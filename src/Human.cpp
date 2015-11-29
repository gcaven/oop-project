#include "Human.h"

Human::Human() {
	//pick random name
	//this file lives in the .app
	//don't know where it goes in windows, prob in the same folder as the .exe
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
	name = namesVector.at(randomInt(namesVector.size()-1,0));
	alive = true;
	//generate stuff ((max+1)-min)+min)
	//change this to min + (rand() % (int)(max - min + 1)) for more even distribution
	health = randomInt(30,10);
	currentHealth = health;
	speed = randomInt(3,2);
	attack = randomInt(10,5);
	defense = randomInt(9,5);
	dexterity = randomInt(3,0);
	if (dexterity == 1) {
		dexterity = 0;
	}
	x = -1;
	y = -1;
}

void Human::useItem(Item item) {
	return;
}

void Human::setId(unsigned int id) {
	this->id = id;
}

void Enemy::makeAMove(int r,Human *h) {
	//enemy AI will live here

    //if there is an adjacent player
    if(r>0)
    {
        //if there is an adjacent player to the right
        if(r==1){
            if(h[0].x==x+1&&h[0].y==y){
                //h[0].health=h[0].health-
            }
        }

        //if there is an adjacent player directly below
        else if(r==2){

        }
        //if there is an adjacent player to the left
        else if(r==3){

        }
        //if there is an adjacent player directly above
        else{

        }

    }	
}

Ally::Ally() : Human() {
	enemy = false;
}

Enemy::Enemy() : Human() {
	enemy = true;
}

int randomInt(int max, int min) {
	int rando = (min + (qrand() % (int)(max - min + 1)));
	//classic rando
	return rando;
}


