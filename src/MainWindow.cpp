#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
};

void MainWindow::decorate() {
	//actions panel
	QLabel *theSitch = new QLabel("In WATER: ATK down, SPD down\nRanged attacks not possible");
	this->theSitch = theSitch;
	buttonA = new QPushButton("Attack");
	buttonR = new QPushButton("Ranged");
	buttonM = new QPushButton("Move");
	buttonEnd = new QPushButton("End Turn");
	buttonA->setEnabled(false);
	buttonR->setEnabled(false);
	buttonM->setEnabled(false);
	buttonEnd->setEnabled(false);
	QObject::connect(buttonA, SIGNAL(clicked()), this, SLOT(attackSlot()));
    QObject::connect(buttonR, SIGNAL(clicked()), this, SLOT(rangedSlot()));
    QObject::connect(buttonM, SIGNAL(clicked()), this, SLOT(moveSlot()));
    QObject::connect(buttonEnd, SIGNAL(clicked()), this, SLOT(endTurnSlot()));
	actionsLayout = new QVBoxLayout();
	actionsLayout->addWidget(theSitch);
	actionsLayout->addWidget(buttonA);
	actionsLayout->addWidget(buttonR);
	actionsLayout->addWidget(buttonM);
	actionsLayout->addWidget(buttonEnd);

	//start game panel
	buttonStart = new QPushButton("Start");
	QObject::connect(buttonStart, SIGNAL(clicked()), this, SLOT(startGameSlot()));
	stats = new QLabel("");
	statsLayout = new QVBoxLayout();
	statsLayout->addWidget(buttonStart);

	//movement buttons
	buttonMoveUp = new QPushButton("Move Up");
	buttonMoveRight = new QPushButton("Move Right");
	buttonMoveDown = new QPushButton("Move Down");
	buttonMoveLeft = new QPushButton("Move Left");
	buttonMoveStop = new QPushButton("Stop Moving");
	QObject::connect(buttonMoveUp, SIGNAL(clicked()), this, SLOT(moveUpSlot()));
	QObject::connect(buttonMoveRight, SIGNAL(clicked()), this, SLOT(moveRightSlot()));
	QObject::connect(buttonMoveDown, SIGNAL(clicked()), this, SLOT(moveDownSlot()));
	QObject::connect(buttonMoveLeft, SIGNAL(clicked()), this, SLOT(moveLeftSlot()));
	QObject::connect(buttonMoveStop, SIGNAL(clicked()), this, SLOT(moveStopSlot()));
	actionsLayout->addWidget(buttonMoveUp);
	actionsLayout->addWidget(buttonMoveRight);
	actionsLayout->addWidget(buttonMoveDown);
	actionsLayout->addWidget(buttonMoveLeft);
	actionsLayout->addWidget(buttonMoveStop);
	buttonMoveUp->hide();
	buttonMoveRight->hide();
	buttonMoveDown->hide();
	buttonMoveLeft->hide();
	buttonMoveStop->hide();

	//attack buttons
	targetA = new QPushButton();
	targetB = new QPushButton();
	targetC = new QPushButton();
	attackStop = new QPushButton("Return");
	QObject::connect(targetA, SIGNAL(clicked()), this, SLOT(attackTargetASlot()));
	QObject::connect(targetB, SIGNAL(clicked()), this, SLOT(attackTargetBSlot()));
	QObject::connect(targetC, SIGNAL(clicked()), this, SLOT(attackTargetCSlot()));
	QObject::connect(attackStop, SIGNAL(clicked()), this, SLOT(stopAttackingSlot()));
	actionsLayout->addWidget(targetA);
	actionsLayout->addWidget(targetB);
	actionsLayout->addWidget(targetC);
	actionsLayout->addWidget(attackStop);
	targetA->hide();
	targetB->hide();
	targetC->hide();
	attackStop->hide();

	//ranged attack buttons
	rangedTargetA = new QPushButton();
	rangedTargetB = new QPushButton();
	rangedTargetC = new QPushButton();
	rangedStop = new QPushButton("Return");
	QObject::connect(rangedTargetA, SIGNAL(clicked()), this, SLOT(attackRangedTargetASlot()));
	QObject::connect(rangedTargetB, SIGNAL(clicked()), this, SLOT(attackRangedTargetBSlot()));
	QObject::connect(rangedTargetC, SIGNAL(clicked()), this, SLOT(attackRangedTargetCSlot()));
	QObject::connect(rangedStop, SIGNAL(clicked()), this, SLOT(stopRangedSlot()));
	actionsLayout->addWidget(rangedTargetA);
	actionsLayout->addWidget(rangedTargetB);
	actionsLayout->addWidget(rangedTargetC);
	actionsLayout->addWidget(rangedStop);
	rangedTargetA->hide();
	rangedTargetB->hide();
	rangedTargetC->hide();
	rangedStop->hide();

	//turn order panel
	turnOrder = new QTableWidget(6,1);
	turnOrder->setFixedWidth(150);
	turnOrder->setFixedHeight(180);
	QHeaderView *header = turnOrder->horizontalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();
	header = turnOrder->verticalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();

	//put bottom stuff together
	bottomLayout = new QHBoxLayout();
	bottomLayout->addWidget(turnOrder);
	bottomLayout->addLayout(statsLayout);
	bottomLayout->addLayout(actionsLayout);

	//build the board
	int width = 10;
	int height = 10;
	table = new QTableWidget(width,height);
	table->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    table->setMinimumWidth(500);
    table->setMinimumHeight(500);
	table->setShowGrid(false);
	header = table->horizontalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();
	header = table->verticalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();

	//make it happen
	generate(width, height);

	//put left half together
	QVBoxLayout *layoutVert = new QVBoxLayout();
	layoutVert->addWidget(table);
	layoutVert->addLayout(bottomLayout);

	//console
	console = new QTextEdit();
	console->setReadOnly(true);

	//put left half and console together
	QHBoxLayout *topLevel = new QHBoxLayout();
	topLevel->addLayout(layoutVert);
	topLevel->addWidget(console);
	setLayout(topLevel);
	setWindowTitle("Adventure Battle");

	show();
}

