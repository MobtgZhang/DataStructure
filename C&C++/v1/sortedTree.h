#pragma once
#pragma once
#ifndef SORTED_TREE_H
#define SORTED_TREE_H
#include "BiTree.h"
template<typename DataType>
class SortedTree {
private:
	BiTreeNode<DataType>*root;
private:
	void static Insert(BiTreeNode<DataType>* ptr, DataType Data) {
		if (Data < ptr->GetData()) {
			//Insert into Left subtree
			if (ptr->GetLeftChild() == NULL) {
				BiTreeNode<DataType>*p = new BiTreeNode<DataType>(Data, NULL, NULL);
				ptr->SetLeftChild(p);
			}
			else Insert(ptr->GetLeftChild(), Data);
		}
		else {
			//Insert int right subtree
			if (ptr->GetRightChild() == NULL) {
				BiTreeNode<DataType>*p = new BiTreeNode<DataType>(Data, NULL, NULL);
				ptr->SetRightChild(p);
			}
			else Insert(ptr->GetRightChild(), Data);
		}
	}
	DataType static Delete(BiTreeNode<DataType>* ptr, BiTreeNode<DataType>* pre) {
		if (ptr->GetLeftChild() == NULL && ptr->GetRightChild() == NULL) {
			if (ptr == pre->GetRightChild()) pre->SetRightChild(NULL); else pre->SetLeftChild(NULL);
			DataType Data = ptr->GetData();
			delete ptr;
			ptr = NULL;
			return Data;
		}
		else if (ptr->GetRightChild() == NULL || ptr->GetLeftChild() == NULL) {
			BiTreeNode<DataType>* Temp = ptr->GetRightChild() == NULL ? ptr->GetLeftChild() : ptr->GetRightChild();
			DataType Data = ptr->GetData();
			ptr->SetData(Temp->GetData());
			ptr->SetLeftChild(Temp->GetLeftChild());
			ptr->SetRightChild(Temp->GetRightChild());
			delete Temp;
			return Data;
		}
		else {
			BiTreeNode<DataType>* p = ptr;
			while (p->GetLeftChild() != NULL) p = p->GetLeftChild();
			pre = ptr;
			DataType Datap = SortedTree::Delete(p, pre);
			DataType Dataptr = ptr->GetData();
			ptr->SetData(Datap);
			return Dataptr;
		}
	}
	bool static DeleteValue(BiTreeNode<DataType>*root, BiTreeNode<DataType>*pre, DataType Data) {
		if (root == NULL) return false;
		if (Data < root->GetData()) {
			pre = root;
			if (root->GetLeftChild() != NULL) return DeleteValue(root->GetLeftChild(), pre, Data);
			else return false;
		}
		else if (Data > root->GetData()) {
			pre = root;
			if (root->GetRightChild() != NULL) return DeleteValue(root->GetRightChild(), pre, Data);
			else return false;
		}
		else if (Data == root->GetData()) {
			SortedTree::Delete(root, pre);
			return true;
		}
		else return false;
	}
	static unsigned int GetHeight(BiTreeNode<DataType>*root) {
		if (root == NULL) return 0;
		if (GetHeight(root->GetLeftChild()) > GetHeight(root->GetRightChild())) return 1 + GetHeight(root->GetLeftChild());
		else return 1 + GetHeight(root->GetRightChild());
	}
public:
	SortedTree() {
		this->root = NULL;
	}
	void AddNode(DataType Data) {
		if (this->root == NULL)this->root = new BiTreeNode<DataType>(Data, NULL, NULL);
		else SortedTree<DataType>::Insert(this->root, Data);
	}
	void LevelTraversal() {
		BiTreeNode<DataType>* ptr;
		Queue<BiTreeNode<DataType>*> queue;
		queue.EnQueue(this->root);
		while (!queue.IsEmpty()) {
			ptr = queue.DeQueue();
			std::cout << ptr->GetData() << " ";
			if (ptr->GetLeftChild() != NULL) queue.EnQueue(ptr->GetLeftChild());
			if (ptr->GetRightChild() != NULL) queue.EnQueue(ptr->GetRightChild());
		}
	}
	bool DeleteNode(DataType Data) {
		if (this->root == NULL) return false;
		else {
			return SortedTree::DeleteValue(this->root, NULL, Data);
		}
	}
	BiTreeNode<DataType>* GetRoot() {
		return this->root;
	}
	unsigned int GetSortedTreeHeight() {
		return SortedTree<DataType>::GetHeight(this->root);
	}
	~SortedTree() {

	}
};
#endif // !SORTED_TREE_H
