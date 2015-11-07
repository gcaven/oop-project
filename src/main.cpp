#include <iostream>
#include <string>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include "Board.h"
#include "Human.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        QWidget window;
        window.setFixedSize(800,800);

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

        QHBoxLayout *layout = new QHBoxLayout();
        layout->addLayout(stats);
        layout->addLayout(actions);

        QTableWidget *table = new QTableWidget(15,15);
        QHeaderView *header = table->horizontalHeader();
        header->setResizeMode(QHeaderView::Stretch);
        QHeaderView *verticalHeader = table->verticalHeader();
		verticalHeader->setResizeMode(QHeaderView::Stretch);

        QVBoxLayout *layoutVert = new QVBoxLayout();
        layoutVert->addWidget(table);
        layoutVert->addLayout(layout);

        window.setLayout(layoutVert);
        window.setWindowTitle("Adventure Battle");
        window.show();
        return app.exec();
}

//this is just testing logic and shit, we need to create a ui
void game() {
    Board board = Board(15,15);
    std::cout << "  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14\n";
    for (int x=0; x<15; x++) {
        std::cout << x << ": ";
        for (int y=0; y<15; y++) {
            Tile tile = board.get(x,y);
            std::cout << tile.getTypeAsString() << " ";
        }
        std::cout << "\n";
    }
    board.destroy();
    return;
}

