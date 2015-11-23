#include "Queue.h"

Queue::Queue() {
	front=rear=nullptr;
	size = 0;
}

bool Queue::emptyQueue() {
	if (front == nullptr) {
		return true;
	} else {
		return false;
	}
}

void Queue::enqueue(Human human) {
	queueNode *tempPtr;
	tempPtr = new (queueNode);
	if (tempPtr != nullptr) {
		tempPtr->human = human;
		tempPtr->prevPtr = nullptr;
		if (emptyQueue()) {
			front=rear=tempPtr;
		} else {
			rear->prevPtr = tempPtr;
			rear = tempPtr;
		}
		size++;
	} else {
		exit(EXIT_FAILURE); 
	}
}

Human Queue::dequeue() {
	Human x;
	queueNode *tempPtr;
	if (emptyQueue()) {
		exit(EXIT_FAILURE);
	} else {
		tempPtr = front;
		x = front->human;
		front = front->prevPtr;
		if (front == nullptr) 
			rear = nullptr;
		else
			delete tempPtr;
		size--;
		return x;
	}
}

int Queue::getSize() {
	return size;
}
std::string Queue::print() {
	std::string string = "";
	queueNode *tempPtr;
	tempPtr = front;
	while(tempPtr != nullptr) {
		string += tempPtr->human.name;
		string += "\n";
		tempPtr = tempPtr->prevPtr;
	}
	return string;
}
