#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

};

void MainWindow::decorate() {
	QLabel *thesitch = new QLabel("In WATER: ATK down, SPD down");

	QLabel *ranged = new QLabel("Ranged attacks not possible");
	QPushButton *buttonA = new QPushButton("Attack");
	QPushButton *buttonR = new QPushButton("Ranged");
	QPushButton *buttonM = new QPushButton("Move");
	QPushButton *buttonEnd = new QPushButton("End Turn");

	QObject::connect(buttonA, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    QObject::connect(buttonR, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    QObject::connect(buttonM, SIGNAL(clicked()), this, SLOT(clickedSlot()));
    QObject::connect(buttonEnd, SIGNAL(clicked()), this, SLOT(clickedSlot()));

	QVBoxLayout *actions = new QVBoxLayout();
	actions->addWidget(thesitch);
	actions->addWidget(ranged);
	actions->addWidget(buttonA);
	actions->addWidget(buttonR);
	actions->addWidget(buttonM);
	actions->addWidget(buttonEnd);

	QLabel *name = new QLabel("Sid the Rogue");
	QLabel *allyOrEnemy = new QLabel("Indeterminate");
	QLabel *health = new QLabel("HP: 20/20");
	QLabel *statsLabel = new QLabel("ATK: 4, DEX: 7");
	QLabel *statsLabel2 = new QLabel("DEF: 7, SPD: 3");

	QVBoxLayout *stats = new QVBoxLayout();
	stats->addWidget(name);
	stats->addWidget(allyOrEnemy);
	stats->addWidget(health);
	stats->addWidget(statsLabel);
	stats->addWidget(statsLabel2);

	QTableWidget *turnOrder = new QTableWidget(6,1);
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
	layout->addLayout(stats);
	layout->addLayout(actions);

	int width = 10;
	int height = 10;

	QTableWidget *table = new QTableWidget(width,height);
	table->setShowGrid(false);
	header = table->horizontalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();
	header = table->verticalHeader();
	header->setResizeMode(QHeaderView::Stretch);
	header->hide();

	Board board = Board(width,height);
	Queue turnQueue = Queue();
	generate(table, width, height, board, turnOrder, &turnQueue);

	//play = true;

	//while(play) {
	    Human curr = turnQueue.dequeue();
	    name->setText(QString::fromStdString(curr.name));
	    allyOrEnemy->setText(QString::fromStdString("Ally"));
	    health->setText(QString::fromStdString("HP: " + std::to_string(curr.health) + "/" + std::to_string(curr.health)));
	    statsLabel->setText(QString::fromStdString("ATK: " + std::to_string(curr.attack) + ", DEX: " + std::to_string(curr.dexterity)));
	    statsLabel2->setText(QString::fromStdString("DEF: " + std::to_string(curr.defense) + ", SPD: " + std::to_string(curr.speed)));
	    thesitch->setText(QString::fromStdString("Nothing is happening"));
	    ranged->setText(QString::fromStdString("Because it hasn't been built yet"));
	    //when end turn button pressed, end turn
	//}

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

void MainWindow::clickedSlot() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You Clicked A Button"/*+ ((QPushButton*)sender())->text()*/);
	msgBox.exec();
}

