#pragma once
#include"node.h"
#include<cassert>
#include<string>
#include<sstream>
#include<iostream>
#ifndef LIST_H
#define LIST_H
//�������������
template<typename DataType>
class LinkedList {
protected:
	unsigned int Length;
public:
	//������ĺ������һ��Ԫ��
	virtual void Push_Back(DataType Data) = 0;
	//�������ǰ�����һ��Ԫ��
	virtual void Push_Front(DataType Data) = 0;
	//�������ǰ��ɾ��һ��Ԫ��
	virtual DataType Pop_Front() = 0;
	//������ĺ���ɾ��һ��Ԫ��
	virtual DataType Pop_Back() = 0;
	//��index������һ��Ԫ��
	virtual void Insert(unsigned int index, DataType Data) = 0;
	//ɾ��index����Ԫ��
	virtual DataType Delete(unsigned int index) = 0;
	// ���������е�Ԫ�����
	virtual void Clear() = 0;
	// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
	virtual Node<DataType>* GetNode(unsigned int index) = 0;
	// ��������index���Ľڵ�����ΪNode�ڵ�
	virtual void SetNode(unsigned int index, Node<DataType>* newnode) {}
	// ��ȡ������index���Ľڵ��ֵ
	DataType operator[](unsigned int index) { return this->GetNode(index)->GetData(); }
	// ��index���Ľڵ�ֵ����Ϊdata
	void Set(unsigned int index, DataType Data) {
		this->GetNode(index)->SetData(Data);
	}
	//��ȡ������index����Ԫ��ֵ�������[]�����������һ��
	DataType Get(unsigned int index) { return this->GetNode(index)->GetData(); }
	// ��ȡ����ĳ�����Ϣ
	unsigned int GetLength() { return this->Length; }
	// ��ȡ����ͷ������ֵ
	virtual DataType Front() = 0;
	// ��ȡ����β������ֵ
	virtual DataType Back() = 0;
	// �ж������Ƿ�Ϊ��
	bool IsEmpty() {return this->Length == 0;}
	// ��ȡ������ַ�����ʽ���������غ���
	std::string toString() {
		std::stringstream s_stream;
		std::string result = "";
		for (unsigned int k = 0; k < this->Length; k++) {
			s_stream << this->Get(k);
			std::string tmp;
			s_stream >> tmp;
			result = result + tmp + " ";
			s_stream.clear();
		}
		return result;
	}
	// ��ӡ����Ԫ�أ��������غ���
	void print() {
		std::cout << this->toString() << std::endl;
	}
};
#endif // !LIST_H
#ifndef SINGLELIST_H
#define SINGLELIST_H
//����һ��������ͷ���ĵ�����
template<typename DataType>
class SingleList :public LinkedList<DataType> {
private:
	SingleNode<DataType>*Head;
public:
	//���캯��
	SingleList() {
		this->Head = new SingleNode<DataType>();
		this->Length = 0;
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

	//����������������������
	~SingleList() {
		SingleNode<DataType>*qtr = NULL;
		SingleNode<DataType>*ptr = this->Head;
		while (ptr != NULL) {
			qtr = ptr;
			ptr = ptr->GetNode();
			delete qtr;
		}
		this->Length = 0;
	}
};
//�Ե������ʵ�ַ���
//������ĺ������һ��Ԫ��
template<typename DataType>
void SingleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	SingleNode<DataType>*ptr = this->Head;
	while (ptr->GetNode() != NULL) ptr = ptr->GetNode();
	SingleNode<DataType>* newnode = new SingleNode<DataType>(Data, NULL);
	ptr->SetNode(newnode);
	this->Length++;
}
//�������ǰ�����һ��Ԫ��
template<typename DataType>
void SingleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	this->Head->SetNode(new SingleNode<DataType>(Data, this->Head->GetNode()));
	this->Length++;
}
//�������ǰ��ɾ��һ��Ԫ��
template<typename DataType>
DataType SingleList<DataType>::Pop_Front() {
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
DataType SingleList<DataType>::Pop_Back() {
	assert(this->Head != NULL && this->GetLength() != 0);
	SingleNode<DataType>*qtr = this->Head;
	SingleNode<DataType>*ptr = qtr->GetNode();
	while (ptr->GetNode() != NULL) {
		qtr = ptr;
		ptr = ptr->GetNode();
	}
	DataType tmp = ptr->GetData();
	delete ptr;
	this->Length--;
	qtr->SetNode(NULL);
	return tmp;
}
//��index������һ��Ԫ��
template<typename DataType>
void  SingleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	SingleNode<DataType>*ptr = this->GetNode(index);
	SingleNode<DataType>*newnode = new SingleNode<DataType>(ptr->GetData(), ptr->GetNode());
	ptr->SetData(Data);
	ptr->SetNode(newnode);
	this->Length++;
}
//ɾ��index����Ԫ��
template<typename DataType>
DataType  SingleList<DataType>::Delete(unsigned int index) {
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
void  SingleList<DataType>::Clear() {
	assert(this->Head != NULL);
	if (this->Length == 0) return;
	SingleNode<DataType>*qtr = this->Head;
	SingleNode<DataType>*ptr = this->Head->GetNode();
	while (ptr != NULL) {
		qtr = ptr;
		ptr = ptr->GetNode();
		delete qtr;
	}
	this->Head->SetNode(NULL);
	this->Length = 0;
}
// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
template<typename DataType>
SingleNode<DataType>* SingleList<DataType>::GetNode(unsigned int index) {
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
void  SingleList<DataType>::SetNode(unsigned int index, SingleNode<DataType>* newnode) {
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
	while (ptr != NULL) {
		qtr = ptr;
		ptr = ptr->GetNode();
		delete qtr;
	}
}
// ��ȡ����ͷ������ֵ
template<typename DataType>
DataType  SingleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNode()->GetData();
}
// ��ȡ����β������ֵ
template<typename DataType>
DataType SingleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !SINGLELIST_H
#ifndef DOUBLELIST_H
#define DOUBLELIST_H
//����һ���������б�ͷ�ڵ��˫������
template<typename DataType>
class DoubleList :public LinkedList<DataType> {
private:
	DoubleNode<DataType>*Head;
public:
	//���캯��
	DoubleList() {
		this->Head = new DoubleNode<DataType>();
		this->Length = 0;
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
	~DoubleList() {
		DoubleNode<DataType>*qtr = NULL;
		DoubleNode<DataType>*ptr = this->Head;
		while (ptr != NULL) {
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
void DoubleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>*ptr = this->Head;
	while (ptr->GetNextNode() != NULL) ptr = ptr->GetNextNode();
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, ptr,NULL);
	ptr->SetNextNode(newnode);
	this->Length++;
}
//�������ǰ�����һ��Ԫ��
template<typename DataType>
void DoubleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, this->Head,this->Head->GetNextNode());
	this->Head->GetNextNode()->SetPreviousNode(newnode);
	this->Head->SetNextNode(newnode);
	this->Length++;
}
//�������ǰ��ɾ��һ��Ԫ��
template<typename DataType>
DataType DoubleList<DataType>::Pop_Front() {
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
DataType DoubleList<DataType>::Pop_Back() {
	assert(this->Head != NULL && this->GetLength() != 0);
	DoubleNode<DataType>*ptr = this->Head;
	while (ptr->GetNextNode() != NULL){
		ptr = ptr->GetNextNode();
	}
	
	
	ptr->GetPreviousNode()->SetNextNode(NULL);
	
	DataType tmp = ptr->GetData();
	delete ptr;
	this->Length--;
	return tmp;
}

// ��ȡ������index��Ԫ�ص�ָ�룬�������[]���������ƣ�
template<typename DataType>
DoubleNode<DataType>* DoubleList<DataType>::GetNode(unsigned int index) {
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
void  DoubleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	DoubleNode<DataType>*ptr = this->GetNode(index);
	DoubleNode<DataType>*newnode = new DoubleNode<DataType>(Data,ptr->GetPreviousNode(),ptr);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	ptr->SetPreviousNode(newnode);
	this->Length++;
}
//ɾ��index����Ԫ��
template<typename DataType>
DataType  DoubleList<DataType>::Delete(unsigned int index) {
	assert(this->Head != NULL && index <this->GetLength() && this->GetLength() != 0);
	DoubleNode<DataType>*ptr = this->GetNode(index);
	if (ptr->GetNextNode()!=NULL)
		ptr->GetNextNode()->SetPreviousNode(ptr->GetPreviousNode());
	ptr->GetPreviousNode()->SetNextNode(ptr->GetNextNode());
	DataType result = ptr->GetData();
	delete ptr;
	this->Length--;
	return result;
}
// ���������е�Ԫ�����
template<typename DataType>
void  DoubleList<DataType>::Clear() {
	assert(this->Head != NULL);
	if (this->Length == 0) return;
	DoubleNode<DataType>*qtr = this->Head;
	DoubleNode<DataType>*ptr = this->Head->GetNextNode();
	while (ptr != NULL) {
		qtr = ptr;
		ptr = ptr->GetNextNode();
		delete qtr;
	}
	this->Head->SetNextNode(NULL);
	this->Length = 0;
}
// ��������index���Ľڵ�����ΪNode�ڵ�
template<typename DataType>
void  DoubleList<DataType>::SetNode(unsigned int index, DoubleNode<DataType>* newnode) {
	assert(this->Head != NULL && index <this->Length);
	DoubleNode<DataType>* ptr = this->GetNode(index);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	DoubleNode<DataType>* qtr = NULL;
	while (ptr != NULL) {
		qtr = ptr;
		ptr = ptr->GetNextNode();
		delete qtr;
	}
}

// ��ȡ����ͷ������ֵ
template<typename DataType>
DataType  DoubleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNextNode()->GetData();
}
// ��ȡ����β������ֵ
template<typename DataType>
DataType DoubleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !DOUBLELIST_H

