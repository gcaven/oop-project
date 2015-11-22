#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
};

void MainWindow::decorate() {
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

	QVBoxLayout *actions = new QVBoxLayout();
	actions->addWidget(theSitch);
	actions->addWidget(buttonA);
	actions->addWidget(buttonR);
	actions->addWidget(buttonM);
	actions->addWidget(buttonEnd);

	buttonStart = new QPushButton("Start");
	QObject::connect(buttonStart, SIGNAL(clicked()), this, SLOT(startGameSlot()));
	stats = new QLabel("");

	statsLayout = new QVBoxLayout();
	statsLayout->addWidget(buttonStart);

	turnOrder = new QTableWidget(6,1);
	turnOrder->setFixedWidth(150);
	turnOrder->setFixedHeight(180);
	QHeaderView *header = turnOrder->horizontalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();
	header = turnOrder->verticalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();
	
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(turnOrder);
	layout->addLayout(statsLayout);
	layout->addLayout(actions);

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

	generate(width, height);

	QVBoxLayout *layoutVert = new QVBoxLayout();
	layoutVert->addWidget(table);
	layoutVert->addLayout(layout);

	QTextEdit *console = new QTextEdit();
	console->setReadOnly(true);

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
                    item->setBackgroundColor(Qt::green);
                    break;
                case HILL:
                    item->setBackgroundColor(Qt::yellow);
                    break;
                case TREES:
                    item->setBackgroundColor(Qt::darkGreen);
                    break;
                case DITCH:
                    item->setBackgroundColor(Qt::darkYellow);
                    break;
                case BOULDER:
                    item->setBackgroundColor(Qt::gray);
                    break;
                case WATER:
                    item->setBackgroundColor(Qt::blue);
                    break;
            }
        }
    }
    qsrand(time(NULL));
    Ally allies[3];
    Enemy enemies[3];
    for (int i=0; i < 3; i++) {
    	allies[i].generateLocation(board, humans);
    	humans[i] = &allies[i];
    	humans[i]->setId(i);
        turnQueue.enqueue(allies[i]);
    }
    for (int i=0; i < 3; i++) {
    	enemies[i].generateLocation(board, humans);
    	humans[i+3] = &enemies[i];
    	humans[i]->setId(i+3);
        turnQueue.enqueue(enemies[i]);
    }
    QFont font;
	font.setBold(true);
    for (int i=0; i < 6; i++) {
    	int x = humans[i]->x;
    	int y = humans[i]->y;
    	//QTableWidgetItem *item = table->takeItem(y,x);
    	//item->setText("H");
    	//item->setTextAlignment(Qt::AlignCenter);
    	//item->setFont(font);
    	//table->setItem(y,x,item);
    }
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
	stats->setText(QString::fromStdString(statsString));
	statsLayout->removeWidget(buttonStart);
	delete buttonStart;
	statsLayout->addWidget(stats);
	buttonA->setEnabled(true);
	buttonR->setEnabled(true);
	buttonM->setEnabled(true);
	buttonEnd->setEnabled(true);
}

void MainWindow::attackSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are attacking! bro!");
	msgBox.exec();

	
	Human *current = &currentCharacter;
	Human target;
	
	//why are you using cout and cin? wont do anything. will need to add text to the console widget.

	/*bool stop = false;
	while(!stop) {
		cout << "Enter the name of your target: " << end;
		cin >> target;
		
		//if position of target is adjacent to current
		if((target.x == current.x) || (target.y == current.y)) {
			if((target.y == current.y - 1 || target.y == current.y + 1) || (target.x == current.x - 1 || target.x == current.x + 1)) {
				int damage = current.attack - target.defense;
				if(damage < 0)
					damage = 0;
				else{
					target.health -= damage;
				}
				cout << "You have dealt " << damage << " to " << target.name << endl;
				stop = true;

				//if attack kills target
				if(target.health <= 0){
					target.alive = false;
					cout << target.name << " has been felled." << endl;
				}
			}
			else {
				cout << "Cannot attack this player" << endl;
			}
		} 
		//if not, current cannot attack the specified target
		else {
			cout << "Cannot attack this player" << endl;
		}
	}*/
}

void MainWindow::rangedSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are attacking from a distance! bruh!");
	msgBox.exec();

	Human *current = &currentCharacter;
	Human target;

	/*bool stop = false;
	while(!stop) {
		cout << "Enter the name of your target: " << end;
		cin >> target;
		
		//if position of target is on a straight x or y path to target
		if(target.x == current.x || target.y == current.y) {
			//if current can reach target with their dexterity stat
			if((abs(target.x - current.x)) <= current.dexterity) || ((abs(target.y - current.y)) <= current.dexterity) {
				int damage = current.attack - target.defense;
				if(damage < 0)
					damage = 0;
				else{
					target.health -= damage;
				}
				cout << "You have dealt " << damage << " to " << target.name << endl;

				//if attack kills target
				if(target.health <= 0){
					target.alive = false;
					cout << target.name << " has been felled." << endl;
				}
				stop = true;
			}
			else {
				cout << "Cannot attack this player" << endl;
			}
		} 
		
		//if position of target is on a diagonal path from current
		else if() {

		}

		//if not, current cannot attack the specified target
		else {
			cout << "Cannot attack this player" << endl;
		}
	}*/
}

void MainWindow::moveSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are moving! wowee!");
	msgBox.exec();
}

void MainWindow::endTurnSlot() {
	turnQueue.enqueue(currentCharacter);
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
	QTableWidgetItem *old = turnOrder->takeItem(0,0);
	for (int i = 1; i < turnQueue.getSize()+1; i++) {
		QTableWidgetItem *pushup = turnOrder->takeItem(i,0);
		turnOrder->setItem(i-1,0,pushup);
	}
	turnOrder->setItem(turnQueue.getSize(),0,old);
	show();
}

