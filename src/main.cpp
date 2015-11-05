#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        QWidget window;

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

        QTableView *table = new QTableView();

        QVBoxLayout *layoutVert = new QVBoxLayout();
        layoutVert->addWidget(table);
        layoutVert->addLayout(layout);

        window.setLayout(layoutVert);
        window.setWindowTitle("Adventure Battle");
        window.show();
        return app.exec();
}
