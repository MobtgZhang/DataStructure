#pragma once
#ifndef SEQUENCE_H
# define MAXSIZE 10000
template<typename DataType>
class Stack{
private:
	int top;
	DataType List*;
public:
	Stack() {
		this->top = -1;
		this->List = new DataType[MAXSIZE];
	}
	void Push(DataType Data) {
		this->List[++this->top] = Data;
	}
	DataType Pop() {
		return this->List[this->top--];
	}
	DataType Top() {
		return this->List[this->top];
	}
	unsigned int GetLength() {
		return top + 1;
	}
	bool IsEmpty() {
		return this->top == -1 ;
	}
	~Stack(){
		delete[] List;
	}
};
template<typename DataType>
class Queue {
private:
	unsigned int rear;
	unsigned int front;
	DataType* List;
public:
	Queue() {
		this->rear = 0;
		this->front = 0;
		this->List = new DataType[MAXSIZE];
	}
	void EnQueue(DataType Data) {
		this->front = (this->front + 1) % MAXSIZE;
		this->List[this->front] = Data;
	}
	DataType DeQueue() {
		DataType Data = this->List[this->rear];
		this->rear = (this->rear + 1) % MAXSIZE;
		return Data;
	}
	unsigned int GetLength() {
		return (MAXSIZE - this->front + this->rear) % MAXSIZE;
	}
	bool IsEmpty() {
		return this->rear == this->front;
	}
	~Queue(){
		delete[] this->List;
	}
};
#endif // !SEQUENCE_H