void MainWindow::generate(int width, int height) {
	//generate board, fill the table
    QTableWidgetItem curr;
    int type;
     for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            Tile tile = board.get(x,y);
            type = tile.getType();
            QTableWidgetItem *item = new QTableWidgetItem( QString(""));                
            item->setFlags(Qt::ItemIsEditable);
            //tablewidget does things as row, column b/c fuck you
            table->setItem(y,x,item);
            switch(type) {
                case PLAIN:
                    item->setBackgroundColor(QColor(131,245,78));
                    break;
                case BOULDER:
                    item->setBackgroundColor(QColor(168,168,168));
                    break;
                case WATER:
                    item->setBackgroundColor(QColor(129,177,240));
                    break;
            }
        }
    }
    //generate some humans
    Ally allies[3];
    Enemy enemies[3];
    //place allies(adventurers) and enemies(bandits) on the board, put them into the humans array and the turnqueue
    int j = 0;
    int k = 0;
    for (int i=0; i < 6; i++) {
    	if (i%2) {
    		generateLocation(&board, &enemies[k]);
    		humans[i] = enemies[k];
    		humans[i].setId(i);
        	turnQueue.enqueue(i);
        	k++;
    	} else {
    		generateLocation(&board, &allies[j]);
    		humans[i] = allies[j];
    		humans[i].setId(i);
        	turnQueue.enqueue(i);
        	j++;
    	}
    	
    }
    //show human locations on the board UI
    QFont font;
	font.setBold(true);
	font.setPointSize(18);
    for (int i=0; i < 6; i++) {
    	int x = humans[i].x;
    	int y = humans[i].y;
    	QTableWidgetItem *item = table->takeItem(y,x);
    	if (item != nullptr) {
    		std::string boardName = humans[i].name.substr(0,2);
    		item->setText(QString::fromStdString(boardName));
	    	if (humans[i].enemy)
	    		item->setForeground(QColor(250, 107, 107));
	    	else 
	    		item->setForeground(QColor(0,0,0));
    		item->setTextAlignment(Qt::AlignCenter);
    		item->setFont(font);
    		table->setItem(y,x,item);
    	}
    }
    //fill in the turn queue UI
    for (int i=0; i < turnQueue.getSize(); i++) {
        std::string name;
        int index = turnQueue.dequeue();
        Human *temp = &humans[index];
        name = temp->name;
        turnQueue.enqueue(index);
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(name));
        if (temp->enemy)
        	item->setBackgroundColor(QColor(255,128,100));
        item->setFlags(Qt::ItemIsEditable);
        turnOrder->setItem(i,0,item);
    }
	return;
}

