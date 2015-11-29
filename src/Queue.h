#include "Human.h"
#include <QCoreApplication>

class Queue {
private:
	struct queueNode{
		int index;
		queueNode *prevPtr;
	};
	queueNode *front,*rear;
	int size;
public:
	Queue();
	bool emptyQueue();
	void enqueue(int index);
	int dequeue();
	int getSize();
	std::string print();
};