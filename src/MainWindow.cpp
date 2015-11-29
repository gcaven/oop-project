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
	QObject::connect(targetA, SIGNAL(clicked()), this, SLOT(attackTargetASlot()));
	QObject::connect(targetB, SIGNAL(clicked()), this, SLOT(attackTargetBSlot()));
	QObject::connect(targetC, SIGNAL(clicked()), this, SLOT(attackTargetCSlot()));
	actionsLayout->addWidget(targetA);
	actionsLayout->addWidget(targetB);
	actionsLayout->addWidget(targetC);
	targetA->hide();
	targetB->hide();
	targetC->hide();

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
    		humans[i] = &enemies[k];
    		humans[i]->setId(i);
        	turnQueue.enqueue(enemies[k]);
        	k++;
    	} else {
    		generateLocation(&board, &allies[j]);
    		humans[i] = &allies[j];
    		humans[i]->setId(i);
        	turnQueue.enqueue(allies[j]);
        	j++;
    	}
    	
    }
    //show human locations on the board UI
    QFont font;
	font.setBold(true);
	font.setPointSize(18);
    for (int i=0; i < 6; i++) {
    	int x = humans[i]->x;
    	int y = humans[i]->y;
    	QTableWidgetItem *item = table->takeItem(y,x);
    	if (item != nullptr) {
    		std::string boardName = humans[i]->name.substr(0,2);
    		item->setText(QString::fromStdString(boardName));
	    	if (humans[i]->enemy)
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
        Human temp = turnQueue.dequeue();
        name = temp.name;
        turnQueue.enqueue(temp);
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(name));
        if (temp.enemy)
        	item->setBackgroundColor(QColor(255,128,100));
        item->setFlags(Qt::ItemIsEditable);
        turnOrder->setItem(i,0,item);
    }
	return;
}

void MainWindow::startGameSlot() {
	currentCharacter = turnQueue.dequeue();
	std::string statsString = currentCharacter.name;
	if (!currentCharacter.enemy)
		statsString += "\n\nAdventurer";
	else 
		statsString += "\n\nBandit";
	statsString += "\n\nHP: " + std::to_string(currentCharacter.currentHealth) + "/" + std::to_string(currentCharacter.health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter.attack) + ", DEX: " + std::to_string(currentCharacter.dexterity);
	statsString += "\n\nDEF: " + std::to_string(currentCharacter.defense) + ", SPD: " + std::to_string(currentCharacter.speed);
	statsString += "\n\nX: " + std::to_string(currentCharacter.x) + ", Y: " + std::to_string(currentCharacter.y);
	stats->setText(QString::fromStdString(statsString));
	statsLayout->removeWidget(buttonStart);
	delete buttonStart;
	statsLayout->addWidget(stats);
	buttonA->setEnabled(true);
	buttonR->setEnabled(true);
	buttonM->setEnabled(true);
	buttonEnd->setEnabled(true);
	console->append("Let the Adventure Begin!<br>");
	std::string consoleText = currentCharacter.name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
	//highlight current player on board
	if (!currentCharacter.enemy) {
		QTableWidgetItem *item = table->takeItem(currentCharacter.y,currentCharacter.x);
		if (item != nullptr) {
			item->setForeground(QColor(255,77,234));
			table->setItem(currentCharacter.y,currentCharacter.x,item);
		}
	}
}

void MainWindow::attackSlot() {
	std::string consoleText = currentCharacter.name;
	consoleText += " is winding up for an attack.";
	console->append(QString::fromStdString(consoleText));

	Human target;
	
	//hide actions buttons
	theSitch->hide();
	buttonA->hide();
	buttonR->hide();
	buttonM->hide();
	buttonEnd->hide();
	//show targets buttons
	QString name1 = QString::fromStdString(humans[0]->name);
	QString name2 = QString::fromStdString(humans[2]->name);
	QString name3 = QString::fromStdString(humans[4]->name);
	targetA->setText(name1);
	targetB->setText(name2);
	targetC->setText(name3);
	targetA->show();
	targetB->show();
	targetC->show();

	//if position of target is adjacent to current
	/*if((target.x == currentCharacter.x) || (target.y == currentCharacter.y)) {
		if((target.y == currentCharacter.y - 1 || target.y == currentCharacter.y + 1) || (target.x == currentCharacter.x - 1 || target.x == currentCharacter.x + 1)) {
			int damage = currentCharacter.attack - target.defense;
			if(damage < 0)
				damage = 0;
			else{
				target.health -= damage;
			}

			consoleText = currentCharacter.name + " has dealt " + std::to_string(damage) + " to " + target.name + ".";
			console->append(QString::fromStdString(consoleText));
			
			//if attack kills target
			if(target.health <= 0){
				target.alive = false;
				consoleText = currentCharacter.name + " has been felled.";
				console->append(QString::fromStdString(consoleText));
			}
			stopAttacking();
		}
		else {
			consoleText = "Cannot attack.";
			console->append(QString::fromStdString(consoleText));
			attackSlot();
		}
	} 
	//if not, current cannot attack the specified target
	else {
		consoleText = "Cannot attack.";
		console->append(QString::fromStdString(consoleText));
		attackSlot();
	}*/
	stopAttacking();
}

