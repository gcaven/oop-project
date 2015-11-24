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

	console = new QTextEdit();
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
                    item->setBackgroundColor(QColor(131,245,78));
                    break;
                case HILL:
                    item->setBackgroundColor(QColor(170,245,132));
                    break;
                case TREES:
                    item->setBackgroundColor(QColor(126,179,46));
                    break;
                case DITCH:
                    item->setBackgroundColor(QColor(154,176,118));
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
    Ally allies[3];
    Enemy enemies[3];
    for (int i=0; i < 3; i++) {
    	allies[i].generateLocation(&board, humans, i);
    	humans[i] = &allies[i];
    	humans[i]->setId(i);
        turnQueue.enqueue(allies[i]);
    }
    for (int i=0; i < 3; i++) {
    	enemies[i].generateLocation(&board, humans, i+3);
    	humans[i+3] = &enemies[i];
    	humans[i]->setId(i+3);
        turnQueue.enqueue(enemies[i]);
    }
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
	console->append("Do the locomotion!");

	Human current = this->currentCharacter;
	int distance = current.speed;

	//console input prompt for board coordinates
	/*std::cout << "Where would you like to move? Ex. A0" << endl;
	std::string xy;
	std::cin << xy;
	*/
}

void MainWindow::endTurnSlot() {
	turnQueue.enqueue(currentCharacter);
	console->append("");
	currentCharacter = turnQueue.dequeue();
	std::string statsString = currentCharacter.name;
	std::string consoleText = currentCharacter.name;
	consoleText += " is getting ready to act!";
	console->append(QString::fromStdString(consoleText));
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

