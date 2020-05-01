#pragma once
#ifndef STACK_H
#define STACK_H
#include "node.h"
#include <iostream>
#include<cassert>
template<typename DataType>
class Stack {
private:
	Node<DataType> * top;
	unsigned int Length;
public:
	Stack() {
		this->top = NULL;
		this->Length = 0;
	}
	void Push(DataType Data) {
		Node<DataType> *Temp = new Node<DataType>(Data,this->top);
		this->top= Temp;
		this->Length++;
	}
	DataType Pop() {
		assert(!this->IsEmpty());
		Node<DataType> *Temp = this->top;
		this->top = Temp->GetNode();
		DataType Data = Temp->GetData();
		delete Temp;
		this->Length--;
		return Data;
	}
	unsigned int GetLength() {
		return this->Length;
	}
	bool IsEmpty() {
		if (this->top == NULL) return true;
		else return false;
	}
	DataType Top() {
		assert(!this->IsEmpty());
		return this->top->GetData();
	}
	~Stack() {
		while (!this->IsEmpty()){
			this->Pop();
		}
	}
};
#endif // !STACK_H