void MainWindow::attackTargetASlot() {
	int x = currentCharacter.x;
	int y = currentCharacter.y;
	if ((humans[2]->x == x+1 || humans[2]->x == x-1) && (humans[2]->y == y+1 || humans[2]->y == y-1)) {
		attack(2);
	} else {
		std::string consoleText = humans[2]->name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackTargetBSlot() {
	int x = currentCharacter.x;
	int y = currentCharacter.y;
	if ((humans[4]->x == x+1 || humans[4]->x == x-1) && (humans[4]->y == y+1 || humans[4]->y == y-1)) {
		attack(4);
	} else {
		std::string consoleText = humans[2]->name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attackTargetCSlot() {
	int x = currentCharacter.x;
	int y = currentCharacter.y;
	if ((humans[6]->x == x+1 || humans[6]->x == x-1) && (humans[6]->y == y+1 || humans[6]->y == y-1)) {
		attack(6);
	} else {
		std::string consoleText = humans[2]->name + " is not close enough to attack!";
		console->append(QString::fromStdString(consoleText));
	}
}

void MainWindow::attack(int index) {

}

void MainWindow::rangedSlot() {
	std::string consoleText = currentCharacter.name;
	consoleText += " is readying their bow.";
	console->append(QString::fromStdString(consoleText));

	//button stuff to get target
	Human *current = &currentCharacter;
	Human target;
	std::string targetname;

	/*bool stop = false;
	while(!stop) {
		
		//if position of target is on a straight x or y path to target
		if(target.x == currentCharacter.x || target.y == currentCharacter.y) {
			//if current can reach target with their dexterity stat
			if( ((abs(target.x - currentCharacter.x)) <= currentCharacter.dexterity) || ((abs(target.y - currentCharacter.y)) <= currentCharacter.dexterity)) {
				int damage = currentCharacter.attack - target.defense;
				if(damage < 0)
					damage = 0;
				else{
					target.health -= damage;
				}

				consoleText = currentCharacter.name + " has dealt " +  std::to_string(damage) + " to " + target.name + ".";
				console->append(QString::fromStdString(consoleText));

				//if attack kills target
				if(target.health <= 0){
					target.alive = false;
					consoleText = currentCharacter.name + " has been felled.";
					console->append(QString::fromStdString(consoleText));
				}
				stop = true;
			}
			else {			
				consoleText = "Cannot attack this player.";
				console->append(QString::fromStdString(consoleText));
			}
		} 
		
		//if position of target is on a diagonal path from current
		


		//if not, current cannot attack the specified target
		else {
			consoleText = "Cannot attack this player.";
			console->append(QString::fromStdString(consoleText));
		}
	}*/
}

void MainWindow::stopAttacking() {
	//hide attack buttons
	targetA->hide();
	targetB->hide();
	targetC->hide();

	//show action buttons
	theSitch->show();
	buttonA->show();
	buttonR->show();
	buttonM->show();
	buttonEnd->show();
	//disable attack button
	buttonA->setEnabled(false);
}

void MainWindow::moveSlot() {
	std::string consoleText = currentCharacter.name;
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
	moves = currentCharacter.speed;
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
	int xNew = currentCharacter.x + x;
	//board UI reverses y, we reverse it here to match what players would expect
	int yNew = currentCharacter.y - y;
	if (checkLocation(&board,xNew,yNew)) {
		int xOld = currentCharacter.x;
		int yOld = currentCharacter.y;
		currentCharacter.x += x;
		currentCharacter.y -= y;
		board.tiles[xOld][yOld].setCharacter(nullptr);
		board.tiles[xNew][yNew].setCharacter(&currentCharacter);
	    QTableWidgetItem *item = table->takeItem(yOld,xOld);
	    item->setText("");
	    table->setItem(yOld,xOld,item);
	    item = table->takeItem(yNew,xNew);
	    QFont font;
		font.setBold(true);
		font.setPointSize(18);
	    if (item != nullptr) {
	    	std::string boardName = currentCharacter.name.substr(0,2);
	    	item->setText(QString::fromStdString(boardName));
	    	if (currentCharacter.enemy)
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
		std::string consoleText = currentCharacter.name;
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
	if (!currentCharacter.enemy) {
		QTableWidgetItem *item = table->takeItem(currentCharacter.y,currentCharacter.x);
		if (item != nullptr) {
			item->setForeground(QColor(0,0,0));
			table->setItem(currentCharacter.y,currentCharacter.x,item);
		}	
	}
	turnQueue.enqueue(currentCharacter);
	console->append("");
	//get the new guy
	currentCharacter = turnQueue.dequeue();
	std::string statsString = currentCharacter.name;
	std::string consoleText = currentCharacter.name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
	//if enemy, disable buttons
	if (!currentCharacter.enemy) {
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
	statsString += "\n\nHP: " + std::to_string(currentCharacter.currentHealth) + "/" + std::to_string(currentCharacter.health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter.attack) + ", DEX: " + std::to_string(currentCharacter.dexterity);
	statsString += "\n\nDEF: " + std::to_string(currentCharacter.defense) + ", SPD: " + std::to_string(currentCharacter.speed);
	statsString += "\n\nX: " + std::to_string(currentCharacter.x) + ", Y: " + std::to_string(currentCharacter.y);
	stats->setText(QString::fromStdString(statsString));
	//increment the turn order UI
	QTableWidgetItem *old = turnOrder->takeItem(0,0);
	for (int i = 1; i < turnQueue.getSize()+1; i++) {
		QTableWidgetItem *pushup = turnOrder->takeItem(i,0);
		turnOrder->setItem(i-1,0,pushup);
	}
	turnOrder->setItem(turnQueue.getSize(),0,old);
	//hook for enemy AI
	if (currentCharacter.enemy) {
		Enemy *currentEnemy = (Enemy*) &currentCharacter;
		currentEnemy->makeAMove();
		endTurnSlot();
	} else {
		//hightlight current player on board
		QTableWidgetItem *item = table->takeItem(currentCharacter.y,currentCharacter.x);
		if (item != nullptr) {
			item->setForeground(QColor(255,77,234));
			table->setItem(currentCharacter.y,currentCharacter.x,item);
		}	
	}
	show();
}

