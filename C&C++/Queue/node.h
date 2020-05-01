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
// 球节点指针，它包括普通经纬度节点、含有多个指出去的北极节点、含有多个指进去的南极节点
template<typename DataType>
class ShpereNode :public Node<DataType> {
private:
	ShpereNode<DataType>*LeftPtr;
	ShpereNode<DataType>*RightPtr;
	ShpereNode<DataType>*Previoustr;
	ShpereNode<DataType>*NextPtr;
public:
	ShpereNode() {
		this->LeftPtr = NULL;
		this->RightPtr = NULL;
		this->NextPtr = NULL;
		this->Previoustr = NULL;
	}
	ShpereNode(ShpereNode<DataType>*LeftPtr, ShpereNode<DataType>*RightPtr, ShpereNode<DataType>*Previoustr, ShpereNode<DataType>*NextPtr) {
		this->LeftPtr = LeftPtr;
		this->RightPtr = RightPtr;
		this->Previoustr = Previoustr;
		this->NextPtr = NextPtr;
	}
	ShpereNode<DataType>* GetLeft() {
		return this->LeftPtr;
	}
	void SetLeft(ShpereNode<DataType>*LeftPtr) {
		this->LeftPtr = LeftPtr;
	}
	ShpereNode<DataType>* GetRight() {
		return this->RightPtr;
	}
	void SetRight(ShpereNode<DataType>*RightPtr) {
		this->RightPtr = RightPtr;
	}
	ShpereNode<DataType>* GetPrevious() {
		return this->Previoustr;
	}
	void SetPrevious(ShpereNode<DataType>*Previoustr) {
		this->Previoustr = Previoustr;
	}
	ShpereNode<DataType>* GetNext() {
		return this->NextPtr;
	}
	void SetNext(ShpereNode<DataType>*NextPtr) {
		this->NextPtr = NextPtr;
	}
};
//二叉树节点指针
