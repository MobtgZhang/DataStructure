#pragma once
#ifndef STACK_H
#define STACK_H
#include<cassert>
#include "node.h"
template<typename DataType>
class Stack {
private:
	//ע��ջ�׽ڵ㲻�洢Ԫ����Ϣ
	DoubleNode<DataType>* TopPtr;
public:
	Stack() {
		this->TopPtr = new DoubleNode<DataType>();
	}
	//ѹ��ջ��
	void Push(DataType Data) {
		this->TopPtr->SetNextNode(new DoubleNode<DataType>(Data, this->TopPtr, NULL));
		this->TopPtr = this->TopPtr->GetNextNode();
	}
	//����ջ��
	DataType Pop() {
		assert(this->TopPtr->GetPreviousNode()!=NULL);
		DoubleNode<DataType>*ptr = this->TopPtr;
		DataType tmp = ptr->GetData();
		this->TopPtr = this->TopPtr->GetPreviousNode();
		this->TopPtr->SetNextNode(NULL);
		delete ptr;
		return tmp;
	}
	//��ȡջ��Ԫ��
	DataType Top() {
		return this->TopPtr->GetData();
	}
	//�鿴ջ�Ƿ�Ϊ��
	bool Empty() {
		return this->TopPtr->GetPreviousNode() == NULL;
	}
	//���ջ�ڵ�Ԫ��
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
