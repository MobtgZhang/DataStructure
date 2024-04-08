#pragma once
#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include<cassert>
#include"node.h"
#include"List.h"
template<typename DataType>
class CircleList:public  LinkedList<DataType>{
private:
	//ע��ͷ��㲻�洢Ԫ����Ϣ
	SingleNode<DataType>*Head;
public:
	CircleList() {
		this->Head = new SingleNode<DataType>();
		this->Head->SetNode(this->Head);
	}
	//������ĺ������һ��Ԫ��
	void Push_Back(DataType Data);
	//�������ǰ�����һ��Ԫ��
	void Push_Front(DataType Data);
	//�������ǰ��ɾ��һ��Ԫ��
	DataType Pop_Front();
	//������ĺ���ɾ��һ��Ԫ��
	DataType Pop_Back();
	//��index������һ��Ԫ��
	void Insert(unsigned int index, DataType Data);
	//ɾ��index����Ԫ��
	DataType Delete(unsigned int index);
	// ���������е�Ԫ�����
	void Clear();
	// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
	SingleNode<DataType>* GetNode(unsigned int index);
	// ��������index���Ľڵ�����ΪNode�ڵ�
	void SetNode(unsigned int index, SingleNode<DataType>* newnode);
	// ��ȡ����ͷ������ֵ
	DataType Front();
	// ��ȡ����β������ֵ
	DataType Back();
	~CircleList() {
		SingleNode<DataType>*qtr = NULL;
		SingleNode<DataType>*ptr = this->Head;
		while (ptr != this->Head) {
			qtr = ptr;
			ptr = ptr->GetNode();
			delete qtr;
		}
		this->Length = 0;
	}
};
//��ѭ���������ʵ�ַ���
//������ĺ������һ��Ԫ��
template<typename DataType>
void CircleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	SingleNode<DataType>*ptr = this->Head;
	while (ptr->GetNode() != this->Head) ptr = ptr->GetNode();
	SingleNode<DataType>* newnode = new SingleNode<DataType>(Data, this->Head);
	ptr->SetNode(newnode);
	this->Length++;
}
//�������ǰ�����һ��Ԫ��
template<typename DataType>
void CircleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	this->Head->SetNode(new SingleNode<DataType>(Data, this->Head->GetNode()));
	this->Length++;
}
//�������ǰ��ɾ��һ��Ԫ��
template<typename DataType>
DataType CircleList<DataType>::Pop_Front() {
	assert(this->Head != NULL && this->GetLength() != 0);
	SingleNode<DataType>*ptr = this->Head->GetNode();
	this->Head->SetNode(ptr->GetNode());
	DataType tmp = ptr->GetData();
	delete ptr;
	this->Length--;
	return tmp;
}
//������ĺ���ɾ��һ��Ԫ��
template<typename DataType>
DataType CircleList<DataType>::Pop_Back() {
	assert(this->Head != NULL && this->GetLength() != 0);
	SingleNode<DataType>*qtr = this->Head;
	SingleNode<DataType>*ptr = qtr->GetNode();
	while (ptr->GetNode() != this->Head) {
		qtr = ptr;
		ptr = ptr->GetNode();
	}
	DataType tmp = ptr->GetData();
	delete ptr;
	this->Length--;
	qtr->SetNode(this->Head);
	return tmp;
}
//��index������һ��Ԫ��
template<typename DataType>
void  CircleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	SingleNode<DataType>*ptr = this->GetNode(index);
	SingleNode<DataType>*newnode = new SingleNode<DataType>(ptr->GetData(), ptr->GetNode());
	ptr->SetData(Data);
	ptr->SetNode(newnode);
	this->Length++;
}
//ɾ��index����Ԫ��
template<typename DataType>
DataType  CircleList<DataType>::Delete(unsigned int index) {
	assert(this->Head != NULL && index <this->GetLength() && this->GetLength() != 0);
	SingleNode<DataType>*ptr = this->Head;
	SingleNode<DataType>*qtr = NULL;
	unsigned int tmp = 0;
	while (tmp <= index) {
		qtr = ptr;
		ptr = ptr->GetNode();
		tmp++;
	}
	DataType result = ptr->GetData();
	qtr->SetNode(ptr->GetNode());

	delete ptr;
	this->Length--;
	return result;
}
// ���������е�Ԫ�����
template<typename DataType>
void  CircleList<DataType>::Clear() {
	assert(this->Head != NULL);
	if (this->Length == 0) return;
	SingleNode<DataType>*qtr = this->Head;
	SingleNode<DataType>*ptr = this->Head->GetNode();
	while (ptr != this->Head) {
		qtr = ptr;
		ptr = ptr->GetNode();
		delete qtr;
	}
	this->Head->SetNode(this->Head);
	this->Length = 0;
}
// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
template<typename DataType>
SingleNode<DataType>* CircleList<DataType>::GetNode(unsigned int index) {
	assert(this->Head != NULL && index <this->Length);
	unsigned int tmp = 0;
	SingleNode<DataType>*ptr = this->Head;
	while (tmp <= index) {
		ptr = ptr->GetNode();
		tmp++;
	}
	return ptr;
}
// ��������index���Ľڵ�����ΪNode�ڵ�
template<typename DataType>
void  CircleList<DataType>::SetNode(unsigned int index, SingleNode<DataType>* newnode) {
	assert(this->Head != NULL && index <this->Length);
	SingleNode<DataType>*ptr = this->Head;
	SingleNode<DataType>*qtr = NULL;
	unsigned int tmp = 0;
	while (tmp <= index) {
		qtr = ptr;
		ptr = ptr->GetNode();
		tmp++;
	}
	qtr->SetNode(newnode);
	while (ptr != this->Head) {
		qtr = ptr;
		ptr = ptr->GetNode();
		delete qtr;
	}
}
// ��ȡ����ͷ������ֵ
template<typename DataType>
DataType  CircleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNode()->GetData();
}
// ��ȡ����β������ֵ
template<typename DataType>
DataType CircleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !CIRCLELIST_H
#ifndef BICIRCLELIST_H
#define BICIRCLELIST_H
//����һ���������б�ͷ�ڵ��˫������
template<typename DataType>
class BiCircleList :public LinkedList<DataType> {
public:
	DoubleNode<DataType>*Head;
public:
	//���캯��
	BiCircleList() {
		this->Head = new DoubleNode<DataType>();
		this->Length = 0;
		this->Head->SetNextNode(this->Head);
		this->Head->SetPreviousNode(this->Head);
	}
	//������ĺ������һ��Ԫ��
	void Push_Back(DataType Data);
	//�������ǰ�����һ��Ԫ��
	void Push_Front(DataType Data);
	//�������ǰ��ɾ��һ��Ԫ��
	DataType Pop_Front();
	//������ĺ���ɾ��һ��Ԫ��
	DataType Pop_Back();
	//��index������һ��Ԫ��
	void Insert(unsigned int index, DataType Data);
	//ɾ��index����Ԫ��
	DataType Delete(unsigned int index);
	// ���������е�Ԫ�����
	void Clear();
	// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
	DoubleNode<DataType>* GetNode(unsigned int index);
	// ��������index���Ľڵ�����ΪNode�ڵ�
	void SetNode(unsigned int index, DoubleNode<DataType>* newnode);
	// ��ȡ����ͷ������ֵ
	DataType Front();
	// ��ȡ����β������ֵ
	DataType Back();
	//����������������������
	~BiCircleList() {
		DoubleNode<DataType>*qtr = NULL;
		DoubleNode<DataType>*ptr = this->Head;
		while (ptr != this->Head) {
			qtr = ptr;
			ptr = ptr->GetNextNode();
			delete qtr;
		}
		this->Length = 0;
	}
};

