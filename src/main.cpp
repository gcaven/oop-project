#include <iostream>
#include <string>
#include <QApplication>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QString>
#include <QStringList>
#include "Board.h"
#include "Queue.h"

void game(QTableWidget *table, int width, int height, QTableWidget *turnOrder) {
    //generate board, fill the table
    Board board = Board(width,height);
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
    Queue turnQueue = Queue();
    for (int i=0; i < 3; i++) {
        turnQueue.enqueue(allies[i]);
    }
    for (int i=0; i < 3; i++) {
        turnQueue.enqueue(enemies[i]);
    }
    for (int i=0; i < turnQueue.getSize(); i++) {
        std::string name;
        Human temp = turnQueue.dequeue();
        name = temp.name;
        turnQueue.enqueue(temp);
        QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(name));
        item->setFlags(Qt::ItemIsEditable);
        turnOrder->setItem(i,0,item);
    }
return;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        QWidget window;
        window.setFixedSize(600,750);

        QLabel *thesitch = new QLabel("In WATER: ATK down, SPD down");
        QLabel *ranged = new QLabel("Ranged attacks not possible");
        QPushButton *buttonA = new QPushButton("Attack");
        QPushButton *buttonR = new QPushButton("Ranged");
        QPushButton *buttonM = new QPushButton("Move");

        QVBoxLayout *actions = new QVBoxLayout();
        actions->addWidget(thesitch);
        actions->addWidget(ranged);
        actions->addWidget(buttonA);
        actions->addWidget(buttonR);
        actions->addWidget(buttonM);

        QLabel *name = new QLabel("Sid the Rogue");
        QLabel *health = new QLabel("HP: 20/20");
        QLabel *statsLabel = new QLabel("ATK: 4, DEX: 7");
        QLabel *statsLabel2 = new QLabel("DEF: 7, SPD: 3");

        QVBoxLayout *stats = new QVBoxLayout();
        stats->addWidget(name);
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

        game(table, width, height, turnOrder);

        QVBoxLayout *layoutVert = new QVBoxLayout();
        layoutVert->addWidget(table);
        layoutVert->addLayout(layout);

        window.setLayout(layoutVert);
        window.setWindowTitle("Adventure Battle");

        window.show();
        return app.exec();
}
