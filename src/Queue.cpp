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

void Queue::enqueue(int index) {
	queueNode *tempPtr;
	tempPtr = new (queueNode);
	if (tempPtr != nullptr) {
		tempPtr->index = index;
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

int Queue::dequeue() {
	int index;
	queueNode *tempPtr;
	if (emptyQueue()) {
		exit(EXIT_FAILURE);
	} else {
		tempPtr = front;
		index = front->index;
		front = front->prevPtr;
		if (front == nullptr) 
			rear = nullptr;
		else
			delete tempPtr;
		size--;
		return index;
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
		string += std::to_string(tempPtr->index);
		string += "\n";
		tempPtr = tempPtr->prevPtr;
	}
	return string;
}