void MainWindow::startGameSlot() {
	int index = turnQueue.dequeue();
	currentCharacter = &humans[index];
	std::string statsString = currentCharacter->name;
	if (!currentCharacter->enemy)
		statsString += "\n\nAdventurer";
	else 
		statsString += "\n\nBandit";
	statsString += "\n\nHP: " + std::to_string(currentCharacter->currentHealth) + "/" + std::to_string(currentCharacter->health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter->attack) + ", DEX: " + std::to_string(currentCharacter->dexterity);
	statsString += "\n\nDEF: " + std::to_string(currentCharacter->defense) + ", SPD: " + std::to_string(currentCharacter->speed);
	statsString += "\n\nX: " + std::to_string(currentCharacter->x) + ", Y: " + std::to_string(currentCharacter->y);
	stats->setText(QString::fromStdString(statsString));
	statsLayout->removeWidget(buttonStart);
	delete buttonStart;
	statsLayout->addWidget(stats);
	buttonA->setEnabled(true);
	buttonR->setEnabled(true);
	buttonM->setEnabled(true);
	buttonEnd->setEnabled(true);
	console->append("Let the Adventure Begin!<br>");
	std::string consoleText = currentCharacter->name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
	//highlight current player on board
	if (!currentCharacter->enemy) {
		QTableWidgetItem *item = table->takeItem(currentCharacter->y,currentCharacter->x);
		if (item != nullptr) {
			item->setForeground(QColor(255,77,234));
			table->setItem(currentCharacter->y,currentCharacter->x,item);
		}
	}
}

void MainWindow::attackSlot() {
	std::string consoleText = currentCharacter->name;
	consoleText += " is winding up for an attack.";
	console->append(QString::fromStdString(consoleText));
	
	//hide actions buttons
	theSitch->hide();
	buttonA->hide();
	buttonR->hide();
	buttonM->hide();
	buttonEnd->hide();
	//show targets buttons
	QString name1 = QString::fromStdString(humans[1].name);
	QString name2 = QString::fromStdString(humans[3].name);
	QString name3 = QString::fromStdString(humans[5].name);
	targetA->setText(name1);
	targetB->setText(name2);
	targetC->setText(name3);
	targetA->show();
	targetB->show();
	targetC->show();
	attackStop->show();
}

