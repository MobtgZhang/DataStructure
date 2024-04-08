#pragma once
#include"node.h"
#include<cassert>
#include<string>
#include<sstream>
#include<iostream>
#ifndef LIST_H
#define LIST_H
//定义抽象链表类
template<typename DataType>
class LinkedList {
protected:
	unsigned int Length;
public:
	//在链表的后面插入一个元素
	virtual void Push_Back(DataType Data) = 0;
	//在链表的前面插入一个元素
	virtual void Push_Front(DataType Data) = 0;
	//从链表的前面删除一个元素
	virtual DataType Pop_Front() = 0;
	//从链表的后面删除一个元素
	virtual DataType Pop_Back() = 0;
	//从index处插入一个元素
	virtual void Insert(unsigned int index, DataType Data) = 0;
	//删除index处的元素
	virtual DataType Delete(unsigned int index) = 0;
	// 将本链表中的元素清空
	virtual void Clear() = 0;
	// 获取链表中index的元素的指针，和运算符[]的作用类似，
	virtual Node<DataType>* GetNode(unsigned int index) = 0;
	// 将链表中index处的节点设置为Node节点
	virtual void SetNode(unsigned int index, Node<DataType>* newnode) {}
	// 获取链表中index处的节点的值
	DataType operator[](unsigned int index) { return this->GetNode(index)->GetData(); }
	// 将index处的节点值设置为data
	void Set(unsigned int index, DataType Data) {
		this->GetNode(index)->SetData(Data);
	}
	//获取链表中index处的元素值，这个和[]运算符的作用一致
	DataType Get(unsigned int index) { return this->GetNode(index)->GetData(); }
	// 获取链表的长度信息
	unsigned int GetLength() { return this->Length; }
	// 获取链表头部的数值
	virtual DataType Front() = 0;
	// 获取链表尾部的数值
	virtual DataType Back() = 0;
	// 判断链表是否为空
	bool IsEmpty() {return this->Length == 0;}
	// 获取链表的字符串格式，可以重载函数
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
	// 打印链表元素，可以重载函数
	void print() {
		std::cout << this->toString() << std::endl;
	}
};
#endif // !LIST_H
#ifndef SINGLELIST_H
#define SINGLELIST_H
//定义一个仅含有头结点的单链表
template<typename DataType>
class SingleList :public LinkedList<DataType> {
private:
	SingleNode<DataType>*Head;
public:
	//构造函数
	SingleList() {
		this->Head = new SingleNode<DataType>();
		this->Length = 0;
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

	//析构函数，用于销毁链表
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
//对单链表的实现方法
//在链表的后面插入一个元素
template<typename DataType>
void SingleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	SingleNode<DataType>*ptr = this->Head;
	while (ptr->GetNode() != NULL) ptr = ptr->GetNode();
	SingleNode<DataType>* newnode = new SingleNode<DataType>(Data, NULL);
	ptr->SetNode(newnode);
	this->Length++;
}
//在链表的前面插入一个元素
template<typename DataType>
void SingleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	this->Head->SetNode(new SingleNode<DataType>(Data, this->Head->GetNode()));
	this->Length++;
}
//从链表的前面删除一个元素
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
//从链表的后面删除一个元素
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
//从index处插入一个元素
template<typename DataType>
void  SingleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	SingleNode<DataType>*ptr = this->GetNode(index);
	SingleNode<DataType>*newnode = new SingleNode<DataType>(ptr->GetData(), ptr->GetNode());
	ptr->SetData(Data);
	ptr->SetNode(newnode);
	this->Length++;
}
//删除index处的元素
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
// 将本链表中的元素清空
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
// 获取链表中index的元素的指针，和运算符[]的作用类似，
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
// 将链表中index处的节点设置为Node节点
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
// 获取链表头部的数值
template<typename DataType>
DataType  SingleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNode()->GetData();
}
// 获取链表尾部的数值
template<typename DataType>
DataType SingleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !SINGLELIST_H
#ifndef DOUBLELIST_H
#define DOUBLELIST_H
//定义一个仅仅含有表头节点的双向链表
template<typename DataType>
class DoubleList :public LinkedList<DataType> {
private:
	DoubleNode<DataType>*Head;
public:
	//构造函数
	DoubleList() {
		this->Head = new DoubleNode<DataType>();
		this->Length = 0;
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

//对双链表的实现方法
//在链表的后面插入一个元素
template<typename DataType>
void DoubleList<DataType>::Push_Back(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>*ptr = this->Head;
	while (ptr->GetNextNode() != NULL) ptr = ptr->GetNextNode();
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, ptr,NULL);
	ptr->SetNextNode(newnode);
	this->Length++;
}
//在链表的前面插入一个元素
template<typename DataType>
void DoubleList<DataType>::Push_Front(DataType Data) {
	assert(this->Head != NULL);
	DoubleNode<DataType>* newnode = new DoubleNode<DataType>(Data, this->Head,this->Head->GetNextNode());
	this->Head->GetNextNode()->SetPreviousNode(newnode);
	this->Head->SetNextNode(newnode);
	this->Length++;
}
//从链表的前面删除一个元素
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
//从链表的后面删除一个元素
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

// 获取链表中index的元素的指针，和运算符[]的作用类似，
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
//从index处插入一个元素
template<typename DataType>
void  DoubleList<DataType>::Insert(unsigned int index, DataType Data) {
	assert(this->Head != NULL && index <this->GetLength());
	DoubleNode<DataType>*ptr = this->GetNode(index);
	DoubleNode<DataType>*newnode = new DoubleNode<DataType>(Data,ptr->GetPreviousNode(),ptr);
	ptr->GetPreviousNode()->SetNextNode(newnode);
	ptr->SetPreviousNode(newnode);
	this->Length++;
}
//删除index处的元素
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
// 将本链表中的元素清空
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
// 将链表中index处的节点设置为Node节点
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

// 获取链表头部的数值
template<typename DataType>
DataType  DoubleList<DataType>::Front() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Head->GetNextNode()->GetData();
}
// 获取链表尾部的数值
template<typename DataType>
DataType DoubleList<DataType>::Back() {
	assert(this->Head != NULL &&this->Length != 0);
	return this->Get(this->Length - 1);
}
#endif // !DOUBLELIST_H

