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

    qsrand(time(NULL));
    //generate some humans
    Ally allies[3];
    Enemy enemies[3];
    //place allies(adventurers) on the board, put them into the humans array and the turnqueue
    for (int i=0; i < 3; i++) {
    	allies[i].generateLocation(&board, humans, i);
    	humans[i] = &allies[i];
    	humans[i]->setId(i);
        turnQueue.enqueue(allies[i]);
    }
    //place enemies(bandits) on the board, put them into the humans array and the turnqueue
    for (int i=0; i < 3; i++) {
    	enemies[i].generateLocation(&board, humans, i+3);
    	humans[i+3] = &enemies[i];
    	humans[i]->setId(i+3);
        turnQueue.enqueue(enemies[i]);
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
    		if (humans[i]->enemy)
    			item->setText("B");
    		else 
    			item->setText("A");
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
}

void MainWindow::attackSlot() {
	std::string consoleText = currentCharacter.name;
	consoleText += " is winding up for an attack.";
	console->append(QString::fromStdString(consoleText));
	
	Human *current = &currentCharacter;
	Human target;
	std::string targetname;
	
	/*bool stop = false;
	while(!stop) {

		//dont do this, add buttons to the UI.
		//we shouldn't take any input from the console
		cout << "Enter the name of your target: " << end;
		cin >> targetname;
		
		//if position of target is adjacent to current
		if((target.x == current.x) || (target.y == current.y)) {
			if((target.y == current.y - 1 || target.y == current.y + 1) || (target.x == current.x - 1 || target.x == current.x + 1)) {
				int damage = current.attack - target.defense;
				if(damage < 0)
					damage = 0;
				else{
					target.health -= damage;
				}
				std::cout << "You have dealt " << damage << " to " << target.name << endl;
				stop = true;

				//if attack kills target
				if(target.health <= 0){
					target.alive = false;
					std::cout << target.name << " has been felled." << endl;
				}
			}
			else {
				std::cout << "Cannot attack this player" << endl;
			}
		} 
		//if not, current cannot attack the specified target
		else {
			std::cout << "Cannot attack this player" << endl;
		}
	}*/
}

void MainWindow::rangedSlot() {
	std::string consoleText = currentCharacter.name;
	consoleText += " is readying their bow.";
	console->append(QString::fromStdString(consoleText));

	Human *current = &currentCharacter;
	Human target;
	std::string targetname;

	/*bool stop = false;
	while(!stop) {
		std::cout << "Enter the name of your target: " << endl;
		std::cin >> targetname;
		
		//if position of target is on a straight x or y path to target
		if(target.x == current.x || target.y == current.y) {
			//if current can reach target with their dexterity stat
			if( ((abs(target.x - current.x)) <= current.dexterity) || ((abs(target.y - current.y)) <= current.dexterity)) {
				int damage = current.attack - target.defense;
				if(damage < 0)
					damage = 0;
				else{
					target.health -= damage;
				}
				std::cout << "You have dealt " << damage << " to " << target.name << endl;

				//if attack kills target
				if(target.health <= 0){
					target.alive = false;
					std::cout << target.name << " has been felled." << endl;
				}
				stop = true;
			}
			else {
				std::cout << "Cannot attack this player" << endl;
			}
		} 
		
		//if position of target is on a diagonal path from current
		


		//if not, current cannot attack the specified target
		else {
			std::cout << "Cannot attack this player" << endl;
		}
	}*/
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
	//board UI reverses y, we reverse it here to match what players would expect
	move(0,-1);
}

//move character x+1;
void MainWindow::moveRightSlot() {
	move(1,0);
}

//move character y-1;
void MainWindow::moveDownSlot() {
	//board UI reverses y, we reverse it here to match what players would expect
	move(0,1);
}

//move character x-1;
void MainWindow::moveLeftSlot() {
	move(-1,0);
}

void MainWindow::moveStopSlot() {
	stopMoving();
}

void MainWindow::move(int x,int y) {
	//need to check for boulders, other humans, edges of board
	//probably could share code with generateLocation()
	//helper function file?
	int xOld = currentCharacter.x;
	int yOld = currentCharacter.y;
	currentCharacter.x += x;
	currentCharacter.y += y;
	int xNew = currentCharacter.x;
	int yNew = currentCharacter.y;
    QTableWidgetItem *item = table->takeItem(yOld,xOld);
    item->setText("");
    table->setItem(yOld,xOld,item);
    item = table->takeItem(yNew,xNew);
    QFont font;
	font.setBold(true);
	font.setPointSize(18);
    if (item != nullptr) {
    	if (currentCharacter.enemy)
    		item->setText("B");
    	else 
    		item->setText("A");
    	item->setTextAlignment(Qt::AlignCenter);
    	item->setFont(font);
    	table->setItem(yNew,xNew,item);
    }
    moves--;
    if (moves <= 0) {
		stopMoving();
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
	turnQueue.enqueue(currentCharacter);
	console->append("");
	currentCharacter = turnQueue.dequeue();
	std::string statsString = currentCharacter.name;
	std::string consoleText = currentCharacter.name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
	buttonA->setEnabled(true);
	buttonR->setEnabled(true);
	buttonM->setEnabled(true);
	if (!currentCharacter.enemy)
		statsString += "\n\nAdventurer";
	else 
		statsString += "\n\nBandit";
	statsString += "\n\nHP: " + std::to_string(currentCharacter.currentHealth) + "/" + std::to_string(currentCharacter.health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter.attack) + ", DEX: " + std::to_string(currentCharacter.dexterity);
	statsString += "\n\nDEF: " + std::to_string(currentCharacter.defense) + ", SPD: " + std::to_string(currentCharacter.speed);
	statsString += "\n\nX: " + std::to_string(currentCharacter.x) + ", Y: " + std::to_string(currentCharacter.y);
	stats->setText(QString::fromStdString(statsString));
	QTableWidgetItem *old = turnOrder->takeItem(0,0);
	for (int i = 1; i < turnQueue.getSize()+1; i++) {
		QTableWidgetItem *pushup = turnOrder->takeItem(i,0);
		turnOrder->setItem(i-1,0,pushup);
	}
	turnOrder->setItem(turnQueue.getSize(),0,old);
	show();
}

