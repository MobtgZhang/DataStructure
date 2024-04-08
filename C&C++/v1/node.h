#pragma once
#ifndef NODE_H
#define NODE_H
#define NULL 0
template<typename DataType>
class Node {
private:
	Node<DataType> * Nextptr;
	DataType Data;
public:
	Node() {
		this->Nextptr = NULL;
	}
	Node(DataType Data,Node<DataType> * Nextptr) {
		this->Data = Data;
		this->Nextptr = Nextptr;
	}
	Node* GetNode() {
		return this->Nextptr;
	}
	DataType GetData() {
		return this->Data;
	}
	void SetNode(Node<DataType>* Nextptr) {
		this->Nextptr = Nextptr;
	}
	void SetData(DataType Data) {
		this->Data = Data;
	}
};
#endif // !NODE_H
#ifndef DENODE_H
#define DENODE_H
template<typename DataType>
class DeNode {
private:
	DeNode<DataType> * Nextptr;
	DeNode<DataType> * Preptr;
	DataType Data;
public:
	DeNode() {
		this->Nextptr = NULL;
		this->Preptr = NULL;
	}
	DeNode(DataType Data, DeNode<DataType> * Nextptr, DeNode<DataType> * Preptr) {
		this->Data = Data;
		this->Nextptr = Nextptr;
		this->Preptr = Preptr;
	}
	DeNode<DataType>* GetNextNode() {
		return this->Nextptr;
	}
	DeNode<DataType>* GetPreviousNode() {
		return this->Preptr;
	}
	DataType GetData() {
		return this->Data;
	}
	void SetNextNode(DeNode<DataType>* Nextptr) {
		this->Nextptr = Nextptr;
	}
	void SetPreviousNode(DeNode<DataType>* Preptr) {
		this->Preptr = Preptr;
	}
	void SetData(DataType Data) {
		this->Data = Data;
	}
};
#endif // !DENODE_H
#ifndef BITREENODE_H
#define BITREENODE_H
#define NULL 0
template<typename DataType>
class BiTreeNode {
protected:
	DataType Data;
	BiTreeNode<DataType>* LeftChild;
	BiTreeNode<DataType>* RightChild;
	unsigned int height;
public:
	BiTreeNode(DataType Data, BiTreeNode<DataType>* LeftChild, BiTreeNode<DataType>* RightChild) {
		this->Data = Data;
		this->LeftChild = LeftChild;
		this->RightChild = RightChild;
	}
	BiTreeNode(DataType Data) {
		this->Data = Data;
		this->LeftChild = NULL;
		this->RightChild = NULL;
	}
	DataType GetData() { return this->Data; }
	void SetData(DataType Data) { this->Data = Data; }
	BiTreeNode<DataType>* GetLeftChild() { return this->LeftChild; }
	void SetLeftChild(BiTreeNode<DataType>* node) { this->LeftChild = node; }
	BiTreeNode<DataType>* GetRightChild() { return this->RightChild; }
	void SetRightChild(BiTreeNode<DataType>* node) { this->RightChild = node; }
	unsigned int GetHeight() {
		return this->height;
	}
	void SetHeight(unsigned int height) {
		this->height = height;
	}
	~BiTreeNode() {

	}
};
#endif // !BITREENODE_H
