#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
template<typename DataType>
class Queue {
private:
	DeNode<DataType> * front;
	DeNode<DataType> * rear;
	unsigned int Length;
public:
	Queue() {
		this->front = NULL;
		this->rear = NULL;
		this->Length = 0;
	}
	void EnQueue(DataType Data) {
		DeNode<DataType>* ptr = new DeNode<DataType>(Data,this->front,NULL);
		if (!IsEmpty()) this->front->SetPreviousNode(ptr);
		this->front = ptr;
		this->Length++;
		if (this->Length == 1) this->rear = this->front;
	}
	DataType DeQueue() {
		DeNode<DataType> * ptr = this->rear;
		this->rear = this->rear->GetPreviousNode();
		DataType Data= ptr->GetData();
		delete ptr;
		this->Length--;
		if (this->Length == 0)this->rear = this->front = NULL;
		return Data;
	}
	bool IsEmpty() {
		if (this->Length == 0) return true;
		else return false;
	}
	unsigned int GetLength() {
		return this->Length;
	}
	~Queue() {
		while (!this->IsEmpty()) this->DeQueue();
	}
};
#endif // !QUEUE_H
