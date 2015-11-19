#include <iostream>
#include <string>
#include <QWidget>
#include <QMessageBox>
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

class MainWindow: public QWidget {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	void decorate();
	void generate(QTableWidget *table, int width, int height, Board board, QTableWidget *turnOrder, Queue *turnQueue);

public slots:
	void attackSlot();
	void rangedSlot();
	void moveSlot();
	void endTurnSlot();
};