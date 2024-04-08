#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <cassert>
#include "node.h"
#include "List.h"
template<typename DataType>
class Queue {
public:
	//注意尾结点,头结点存储信息
	DoubleNode<DataType>* FrontPtr;
	DoubleNode<DataType>* RearPtr;
public:
	Queue() {
		this->FrontPtr = NULL;
		this->RearPtr = NULL;
	}
	void Push(DataType Data) {
		if (this->RearPtr == NULL) {
			this->FrontPtr = new DoubleNode<DataType>(Data, NULL, NULL);
			this->RearPtr = this->FrontPtr;
			return;
		}
		this->RearPtr->SetNextNode(new DoubleNode<DataType>(Data,this->RearPtr,NULL));
		this->RearPtr = this->RearPtr->GetNextNode();
	}
	DataType Pop() {
		assert(this->FrontPtr!=NULL || this->RearPtr!=NULL);
		DoubleNode<DataType>*ptr = this->FrontPtr;
		DataType tmp = ptr->GetData();
		if (ptr->GetNextNode()!=NULL){
			this->FrontPtr = ptr->GetNextNode();
			this->FrontPtr->SetPreviousNode(NULL);
		}
		else {
			this->FrontPtr = NULL;
			this->RearPtr = NULL;
		}
		delete ptr;
		return tmp;
	}
	DataType Front() {
		assert(this->FrontPtr != NULL || this->RearPtr != NULL);
		return this->FrontPtr->GetData();
	}
	DataType Rear() {
		assert(this->FrontPtr != NULL || this->RearPtr != NULL);
		return this->RearPtr->GetData();
	}
	bool Empty() {
		return (this->FrontPtr == NULL) || (this->RearPtr == NULL);
	}
	void Clear() {
		if (this->FrontPtr == NULL && this->RearPtr == NULL) return;
		DoubleNode<DataType>*ptr = this->FrontPtr;
		DoubleNode<DataType>*qtr = NULL;
		while (ptr!= NULL) {
			qtr = ptr;
			ptr = ptr->GetNextNode();
			delete qtr;
		}
		delete ptr;
		this->RearPtr = NULL;
		this->FrontPtr = NULL;
	}
	~Queue() {
		this->Clear();
	}
};
#endif // !QUEUE_H
#ifndef DEQUEUE_H
#define DEQUEUE_H
//实际上就是一个带有头结点和尾结点的双向链表
template<typename DataType>
class Dequeue{
private:
	//注意尾结点,头结点存储信息
	DoubleNode<DataType>* FrontPtr;
	DoubleNode<DataType>* RearPtr;
public:
	Dequeue() {
		this->FrontPtr = NULL;
		this->RearPtr = NULL;
	}
	//在队列的前面加上一个元素
	void Push_Front(DataType Data) {
		if (this->FrontPtr == NULL) {
			this->FrontPtr = new DoubleNode<DataType>(Data,NULL,NULL);
			this->RearPtr = this->FrontPtr;
			return;
		}
		this->FrontPtr->SetPreviousNode(new DoubleNode<DataType>(Data,NULL,this->FrontPtr));
		this->FrontPtr = this->FrontPtr->GetPreviousNode();
	}
	//在队列前面删除一个元素
	DataType Pop_Front() {
		assert(this->FrontPtr || this->RearPtr!=NULL);
		DoubleNode<DataType>*ptr = this->FrontPtr;
		DataType tmp = ptr->GetData();
		if (ptr->GetNextNode() != NULL) {
			this->FrontPtr = this->FrontPtr->GetNextNode();
			this->FrontPtr->SetPreviousNode(NULL);
		}
		else {
			this->FrontPtr = NULL;
			this->RearPtr = NULL;
		}
		delete ptr;
		return tmp;
	}
	//在队列的后面添加一个元素
	void Push_Back(DataType Data) {
		if (this->RearPtr == NULL) {
			this->RearPtr = new DoubleNode<DataType>(Data,this->RearPtr,NULL);
			this->FrontPtr = this->RearPtr;
			return;
		}
		this->RearPtr->SetNextNode(new DoubleNode<DataType>(Data,this->RearPtr,NULL));
		this->RearPtr = this->RearPtr->GetNextNode();
	}
	//在队列后面删除一个元素
	DataType Pop_Back() {
		assert(this->FrontPtr || this->RearPtr != NULL);
		DoubleNode<DataType>*ptr = this->RearPtr;
		DataType tmp = ptr->GetData();
		if (ptr->GetPreviousNode() != NULL) {
			this->RearPtr = this->RearPtr->GetPreviousNode();
			this->RearPtr->SetNextNode(NULL);
		}
		else {
			this->FrontPtr = NULL;
			this->RearPtr = NULL;
		}
		delete ptr;
		return tmp;
	}
	DataType Front() {
		assert(this->FrontPtr != NULL || this->RearPtr != NULL);
		return this->FrontPtr->GetData();
	}
	DataType Rear() {
		assert(this->FrontPtr != NULL || this->RearPtr != NULL);
		return this->RearPtr->GetData();
	}
	bool Empty() {
		return (this->FrontPtr == NULL || this->RearPtr == NULL);
	}
	//清除序列中的所有元素
	void Clear() {
		if (this->FrontPtr == NULL && this->RearPtr == NULL) return;
		DoubleNode<DataType>*ptr = this->FrontPtr;
		DoubleNode<DataType>*qtr = NULL;
		while (ptr != NULL) {
			qtr = ptr;
			ptr = ptr->GetNextNode();
			delete qtr;
		}
		delete ptr;
		this->RearPtr = NULL;
		this->FrontPtr = NULL;
	}
	~Dequeue() {
		this->Clear();
	}
};
#endif // !DEQUEUE_H
