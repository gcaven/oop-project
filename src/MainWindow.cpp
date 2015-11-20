#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
};

void MainWindow::decorate() {
	QLabel *theSitch = new QLabel("In WATER: ATK down, SPD down\nRanged attacks not possible");
	this->theSitch = theSitch;
	QPushButton *buttonA = new QPushButton("Attack");
	QPushButton *buttonR = new QPushButton("Ranged");
	QPushButton *buttonM = new QPushButton("Move");
	QPushButton *buttonEnd = new QPushButton("End Turn");

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

	QLabel *stats = new QLabel("Sid the Rogue\nIndeterminate\nHP: 20/20\nATK: 4, DEX: 7\nDEF: 7, SPD: 3");

	QVBoxLayout *statsLayout = new QVBoxLayout();
	statsLayout->addWidget(stats);
	this->stats = stats;

	QTableWidget *turnOrder = new QTableWidget(6,1);
	turnOrder->setFixedWidth(150);
	turnOrder->setFixedHeight(180);
	QHeaderView *header = turnOrder->horizontalHeader();
	header->setSectionResizeMode(QHeaderView::Stretch);
	header->hide();
	header = turnOrder->verticalHeader();
	header->setSectionResizeMode(QHeaderView::Stretch);
	header->hide();
	this->turnOrder = turnOrder;
	
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(turnOrder);
	layout->addLayout(statsLayout);
	layout->addLayout(actions);

	int width = 10;
	int height = 10;

	QTableWidget *table = new QTableWidget(width,height);
	table->setShowGrid(false);
	header = table->horizontalHeader();
	header->setSectionResizeMode(QHeaderView::Stretch);
	header->hide();
	header = table->verticalHeader();
	header->setSectionResizeMode(QHeaderView::Stretch);
	header->hide();
	this->table = table;

	generate(table, width, height, board, turnOrder, &turnQueue);

	Human curr = turnQueue.dequeue();
    this->currentCharacter = &curr;
	std::string statsString = curr.name;
	statsString += "\n\ndunno";
	statsString += "\n\nHP: " + std::to_string(curr.health) + "/" + std::to_string(curr.health);
	statsString += "\n\nATK: " + std::to_string(curr.attack) + ", DEX: " + std::to_string(curr.dexterity);
	statsString += "\n\nDEF" + std::to_string(curr.defense) + ", SPD: " + std::to_string(curr.speed);
	stats->setText(QString::fromStdString(statsString));
	theSitch->setText(QString::fromStdString("Nothing is happening\n\nBecause it hasn't been built yet"));

	QVBoxLayout *layoutVert = new QVBoxLayout();
	layoutVert->addWidget(table);
	layoutVert->addLayout(layout);

	setLayout(layoutVert);
	setWindowTitle("Adventure Battle");

	show();
}

void MainWindow::generate(QTableWidget *table, int width, int height, Board board, QTableWidget *turnOrder, Queue *turnQueue) {
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
        turnQueue->enqueue(allies[i]);
    }
    for (int i=0; i < 3; i++) {
        turnQueue->enqueue(enemies[i]);
    }
    for (int i=0; i < turnQueue->getSize(); i++) {
        std::string name;
        Human temp = turnQueue->dequeue();
        name = temp.name;
        turnQueue->enqueue(temp);
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(name));
        item->setFlags(Qt::ItemIsEditable);
        turnOrder->setItem(i,0,item);
    }
return;
}

void MainWindow::attackSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are attacking! bro!");
	msgBox.exec();

	/*
	Human current = currentplayer pointer;
	Human target;
	cout << "Enter the name of your target: " << end;
	cin >> target;
	
	*/
}

void MainWindow::rangedSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are attacking from a distance! bruh!");
	msgBox.exec();
}

void MainWindow::moveSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You are moving! wowee!");
	msgBox.exec();
}

void MainWindow::endTurnSlot() {
	turnQueue.enqueue(*currentCharacter);
	*currentCharacter = turnQueue.dequeue();
	std::string kablam = "wowee";
	std::string statsString = currentCharacter->name;
	statsString += "\n\ndunno";
	statsString += "\n\nHP: " + std::to_string(currentCharacter->health) + "/" + std::to_string(currentCharacter->health);
	statsString += "\n\nATK: " + std::to_string(currentCharacter->attack) + ", DEX: " + std::to_string(currentCharacter->dexterity);
	statsString += "\n\nDEFFF JAM" + std::to_string(currentCharacter->defense) + ", SPD: " + std::to_string(currentCharacter->speed);
	stats->setText(QString::fromStdString(statsString));
	show();
}