//��˫�����ʵ�ַ���
//������ĺ������һ��Ԫ��
template<typename DataType>
void BiCircleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	//�õ����һ��Ԫ�ص�ָ��
	DoubleNode<DataType>* lastptr = this->Head->GetPreviousNode();
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, lastptr,this->Head);
	this->Head->SetPreviousNode(newnode);
	lastptr->SetNextNode(newnode);
	this->Length++;
}
//�������ǰ�����һ��Ԫ��
template<typename DataType>
void BiCircleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, this->Head, this->Head->GetNextNode());
	this->Head->GetNextNode()->SetPreviousNode(newnode);
	this->Head->SetNextNode(newnode);
	this->Length++;
}
//�������ǰ��ɾ��һ��Ԫ��
template<typename DataType>
DataType BiCircleList<DataType>::Pop_Front() {
	assert(this->Head != NULL && this->GetLength() != 0);
	DoubleNode<DataType>*ptr = this->Head->GetNextNode();
	this->Head->SetNextNode(ptr->GetNextNode());
	ptr->GetNextNode()->SetPreviousNode(this->Head);
	DataType tmp = ptr->GetData();
	delete ptr;
	this->Length--;
	return tmp;
}
//������ĺ���ɾ��һ��Ԫ��
template<typename DataType>
DataType BiCircleList<DataType>::Pop_Back() {
	assert(this->Head != NULL && this->GetLength() != 0);
	//�õ����һ��Ԫ��
	DoubleNode<DataType>*lastptr = this->Head->GetPreviousNode();
	this->Head->SetPreviousNode(lastptr->GetPreviousNode());
	lastptr->GetPreviousNode()->SetNextNode(this->Head);
	DataType tmp = lastptr->GetData();
	delete lastptr;
	this->Length--;
	return tmp;
}

// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
template<typename DataType>
DoubleNode<DataType>* BiCircleList<DataType>::GetNode(unsigned int index) {
	assert(this->Head != NULL && index <this->Length);
	unsigned int tmp = 0;
	DoubleNode<DataType>*ptr = this->Head;
	while (tmp <= index) {
		ptr = ptr->GetNextNode();
		tmp++;
	}
	return ptr;
}
//��index������һ��Ԫ��
template<typename DataType>
void  BiCircleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	DoubleNode<DataType>*ptr = this->GetNode(index);
	DoubleNode<DataType>*newnode = new DoubleNode<DataType>(Data, ptr->GetPreviousNode(), ptr);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	ptr->SetPreviousNode(newnode);
	this->Length++;
}
//ɾ��index����Ԫ��
template<typename DataType>
DataType  BiCircleList<DataType>::Delete(unsigned int index) {
	assert(this->Head != NULL && index <this->GetLength() && this->GetLength() != 0);
	DoubleNode<DataType>*ptr = this->GetNode(index);
	ptr->GetNextNode()->SetPreviousNode(ptr->GetPreviousNode());
	ptr->GetPreviousNode()->SetNextNode(ptr->GetNextNode());
	DataType result = ptr->GetData();
	delete ptr;
	this->Length--;
	return result;
}
// ���������е�Ԫ�����
template<typename DataType>
void  BiCircleList<DataType>::Clear() {
	assert(this->Head != NULL);
	if (this->Length == 0) return;
	DoubleNode<DataType>*qtr = this->Head;
	DoubleNode<DataType>*ptr = this->Head->GetNextNode();
	while (ptr != this->Head) {
		qtr = ptr;
		ptr = ptr->GetNextNode();
		delete qtr;
	}
	this->Head->SetNextNode(this->Head);
	this->Head->SetPreviousNode(this->Head);
	this->Length = 0;
}
// ��������index���Ľڵ�����ΪNode�ڵ�
template<typename DataType>
void  BiCircleList<DataType>::SetNode(unsigned int index, DoubleNode<DataType>* newnode) {
	assert(this->Head != NULL && index <this->Length);
	DoubleNode<DataType>* ptr = this->GetNode(index);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	DoubleNode<DataType>* qtr = NULL;
	while (ptr != this->Head) {
		qtr = ptr;
		ptr = ptr->GetNextNode();
		delete qtr;
	}
}

// ��ȡ����ͷ������ֵ
template<typename DataType>
DataType  BiCircleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNextNode()->GetData();
}
// ��ȡ����β������ֵ
template<typename DataType>
DataType BiCircleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetPreviousNode()->GetData();
}
#endif // !BICIRCLELIST_H