void MainWindow::attackTargetASlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	if ((humans[1].x == x+1 || humans[1].x == x-1 || humans[1].x == x) && (humans[1].y == y+1 || humans[1].y == y-1 || humans[1].y == y)) {
		attack(1);
	} else {
		std::string consoleText = humans[1].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackTargetBSlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	if ((humans[3].x == x+1 || humans[3].x == x-1 || humans[3].x == x) && (humans[3].y == y+1 || humans[3].y == y-1 || humans[3].y == y)) {
		attack(3);
	} else {
		std::string consoleText = humans[3].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackTargetCSlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	if ((humans[5].x == x+1 || humans[5].x == x-1 || humans[5].x == x) && (humans[5].y == y+1 || humans[5].y == y-1 || humans[5].y == y)) {
		attack(5);
	} else {
		std::string consoleText = humans[5].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attack(int index) {
	Human *target = &humans[index];
	int damage = currentCharacter->attack - (currentCharacter->attack * target->defense/10);
	if(damage < 0)
		damage = 0;
	else 
		target->currentHealth -= damage;

	std::string consoleText = currentCharacter->name + " has dealt " + std::to_string(damage) + " damage to " + target->name + ".";
	console->append(QString::fromStdString(consoleText));
	
	//if attack kills target
	if(target->currentHealth <= 0){
		target->alive = false;
		consoleText = currentCharacter->name + " has been felled.";
		console->append(QString::fromStdString(consoleText));
	}
	stopAttacking();
}

void MainWindow::rangedSlot() {
	if (board.tiles[currentCharacter->x][currentCharacter->y].getType() == WATER) {
		console->append("Cannot use ranged attacks from water!");
	} else {
		std::string consoleText = currentCharacter->name;
		consoleText += " is readying their bow.";
		console->append(QString::fromStdString(consoleText));

		//hide actions buttons
		theSitch->hide();
		buttonA->hide();
		buttonR->hide();
		buttonM->hide();
		buttonEnd->hide();
		//show targets buttons
		QString name1 = QString::fromStdString(humans[1].name);
		QString name2 = QString::fromStdString(humans[3].name);
		QString name3 = QString::fromStdString(humans[5].name);
		rangedTargetA->setText(name1);
		rangedTargetB->setText(name2);
		rangedTargetC->setText(name3);
		rangedTargetA->show();
		rangedTargetB->show();
		rangedTargetC->show();
		rangedStop->show();
	}
}

void MainWindow::attackRangedTargetASlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	int dexterity = currentCharacter->dexterity;
	if (((humans[1].x > x && humans[1].x <= x+dexterity && humans[1].y == y) || (humans[1].x < x && humans[1].x >= x-dexterity && humans[1].y == y)) 
		|| ((humans[1].y > y && humans[1].x <= y+dexterity && humans[1].x == x) || (humans[1].y < x && humans[1].y >= y-dexterity && humans[1].x == x))) {
			attack(1);
	} else {
		std::string consoleText = humans[1].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackRangedTargetBSlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	int dexterity = currentCharacter->dexterity;
	if (((humans[3].x > x && humans[3].x <= x+dexterity && humans[3].y == y) || (humans[3].x < x && humans[3].x >= x-dexterity && humans[3].y == y)) 
		|| ((humans[3].y > y && humans[3].x <= y+dexterity && humans[3].x == x) || (humans[3].y < x && humans[3].y >= y-dexterity && humans[3].x == x))) {
			attack(3);
	} else {
		std::string consoleText = humans[3].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackRangedTargetCSlot() {
	int x = currentCharacter->x;
	int y = currentCharacter->y;
	int dexterity = currentCharacter->dexterity;
	if (((humans[5].x > x && humans[5].x <= x+dexterity && humans[5].y == y) || (humans[5].x < x && humans[5].x >= x-dexterity && humans[5].y == y)) 
		|| ((humans[5].y > y && humans[5].x <= y+dexterity && humans[5].x == x) || (humans[5].y < x && humans[5].y >= y-dexterity && humans[5].x == x))) {
			attack(5);
	} else {
		std::string consoleText = humans[5].name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackRanged(int index) {
	Human *target = &humans[index];
	int damage = currentCharacter->attack - (currentCharacter->attack * target->defense/10);
	if(damage < 0)
		damage = 0;
	else 
		target->currentHealth -= damage;

	std::string consoleText = currentCharacter->name + " has dealt " + std::to_string(damage) + "damage to " + target->name + ".";
	console->append(QString::fromStdString(consoleText));
	
	//if attack kills target
	if(target->currentHealth <= 0){
		target->alive = false;
		consoleText = currentCharacter->name + " has been felled.";
		console->append(QString::fromStdString(consoleText));
	}
	stopRanged();
}

void MainWindow::stopRangedSlot() {
	//hide attack buttons
	rangedTargetA->hide();
	rangedTargetB->hide();
	rangedTargetC->hide();
	rangedStop->hide();

	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
}

void MainWindow::stopRanged() {
	//hide attack buttons
	rangedTargetA->hide();
	rangedTargetB->hide();
	rangedTargetC->hide();
	rangedStop->hide();

	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
	buttonR->setEnabled(false);
}

void MainWindow::stopAttacking() {
	//hide attack buttons
	targetA->hide();
	targetB->hide();
	targetC->hide();
	attackStop->hide();
	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
	//disable attack button
	buttonA->setEnabled(false);
}

void MainWindow::stopAttackingSlot() {
	//hide attack buttons
	targetA->hide();
	targetB->hide();
	targetC->hide();
	attackStop->hide();

	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
}

void MainWindow::moveSlot() {
	std::string consoleText = currentCharacter->name;
	consoleText += " is on the move.";
	console->append(QString::fromStdString(consoleText));
	
	//hide action buttons
	theSitch->hide();
	buttonA->hide();
	buttonR->hide();
	buttonM->hide();
	buttonEnd->hide();
	//show movement buttons
	buttonMoveUp->show();
	buttonMoveRight->show();
	buttonMoveDown->show();
	buttonMoveLeft->show();
	buttonMoveStop->show();
	moves = currentCharacter->speed;
}

//move character y+1;
void MainWindow::moveUpSlot() {
	move(0,1);
}

//move character x+1;
void MainWindow::moveRightSlot() {
	move(1,0);
}

//move character y-1;
void MainWindow::moveDownSlot() {
	
	move(0,-1);
}

//move character x-1;
void MainWindow::moveLeftSlot() {
	move(-1,0);
}

void MainWindow::moveStopSlot() {
	stopMoving();
}

void MainWindow::move(int x,int y) {
	int xNew = currentCharacter->x + x;
	//board UI reverses y, we reverse it here to match what players would expect
	int yNew = currentCharacter->y - y;
	if (checkLocation(&board,xNew,yNew)) {
		int xOld = currentCharacter->x;
		int yOld = currentCharacter->y;
		currentCharacter->x += x;
		currentCharacter->y -= y;
		board.tiles[xOld][yOld].setCharacter(nullptr);
		board.tiles[xNew][yNew].setCharacter(currentCharacter);
	    QTableWidgetItem *item = table->takeItem(yOld,xOld);
	    item->setText("");
	    table->setItem(yOld,xOld,item);
	    item = table->takeItem(yNew,xNew);
	    QFont font;
		font.setBold(true);
		font.setPointSize(18);
	    if (item != nullptr) {
	    	std::string boardName = currentCharacter->name.substr(0,2);
	    	item->setText(QString::fromStdString(boardName));
	    	if (currentCharacter->enemy)
	    		item->setForeground(QColor(250, 107, 107));
	    	else 
	    		item->setForeground(QColor(0,0,0));
	    	item->setTextAlignment(Qt::AlignCenter);
	    	item->setFont(font);
	    	table->setItem(yNew,xNew,item);
	    }
	    moves--;
	    if (moves <= 0) {
			stopMoving();
		}
	} else {
		std::string consoleText = currentCharacter->name;
		consoleText += " cannot move there!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::stopMoving() {
	//hide movement buttons
	buttonMoveUp->hide();
	buttonMoveRight->hide();
	buttonMoveDown->hide();
	buttonMoveLeft->hide();
	buttonMoveStop->hide();
	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
	//disable move button
	buttonM->setEnabled(false);
}

void MainWindow::endTurnSlot() {
	//put current character back in queue
	if (!currentCharacter->enemy) {
		QTableWidgetItem *item = table->takeItem(currentCharacter->y,currentCharacter->x);
		if (item != nullptr) {
			item->setForeground(QColor(0,0,0));
			table->setItem(currentCharacter->y,currentCharacter->x,item);
		}	
	}
	turnQueue.enqueue(currentCharacter->id);
	console->append("");
	//get the new guy
	int index = turnQueue.dequeue();
	currentCharacter = &humans[index];

	std::string statsString = currentCharacter->name;
	std::string consoleText = currentCharacter->name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
	//if enemy, disable buttons
	if (!currentCharacter->enemy) {
		statsString += "\n\nAdventurer";
		buttonA->setEnabled(true);
		buttonR->setEnabled(true);
		buttonM->setEnabled(true);
	} else {
		statsString += "\n\nBandit";
		buttonA->setEnabled(false);
		buttonR->setEnabled(false);
		buttonM->setEnabled(false);
	}
	//show current stats on UI
	statsString += "\n\nHP: " + std::to_string(currentCharacter->currentHealth) + "/" + std::to_string(currentCharacter->health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter->attack) + ", DEX: " + std::to_string(currentCharacter->dexterity);
	statsString += "\n\nDEF: " + std::to_string(currentCharacter->defense) + ", SPD: " + std::to_string(currentCharacter->speed);
	statsString += "\n\nX: " + std::to_string(currentCharacter->x) + ", Y: " + std::to_string(currentCharacter->y);
	stats->setText(QString::fromStdString(statsString));
	//increment the turn order UI
	QTableWidgetItem *old = turnOrder->takeItem(0,0);
	for (int i = 1; i < turnQueue.getSize()+1; i++) {
		QTableWidgetItem *pushup = turnOrder->takeItem(i,0);
		turnOrder->setItem(i-1,0,pushup);
	}
	turnOrder->setItem(turnQueue.getSize(),0,old);
	//hook for enemy AI
	if (currentCharacter->enemy) {
		Enemy *currentEnemy = (Enemy*) &currentCharacter;
        currentEnemy->makeAMove(board.adjPlayer(currentEnemy->x,currentEnemy->y),&humans);
		endTurnSlot();
	} else {
		//hightlight current player on board
		QTableWidgetItem *item = table->takeItem(currentCharacter->y,currentCharacter->x);
		if (item != nullptr) {
			item->setForeground(QColor(255,77,234));
			table->setItem(currentCharacter->y,currentCharacter->x,item);
		}	
	}
	show();
	//if enemy, makeAmove, disable buttons
}

