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
	//���رȽ������
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
	//������ѧ�����
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
	//���ظ�ֵ�����
	bool operator =(const Node<DataType>& item) const {
		return this->Data = item.GetData();
	}
};
//������һ���ڵ�ָ��Ľڵ�
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
//������һ���ڵ�ָ�����һ���ڵ�ָ��Ľڵ�
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
// ��ڵ�ָ�룬��������ͨ��γ�Ƚڵ㡢���ж��ָ��ȥ�ı����ڵ㡢���ж��ָ��ȥ���ϼ��ڵ�
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
//�������ڵ�ָ��
