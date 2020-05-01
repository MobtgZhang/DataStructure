#pragma once
#ifndef CIRCLELIST_H
#define CIRCLELIST_H
#include<cassert>
#include"node.h"
#include"List.h"
template<typename DataType>
class CircleList:public  LinkedList<DataType>{
private:
	//注意头结点不存储元素信息
	SingleNode<DataType>*Head;
public:
	CircleList() {
		this->Head = new SingleNode<DataType>();
		this->Head->SetNode(this->Head);
	}
	//在链表的后面插入一个元素
	void Push_Back(DataType Data);
	//在链表的前面插入一个元素
	void Push_Front(DataType Data);
	//从链表的前面删除一个元素
	DataType Pop_Front();
	//从链表的后面删除一个元素
	DataType Pop_Back();
	//从index处插入一个元素
	void Insert(unsigned int index, DataType Data);
	//删除index处的元素
	DataType Delete(unsigned int index);
	// 将本链表中的元素清空
	void Clear();
	// 获取链表中index的元素的指针，和运算符[]的作用类似，
	SingleNode<DataType>* GetNode(unsigned int index);
	// 将链表中index处的节点设置为Node节点
	void SetNode(unsigned int index, SingleNode<DataType>* newnode);
	// 获取链表头部的数值
	DataType Front();
	// 获取链表尾部的数值
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
//对循环单链表的实现方法
//在链表的后面插入一个元素
template<typename DataType>
void CircleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	SingleNode<DataType>*ptr = this->Head;
	while (ptr->GetNode() != this->Head) ptr = ptr->GetNode();
	SingleNode<DataType>* newnode = new SingleNode<DataType>(Data, this->Head);
	ptr->SetNode(newnode);
	this->Length++;
}
//在链表的前面插入一个元素
template<typename DataType>
void CircleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	this->Head->SetNode(new SingleNode<DataType>(Data, this->Head->GetNode()));
	this->Length++;
}
//从链表的前面删除一个元素
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
//从链表的后面删除一个元素
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
//从index处插入一个元素
template<typename DataType>
void  CircleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	SingleNode<DataType>*ptr = this->GetNode(index);
	SingleNode<DataType>*newnode = new SingleNode<DataType>(ptr->GetData(), ptr->GetNode());
	ptr->SetData(Data);
	ptr->SetNode(newnode);
	this->Length++;
}
//删除index处的元素
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
// 将本链表中的元素清空
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
// 获取链表中index的元素的指针，和运算符[]的作用类似，
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
// 将链表中index处的节点设置为Node节点
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
// 获取链表头部的数值
template<typename DataType>
DataType  CircleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNode()->GetData();
}
// 获取链表尾部的数值
template<typename DataType>
DataType CircleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !CIRCLELIST_H
#ifndef BICIRCLELIST_H
#define BICIRCLELIST_H
//定义一个仅仅含有表头节点的双向链表
template<typename DataType>
class BiCircleList :public LinkedList<DataType> {
public:
	DoubleNode<DataType>*Head;
public:
	//构造函数
	BiCircleList() {
		this->Head = new DoubleNode<DataType>();
		this->Length = 0;
		this->Head->SetNextNode(this->Head);
		this->Head->SetPreviousNode(this->Head);
	}
	//在链表的后面插入一个元素
	void Push_Back(DataType Data);
	//在链表的前面插入一个元素
	void Push_Front(DataType Data);
	//从链表的前面删除一个元素
	DataType Pop_Front();
	//从链表的后面删除一个元素
	DataType Pop_Back();
	//从index处插入一个元素
	void Insert(unsigned int index, DataType Data);
	//删除index处的元素
	DataType Delete(unsigned int index);
	// 将本链表中的元素清空
	void Clear();
	// 获取链表中index的元素的指针，和运算符[]的作用类似，
	DoubleNode<DataType>* GetNode(unsigned int index);
	// 将链表中index处的节点设置为Node节点
	void SetNode(unsigned int index, DoubleNode<DataType>* newnode);
	// 获取链表头部的数值
	DataType Front();
	// 获取链表尾部的数值
	DataType Back();
	//析构函数，用于销毁链表
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

//对双链表的实现方法
//在链表的后面插入一个元素
template<typename DataType>
void BiCircleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	//得到最后一个元素的指针
	DoubleNode<DataType>* lastptr = this->Head->GetPreviousNode();
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, lastptr,this->Head);
	this->Head->SetPreviousNode(newnode);
	lastptr->SetNextNode(newnode);
	this->Length++;
}
//在链表的前面插入一个元素
template<typename DataType>
void BiCircleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, this->Head, this->Head->GetNextNode());
	this->Head->GetNextNode()->SetPreviousNode(newnode);
	this->Head->SetNextNode(newnode);
	this->Length++;
}
//从链表的前面删除一个元素
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
//从链表的后面删除一个元素
template<typename DataType>
DataType BiCircleList<DataType>::Pop_Back() {
	assert(this->Head != NULL && this->GetLength() != 0);
	//得到最后一个元素
	DoubleNode<DataType>*lastptr = this->Head->GetPreviousNode();
	this->Head->SetPreviousNode(lastptr->GetPreviousNode());
	lastptr->GetPreviousNode()->SetNextNode(this->Head);
	DataType tmp = lastptr->GetData();
	delete lastptr;
	this->Length--;
	return tmp;
}

// 获取链表中index的元素的指针，和运算符[]的作用类似，
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
//从index处插入一个元素
template<typename DataType>
void  BiCircleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	DoubleNode<DataType>*ptr = this->GetNode(index);
	DoubleNode<DataType>*newnode = new DoubleNode<DataType>(Data, ptr->GetPreviousNode(), ptr);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	ptr->SetPreviousNode(newnode);
	this->Length++;
}
//删除index处的元素
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
// 将本链表中的元素清空
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
// 将链表中index处的节点设置为Node节点
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

// 获取链表头部的数值
template<typename DataType>
DataType  BiCircleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNextNode()->GetData();
}
// 获取链表尾部的数值
template<typename DataType>
DataType BiCircleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetPreviousNode()->GetData();
}
#endif // !BICIRCLELIST_H

