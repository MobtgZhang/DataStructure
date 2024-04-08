#pragma once
#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <cassert>
template<typename DataType>
class LinkedList{
private:
	Node<DataType> * Head;
	unsigned int Length;
public:
	LinkedList() {
		this->Head = NULL;
		this->Length = 0;
	}
	void Push_Back(DataType Data) {
		Node<DataType>* ptr = new Node<DataType>(Data,NULL);
		if (this->Head == NULL) this->Head = ptr;
		else {
			Node<DataType>* Insert = this->Head;
			while (Insert->GetNode() != NULL) Insert = Insert->GetNode();
			Insert->SetNode(ptr);
		}
		this->Length++;
	}
	void Push_Front(DataType Data) {
		Node<DataType>* ptr = new Node<DataType>(Data, this->Head);
		this->Head = ptr;
		this->Length++;
	}
	DataType Pop_Front() {
		Node<DataType>* ptr = this->Head;
		this->Head = this->Head->GetNode();
		DataType Temp = ptr->GetData();
		this->Length--;
		delete ptr;
		return Temp;
	}
	DataType Pop_Back() {
		Node<DataType>* ptr = this->Head;
		Node<DataType>* pre = NULL;
		while (ptr->GetNode()!=NULL) {
			pre = ptr;
			ptr = ptr->GetNode();
		}
		DataType Data = ptr->GetData();
		delete ptr;
		if(pre !=NULL ) pre->SetNode(NULL);
		else this->Head = NULL;
		this->Length--;
		return Data;
	}
	//insert after the index 
	void Insert(unsigned int index,DataType Data) {
		if (this->Length == 0) this->Push_Back(Data);
		else {
			Node<DataType>*p = this->GetNode(index);
			Node<DataType> *q = new Node<DataType>(Data, p->GetNode());
			p->SetNode(q);
			this->Length++;
		}
	}
	// delete this index
	DataType Delete(unsigned int index) {
		Node<DataType>*p = this->GetNode(index);
		DataType Data = p->GetData();
		Node<DataType>*q = p->GetNode();
		p->SetData(q->GetData());
		p->SetNode(q->GetNode());
		delete q;
		this->Length--;
		return Data;
	}
	void Clear() {
		while (this->Head != NULL) this->Pop_Front();
	}
	DataType operator[](unsigned int index) {
		assert(index < this->Length);
		unsigned int t = 0;
		Node<DataType>*ptr = this->Head;
		while (t < index) {
			ptr = ptr->GetNode(); t++;
		}
		return ptr->GetData();
	}
	Node<DataType>* GetNode(unsigned int index) {
		assert(index < this->Length);
		unsigned int t = 0;
		Node<DataType>*ptr = this->Head;
		while (t < index) {
			ptr = ptr->GetNode(); t++;
		}
		return ptr;
	}
	void SetNode(unsigned int index,Node<DataType>*node) {
		assert(index < this->Length);
		unsigned int t = 0;
		Node<DataType>* ptr = this->Head;
		Node<DataType>* pre = NULL;
		while (t < index) {
			pre = ptr;
			ptr = ptr->GetNode();
			t++;
		}
		pre->SetNode(node);
		node->SetNode(ptr->GetNode());
	}
	void Set(unsigned int index,DataType Data) {
		this->GetNode(index)->SetData(Data);
	}
	DataType Get(unsigned int index) { return this->GetNode(index)->GetData(); }
	unsigned int GetLength() { return this->Length; }
	DataType Front() { return this->Head->GetData(); }
	DataType Back() { return this->operator[](this->Length-1); }
	bool IsEmpty() {
		return this->Head!=NULL;
	}
	~LinkedList(){
		while (this->Head != NULL) this->Pop_Front();
	}
};
template<typename DataType>
class BiList {
public:
	DeNode<DataType> * Head;
	DeNode<DataType> * Rear;
	unsigned int Length;
public:
	BiList() {
		this->Head = NULL;
		this->Rear = NULL;
		this->Length = 0;
	}
	unsigned int GetLength() { return this->Length; }
	bool IsEmpty() {
		return this->Head == NULL ;
	}
	void Push_Front(DataType Data) {
		DeNode<DataType>* ptr = new DeNode<DataType>(Data, this->Head, NULL);
		if (this->Length == 0) this->Rear = ptr;
		else this->Head->SetPreviousNode(ptr);
		this->Head = ptr;
		this->Length++;
	}
	void Push_Back(DataType Data) {
		DeNode<DataType>* ptr = new DeNode<DataType>(Data,  NULL, this->Rear);
		if (this->Length == 0) this->Head = ptr;
		else this->Rear->SetNextNode(ptr);
		this->Rear = ptr;
		this->Length++;
	}
	DataType Pop_Front() {
		DeNode<DataType>* ptr = this->Head;
		this->Head = this->Head->GetNextNode();
		if (this->Head!=NULL) this->Head->SetPreviousNode(NULL);
		else this->Rear = NULL;
		DataType Data = ptr->GetData();
		delete ptr;
		this->Length--;
		return Data;
	}
	DataType Pop_Back() {
		DeNode<DataType>* ptr = this->Rear;
		this->Rear = this->Rear->GetPreviousNode();
		if (this->Rear != NULL) this->Rear->SetNextNode(NULL);
		else this->Head = NULL;
		DataType Data = ptr->GetData();
		delete ptr;
		this->Length--;
		return Data;
	}
	DataType operator[](unsigned int index) {
		assert(index < this->Length);
		unsigned int t = 0;
		DeNode<DataType>*ptr = this->Head;
		while (t < index) {
			ptr = ptr->GetNextNode(); t++;
		}
		return ptr->GetData();
	}
	DataType Front() {
		return this->Head->GetData();
	}
	DataType Back() {
		return this->Rear->GetData();
	}
	~BiList() {
		while (!this->IsEmpty()) this->Pop_Front();
	}
};
template<typename DataType>
class CircleBiList{
public:
	DeNode<DataType>*Head;
	DeNode<DataType>*Rear;
	unsigned int Length;
public:
	CircleBiList() {
		this->Head = NULL;
		this->Rear = NULL;
		this->Length = 0;
	}
	void Push_Front(DataType Data) {
		DeNode<DataType>* ptr = new DeNode<DataType>(Data, this->Head,this->Rear);
		if (this->Length == 0) {
			ptr->SetNextNode(ptr);
			ptr->SetPreviousNode(ptr);
			this->Head = ptr;
			this->Rear = ptr;
		}
		this->Head->SetPreviousNode(ptr);
		this->Rear->SetNextNode(ptr);
		this->Head = ptr;
		this->Length++;
	}
	void Push_Back(DataType Data) {
		DeNode<DataType>* ptr = new DeNode<DataType>(Data, this->Head,this->Rear);
		if (this->Length == 0) {
			ptr->SetNextNode(ptr);
			ptr->SetPreviousNode(ptr);
			this->Head = ptr;
			this->Rear = ptr;
		}
		this->Rear->SetNextNode(ptr);
		this->Head->SetPreviousNode(ptr);
		this->Rear = ptr;
		this->Length++;
	}
	DataType Pop_Back() {
		DeNode<DataType>* ptr = this->Rear;
		if (this->Length == 1) {
			this->Head = NULL;
			this->Rear = NULL;
		}
		else {
			this->Rear = this->Rear->GetPreviousNode();
			this->Rear->SetNextNode(this->Head);
			this->Head->SetPreviousNode(this->Rear);
		}
		DataType Data = ptr->GetData();
		delete ptr;
		this->Length--;
		return Data;
	}
	DataType Pop_Front() {
		DeNode<DataType>* ptr = this->Head;
		if (this->Length == 1) {
			this->Head = NULL;
			this->Rear = NULL;
		}
		else {
			this->Head = this->Head->GetNextNode();
			this->Head->SetPreviousNode(this->Rear);
			this->Rear->SetNextNode(this->Head);
		}
		DataType Data = ptr->GetData();
		delete ptr;
		this->Length--;
		return Data;
	}
	DataType Back() {
		return this->Rear->GetData();
	}
	DataType Front() {
		return this->Head->GetData();
	}
	bool IsEmpty() {
		return this->Head == NULL ;
	}
	DataType operator[](unsigned int index) {
		assert(index <this->Length);
		unsigned int t = 0;
		DeNode<DataType>* ptr = this->Head;
		while (t < index) {
			ptr = ptr->GetNextNode();
			t++;
		}
		return ptr->GetData();
	}
	unsigned int GetLength() {
		return this->Length;
	}
	~CircleBiList() {
		//while (!this->IsEmpty()) this->Pop_Front();
	}
};
#endif // !LIST_H
