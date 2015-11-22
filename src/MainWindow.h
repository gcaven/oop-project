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
#include <QColor>
#include <QLayoutItem>
#include <QTextEdit>
#include "Board.h"
#include "Queue.h"

class MainWindow: public QWidget {
	Q_OBJECT

private:
	Board board;
	Queue turnQueue;
	QTableWidget *turnOrder;
	QTableWidget *table;
	QVBoxLayout *statsLayout;
	QLabel *stats;
	QPushButton *buttonStart;
	QPushButton *buttonA;
	QPushButton *buttonR;
	QPushButton *buttonM;
	QPushButton *buttonEnd;
	Human *humans[6];
	Human currentCharacter;
	QLabel *theSitch;

public:
	MainWindow(QWidget *parent = 0);
	void decorate();
	void generate(int width, int height);

private slots:
	void startGameSlot();
	void attackSlot();
	void rangedSlot();
	void moveSlot();
	void endTurnSlot();
};