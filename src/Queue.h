#include "Human.h"
#include <QCoreApplication>

class Queue {
private:
	struct queueNode{
		Human human;
		queueNode *prevPtr;
	};
	queueNode *front,*rear;
	int size;
public:
	Queue();
	bool emptyQueue();
	void enqueue(Human human);
	Human dequeue();
	int getSize();
	std::string print();
};