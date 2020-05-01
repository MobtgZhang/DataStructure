#pragma once
#ifndef STACK_H
#define STACK_H
#include<cassert>
#include "node.h"
template<typename DataType>
class Stack {
private:
	//注意栈底节点不存储元素信息
	DoubleNode<DataType>* TopPtr;
public:
	Stack() {
		this->TopPtr = new DoubleNode<DataType>();
	}
	//压入栈顶
	void Push(DataType Data) {
		this->TopPtr->SetNextNode(new DoubleNode<DataType>(Data, this->TopPtr, NULL));
		this->TopPtr = this->TopPtr->GetNextNode();
	}
	//弹出栈顶
	DataType Pop() {
		assert(this->TopPtr->GetPreviousNode()!=NULL);
		DoubleNode<DataType>*ptr = this->TopPtr;
		DataType tmp = ptr->GetData();
		this->TopPtr = this->TopPtr->GetPreviousNode();
		this->TopPtr->SetNextNode(NULL);
		delete ptr;
		return tmp;
	}
	//获取栈顶元素
	DataType Top() {
		return this->TopPtr->GetData();
	}
	//查看栈是否为空
	bool Empty() {
		return this->TopPtr->GetPreviousNode() == NULL;
	}
	//清空栈内的元素
	void Clear() {
		DoubleNode<DataType>*ptr = this->TopPtr;
		DoubleNode<DataType>*qtr = this->TopPtr;
		while (qtr->GetPreviousNode()!=NULL) {
			qtr = qtr->GetPreviousNode();
			delete ptr;
			ptr = qtr;
		}
		qtr->SetNextNode(NULL);
		this->TopPtr = qtr;
	}
	~Stack() {
		DoubleNode<DataType>*ptr = this->TopPtr;
		DoubleNode<DataType>*qtr = this->TopPtr;
		while (qtr->GetPreviousNode() != NULL) {
			qtr = qtr->GetPreviousNode();
			delete ptr;
			ptr = qtr;
		}
		delete qtr;
	}
};
#endif // !STACK_H
