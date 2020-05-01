#pragma once
#ifndef BITREE_H
#define BITREE_H
#define NULL 0 
#include<iostream>
# include<string>
#include"stack.h"
#include"queue.h"
template<typename DataType>
class BiTreeNode {
private:
	BiTreeNode<DataType> *LeftChild;
	BiTreeNode<DataType>  *RightChild;
	DataType Data;
public:
	BiTreeNode() {
		this->LeftChild = NULL;
		this->RightChild = NULL;
	}
	BiTreeNode(DataType Data, BiTreeNode<DataType>*LeftChild, BiTreeNode<DataType>*RightChild) {
		this->LeftChild = LeftChild;
		this->RightChild = RightChild;
		this->Data = Data;
	}
	DataType GetData() {
		return this->Data;
	}
	BiTreeNode<DataType> * GetLeftChild() {
		return this->LeftChild;;
	}
	BiTreeNode<DataType> * GetRightChild() {
		return this->RightChild;
	}
	void SetLeftChild(BiTreeNode<DataType>*LeftChild) {
		this->LeftChild = LeftChild;
	}
	void SetRightChild(BiTreeNode<DataType>*RightChild) {
		this->RightChild = RightChild;
	}
	void SetData(DataType Data) {
		this->Data = Data;
	}
};
#endif // !BITREE_H


#ifndef BITREE_TREE_H
#define BITREE_TREE_H
template<typename DataType>
class BiTree {
private:
	BiTreeNode<DataType> * root;
	void static DeleteTree(BiTreeNode<DataType> * tree) {
		if (tree != NULL) {
			if (tree->GetLeftChild() == NULL && tree->GetRightChild() == NULL) {
				delete tree;
			}
			else {
				BiTree::DeleteTree(tree->GetLeftChild());
				BiTree::DeleteTree(tree->GetRightChild());
			}
		}
	}
public:
	BiTree(BiTreeNode<DataType> * root) {
		this->root = root;
	}
	~BiTree(){
		BiTree::DeleteTree(this->root);
	}
	void PreOrderVisit() {
		BiTreeNode<DataType>* ptr = this->root;
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr!=NULL ||!stack.IsEmpty()){
			while (ptr!= NULL) {
				stack.Push(ptr);
				std::cout << ptr->GetData() << " ";
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Pop();
			ptr = ptr->GetRightChild();
		}
	}
	void InOrderVisit() {
		BiTreeNode<DataType>* ptr = this->root;
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				stack.Push(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Pop();
			std::cout << ptr->GetData() << " ";
			ptr = ptr->GetRightChild();
		}
	}
	void PostOrderVisit() {
		BiTreeNode<DataType>* ptr = this->root;
		BiTreeNode<DataType>* pre = NULL;
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				stack.Push(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Top();
			if (ptr->GetRightChild() == NULL || ptr->GetRightChild() == pre) {
				std::cout << ptr->GetData() << " ";
				pre = ptr;
				ptr = NULL;
				stack.Pop();
			}
			else ptr = ptr->GetRightChild();
		}
	}
	void LevelVisit() {
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
	BiTreeNode<DataType>* GetParent(BiTreeNode<DataType>* subtree) {
		if (subtree == this->root) return NULL;
		// Using the inorder traversal to find its parent node
		BiTreeNode<DataType>* ptr = this->root;
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				if (ptr->GetLeftChild() == subtree) return ptr->GetLeftChild();
				else {
					ptr = ptr->GetLeftChild();
					stack.Push(ptr);
				}
			}
			ptr = stack.Pop();
			if (ptr->GetRightChild() == subtree) return ptr->GetRightChild();
			else ptr = ptr->GetRightChild();
		}
	}
};
#endif // !BITREE_TREE_H
#ifndef CREATE_TREE_H
#define CREATE_TREE_H
BiTreeNode<char>* CreateBiTree(std::string preorder, std::string inorder) {
	if (preorder.length() == 0) return NULL;
	BiTreeNode<char>* root = new BiTreeNode<char>;
	unsigned int length = preorder.length();
	char c = preorder[0];
	unsigned int mid = inorder.find(c);
	std::string inA = inorder.substr(0, mid);
	std::string inB = inorder.substr(mid + 1, length);
	std::string preA = preorder.substr(1, inA.length());
	std::string preB = preorder.substr(inA.length() + 1, length);
	BiTreeNode<char>* LeftChild = CreateBiTree(preA, inA);
	BiTreeNode<char>* RightChild = CreateBiTree(preB, inB);
	root->SetData(c);
	root->SetLeftChild(LeftChild);
	root->SetRightChild(RightChild);
	return root;
}
template<typename DataType>
void PreOrderVisitWithNoStack(BiTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	std::cout << tree->GetData() <<" ";
	PreOrderVisitWithNoStack(tree->GetLeftChild());
	PreOrderVisitWithNoStack(tree->GetRightChild());
}
template<typename DataType>
void InOrderVisitWithNoStack(BiTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	InOrderVisitWithNoStack(tree->GetLeftChild());
	std::cout << tree->GetData() << " ";
	InOrderVisitWithNoStack(tree->GetRightChild());
}
template<typename DataType>
void PostOrderVisitWithNoStack(BiTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	PostOrderVisitWithNoStack(tree->GetLeftChild());
	PostOrderVisitWithNoStack(tree->GetRightChild());
	std::cout << tree->GetData()<< " ";
}
template<typename DataType>
unsigned int GetTreeDepthWithNoStack(BiTreeNode<DataType>* tree) {
	if (tree == NULL) return 0;
	if (GetTreeDepthWithNoStack(tree->GetLeftChild()) > GetTreeDepthWithNoStack(tree->GetRightChild())) return 1 + GetTreeDepthWithNoStack(tree->GetLeftChild());
	else return 1 + GetTreeDepthWithNoStack(tree->GetRightChild());
}
template<typename DataType>
unsigned int GetTreeLeavesWithNoStack(BiTreeNode<DataType>* tree) {
	if (tree == NULL) return 0;
	if (tree->GetLeftChild() == NULL && tree->GetRightChild() == NULL) return 1;
	else  return GetTreeLeavesWithNoStack(tree->GetLeftChild())+GetTreeLeavesWithNoStack(tree->GetRightChild());
}
#endif // !CREATE_TREE_H

