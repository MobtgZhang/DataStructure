#pragma once
#ifndef NODE_H
#define NODE_H
#define NULL 0
template<typename DataType>
class Node {
protected:
	DataType Data;
public:
	void SetData(DataType Data) {
		this->Data = Data;
	}
	DataType GetData() {
		return this->Data;
	}
	//重载比较运算符
	bool operator >(const Node<DataType>& item) const {
		return this->Data > item.GetData();
	}
	bool operator <(const Node<DataType>& item) const {
		return this->Data < item.GetData();
	}
	bool operator >=(const Node<DataType>& item) const {
		return this->Data >= item.GetData();
	}
	bool operator <=(const Node<DataType>& item) const {
		return this->Data <= item.GetData();
	}
	bool operator == (const Node<DataType>& item) const {
		return this->Data == item.GetData();
	}
	bool operator !=(const Node<DataType>& item) const {
		return this->Data > item.GetData();
	}
	//重载数学运算符
	DataType operator +(const Node<DataType>& item) const {
		return this->Data + item.GetData();
	}
	DataType operator -(const Node<DataType>& item) const {
		return this->Data - item.GetData();
	}
	DataType operator *(const Node<DataType>& item) const {
		return this->Data * item.GetData();
	}
	DataType operator /(const Node<DataType>& item) const {
		return this->Data / item.GetData();
	}
	//重载赋值运算符
	bool operator =(const Node<DataType>& item) const {
		return this->Data = item.GetData();
	}
};
//含有下一个节点指针的节点
#endif // !NODE_H
#ifndef SINGLENODE_H
#define SINGLENODE_H
template<typename DataType>
class SingleNode:public Node<DataType> {
private:
	SingleNode<DataType> * Nextptr;
public:
	SingleNode() {
		this->Nextptr = NULL;
	}
	SingleNode(DataType Data, SingleNode<DataType> * Nextptr) {
		this->Data = Data;
		this->Nextptr = Nextptr;
	}
	SingleNode<DataType>* GetNode() {
		return this->Nextptr;
	}
	void SetNode(SingleNode<DataType>* Nextptr) {
		this->Nextptr = Nextptr;
	}
};
//含有上一个节点指针和下一个节点指针的节点
#endif // !SINGLENODE_H
#ifndef DOUBLENODE_H
#define DOUBLENODE_H
template<typename DataType>
class DoubleNode:public Node<DataType> {
private:
	DoubleNode<DataType> * Nextptr;
	DoubleNode<DataType> * Preptr;
public:
	DoubleNode() {
		this->Nextptr = NULL;
		this->Preptr = NULL;
	}
	DoubleNode(DataType Data, DoubleNode<DataType> * Preptr, DoubleNode<DataType> * Nextptr) {
		this->Data = Data;
		this->Nextptr = Nextptr;
		this->Preptr = Preptr;
	}
	DoubleNode<DataType>* GetNextNode() {
		return this->Nextptr;
	}
	DoubleNode<DataType>* GetPreviousNode() {
		return this->Preptr;
	}
	void SetNextNode(DoubleNode<DataType>* Nextptr) {
		this->Nextptr = Nextptr;
	}
	void SetPreviousNode(DoubleNode<DataType>* Preptr) {
		this->Preptr = Preptr;
	}
};
#endif // !DOUBLENODE_H
//二叉树节点指针
