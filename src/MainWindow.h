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
#include <QSound>
#include <QDir>
#include "Board.h"
#include "Queue.h"

class MainWindow: public QWidget {
	Q_OBJECT

private:
	Board board;
	Queue turnQueue;
	QTableWidget *turnOrder;
	QTableWidget *table;
	QTextEdit *console;

	Human humans[6];
	Human *currentCharacter;
	int moves;

	QVBoxLayout *statsLayout;
	QVBoxLayout *actionsLayout;
	QHBoxLayout *bottomLayout;

	QLabel *stats;

	QPushButton *buttonStart;
	QPushButton *buttonA;
	QPushButton *buttonR;
	QPushButton *buttonM;
	QPushButton *buttonEnd;

	QPushButton *buttonMoveUp;
	QPushButton *buttonMoveRight;
	QPushButton *buttonMoveDown;
	QPushButton *buttonMoveLeft;
	QPushButton *buttonMoveStop;

	QPushButton *targetA;
	QPushButton *targetB;
	QPushButton *targetC;
	QPushButton *attackStop;

	QPushButton *rangedTargetA;
	QPushButton *rangedTargetB;
	QPushButton *rangedTargetC;
	QPushButton *rangedStop;

	QSound *attackSound;
	QSound *deathSound;

public:
	MainWindow(QWidget *parent = 0);
	void decorate(QString dir);
	void generate(int width, int height);
	void attack(int index);
	void attackRanged(int index);
	void move(int x, int y);
	void stopMoving();
	void stopAttacking();
	void stopRanged();
	bool enemyTurn(Human *adjPlayer, Human *closestPlayer);
	bool enemyAttack(Human *adjPlayer);
	void removePlayer(int index);

private slots:
	void startGameSlot();

	void attackSlot();
	void attackTargetASlot();
	void attackTargetBSlot();
	void attackTargetCSlot();

	void rangedSlot();
	void attackRangedTargetASlot();
	void attackRangedTargetBSlot();
	void attackRangedTargetCSlot();

	void moveSlot();
	void moveUpSlot();
	void moveRightSlot();
	void moveDownSlot();
	void moveLeftSlot();
	void moveStopSlot();

	void endTurnSlot();
	void stopAttackingSlot();	
	void stopRangedSlot();
};
