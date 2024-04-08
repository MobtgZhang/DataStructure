#pragma once
#ifndef THEAD_TREE_H
#define THEAD_TREE_H
#define NULL 0
#include <iostream>
#include<string>
#include "stack.h"
template<typename DataType>
class ThreadTreeNode {
private:
	bool ltag, rtag;
	ThreadTreeNode<DataType>* LeftChild;
	ThreadTreeNode<DataType>* RightChild;
	DataType Data;
public:
	ThreadTreeNode() {
		this->LeftChild = NULL;
		this->RightChild = NULL;
		this->ltag = false;
		this->rtag = false;
	}
	bool Getltag() { return this->ltag; }
	bool Getrtag() { return this->rtag; }
	DataType GetData() { return this->Data; }
	ThreadTreeNode<DataType>* GetLeftChild() { return this->LeftChild; }
	ThreadTreeNode<DataType>* GetRightChild() { return this->RightChild; }
	void Setltag(unsigned int ltag) { this->ltag = ltag; }
	void Setrtag(unsigned int rtag) { this->rtag = rtag; }
	void SetData(DataType Data) { this->Data = Data; }
	void SetLeftChild(ThreadTreeNode<DataType>* LeftChild) { this->LeftChild = LeftChild; }
	void SetRightChild(ThreadTreeNode<DataType>* RightChild) { this->RightChild = RightChild; }
};
#endif // !THEAD_TREE_H

#ifndef THEADTREE_H
#define THEADTREE_H
template<typename DataType>
class ThreadTree {
private:
	ThreadTreeNode<DataType>* root;
	int ThreadTag;
public:
	ThreadTree() {
		this->root = NULL;
	}
	ThreadTree(ThreadTreeNode<DataType>* root) {
		this->root = root;
		this->ThreadTag = -1;
	}
	ThreadTreeNode<DataType>*GetRoot() {
		return this->root;
	}
	void SetRoot(ThreadTreeNode<DataType>* root) {
		this->root = root;
	}
	void Inorder() {
		if (this->ThreadTag != 1) return;
		for (ThreadTreeNode<DataType>*p = ThreadTree<DataType>::GetFirstInNode(this->GetRoot()); p != NULL; p = ThreadTree<DataType>::GetNextInNode(p)) {
			std::cout << p->GetData() << " ";
		}
	}
	void Preorder() {
		if (this->ThreadTag != 0) return;
		for (ThreadTreeNode<DataType>*p = ThreadTree<DataType>::GetFirstPreNode(this->GetRoot()); p != NULL; p = ThreadTree<DataType>::GetNextPreNode(p)) {
			std::cout << p->GetData() << " ";
		}
	}
	void Postorder() {
		if (this->ThreadTag != 2) return;
		Stack<ThreadTreeNode<DataType>*> stack;
		for (ThreadTreeNode<DataType>*p = ThreadTree<DataType>::GetFirstPostNode(this->root,stack); p != NULL; p = ThreadTree<DataType>::GetNextPostNode(p, stack)) {
			std::cout << p->GetData()<< " ";
			//std::cout << "A Address: "<<this->root->GetRightChild() << std::endl;
		}
	}
	~ThreadTree() {
		
	}
	void ClearTree() {
		this->root = NULL;
		this->ThreadTag = -1;
	}
	void ClearTag() {
		ThreadTree::DeleteTreeTag(this->root);
		this->ThreadTag = -1;
	}
public:
	void static DeleteTree(ThreadTreeNode<DataType>*p) {
		if (p == NULL) return;
		else if (p->Getltag() && p->Getrtag()) {
			delete p;
			p = NULL;
		}
		else {
			ThreadTree<DataType>::DeleteTree(p->GetLeftChild());
			ThreadTree<DataType>::DeleteTree(p->GetRightChild());
		}
	}
	void static DeleteTreeTag(ThreadTreeNode<DataType>*p) {
		if (p == NULL) return;
		else if (p->Getltag() && p->Getrtag()) {
			p->Setltag(false);
			p->Setrtag(false);
			p->SetLeftChild(NULL);
			p->SetRightChild(NULL);
		}
		else if(p->Getltag()){
			p->Setltag(false);
			p->SetLeftChild(NULL);
			ThreadTree<DataType>::DeleteTreeTag(p->GetRightChild());
		}
		else if (p->Getrtag()) {
			p->Setrtag(false);
			p->SetRightChild(NULL);
			ThreadTree<DataType>::DeleteTreeTag(p->GetLeftChild());
		}
		else {
			ThreadTree<DataType>::DeleteTreeTag(p->GetLeftChild());
			ThreadTree<DataType>::DeleteTreeTag(p->GetRightChild());
		}
	}
//This is used for the preorder traversal.
private:
	void static InThreadTreePreorder(ThreadTree<DataType>&Tree, ThreadTree<DataType>&Pre) {
		if (Tree.GetRoot() != NULL) {
			if (Tree.GetRoot()->GetLeftChild() == NULL) {
				Tree.GetRoot()->SetLeftChild(Pre.GetRoot());
				Tree.GetRoot()->Setltag(true);
			}
			if (Pre.GetRoot() != NULL && Pre.GetRoot()->GetRightChild() == NULL) {
				Pre.GetRoot()->SetRightChild(Tree.GetRoot());
				Pre.GetRoot()->Setrtag(true);
			}
			Pre.SetRoot(Tree.GetRoot());
			ThreadTree<DataType>p;
			if (!Tree.GetRoot()->Getltag()) {
				p.SetRoot(Tree.GetRoot()->GetLeftChild());
				ThreadTree::InThreadTreePreorder(p, Pre);
			}
			if (!Tree.GetRoot()->Getrtag()) {
				p.SetRoot(Tree.GetRoot()->GetRightChild());
				ThreadTree::InThreadTreePreorder(p, Pre);
			}
		}
	}
public:
	void static CreateInThreadTreePreorder(ThreadTree<DataType>& Tree) {
		ThreadTree<DataType>Pre;
		Tree.ThreadTag = 0;
		if (Tree.GetRoot() != NULL) {
			ThreadTree<DataType>::InThreadTreePreorder(Tree, Pre);
			Pre.GetRoot()->SetRightChild(NULL);
			Pre.GetRoot()->Setrtag(true);
		}
	}
	static ThreadTreeNode<DataType>* GetFirstPreNode(ThreadTreeNode<DataType>*p) {
		return p;
	}
	static ThreadTreeNode<DataType>* GetNextPreNode(ThreadTreeNode<DataType>*p) {
		if (p->Getltag() == 0) return p->GetLeftChild();
		else return p->GetRightChild();
	}
//This is used for the inorder traversal.
private:
	void static InThreadTreeInorder(ThreadTree<DataType>&Tree, ThreadTree<DataType>&Pre) {
		if (Tree.GetRoot() != NULL) {
			ThreadTree<DataType>p(Tree.GetRoot()->GetLeftChild());
			ThreadTree<DataType>::InThreadTreeInorder(p, Pre);
			p.SetRoot(Tree.GetRoot());
			if (p.GetRoot()->GetLeftChild() == NULL) {
				p.GetRoot()->SetLeftChild(Pre.GetRoot());
				p.GetRoot()->Setltag(true);
			}
			if (Pre.GetRoot() != NULL && Pre.GetRoot()->GetRightChild() == NULL) {
				Pre.GetRoot()->SetRightChild(p.GetRoot());
				Pre.GetRoot()->Setrtag(true);
			}
			Pre.SetRoot(p.GetRoot());
			p.SetRoot(Tree.GetRoot()->GetRightChild());
			ThreadTree<DataType>::InThreadTreeInorder(p, Pre);
		}
	}
public:
	void static CreateInThreadTreeInorder(ThreadTree<DataType>& Tree) {
		ThreadTree<DataType>Pre;
		Tree.ThreadTag = 1;
		if (Tree.GetRoot() != NULL) {
			ThreadTree<DataType>::InThreadTreeInorder(Tree, Pre);
			Pre.GetRoot()->SetRightChild(NULL);
			Pre.GetRoot()->Setrtag(true);
		}
	}
	static ThreadTreeNode<DataType>* GetFirstInNode(ThreadTreeNode<DataType>*p) {
		while (p->Getltag() == 0) p = p->GetLeftChild();
		return p;
	}
	static ThreadTreeNode<DataType>* GetNextInNode(ThreadTreeNode<DataType>*p) {
		if (p->Getrtag() == 0) return GetFirstInNode(p->GetRightChild());
		else return p->GetRightChild();
	}
//This is used for the postorder traversal.
private:
	void static InThreadTreePostorder(ThreadTree<DataType>&Tree, ThreadTree<DataType>&Pre) {
		if (Tree.GetRoot() != NULL) {
			ThreadTree<DataType>p(Tree.GetRoot()->GetLeftChild());
			InThreadTreePostorder(p, Pre);
			p.SetRoot(Tree.GetRoot()->GetRightChild());
			InThreadTreePostorder(p, Pre);
			if (Tree.GetRoot()->GetLeftChild() == NULL) {
				Tree.GetRoot()->SetLeftChild(Pre.GetRoot());
				Tree.GetRoot()->Setltag(true);
			}
			if (Pre.GetRoot()!=NULL && Pre.GetRoot()->GetRightChild() == NULL) {
				Pre.GetRoot()->SetRightChild(Tree.GetRoot());
				Pre.GetRoot()->Setrtag(true);
			}
			Pre.SetRoot(Tree.GetRoot());
		}
	}
public:
	void static CreateInThreadTreePostorder(ThreadTree<DataType>& Tree) {
		ThreadTree<DataType>Pre(NULL);
		Tree.ThreadTag = 2;
		if (Tree.GetRoot() != NULL) {
			ThreadTree<DataType>::InThreadTreePostorder(Tree, Pre);
		}
	}
	static ThreadTreeNode<DataType>* GetFirstPostNode(ThreadTreeNode<DataType>*p, Stack<ThreadTreeNode<DataType>*>&stack) {
		while (p->Getltag() == 0) {
			stack.Push(p); p = p->GetLeftChild();
		}
		if (p->Getrtag() == 1) return p;
		else {
			stack.Push(p);
			return ThreadTree<DataType>::GetFirstPostNode(p->GetRightChild(),stack);
		}
	}
	static ThreadTreeNode<DataType>* GetNextPostNode(ThreadTreeNode<DataType>*p, Stack<ThreadTreeNode<DataType>*>&stack) {
		if (p->Getrtag() == 1)	return p->GetRightChild();
		else {
			// Wheather the root node is visited
			if(!stack.IsEmpty()){
				if (p == stack.Top()) {
					//When the left tree is visited.
					stack.Pop();
					if (stack.Top()->GetRightChild() == p) return stack.Pop();
					else return ThreadTree<DataType>::GetFirstPostNode(stack.Top()->GetRightChild(), stack);
				}
				else if (stack.Top()->GetLeftChild() == p) return ThreadTree<DataType>::GetFirstPostNode(stack.Top()->GetRightChild(), stack);
				else return stack.Pop();//(stack.Top()->GetRightChild() == p)
			}
			else return NULL;
		}
	}
public:
	static ThreadTreeNode<DataType>* FindFather(ThreadTreeNode<DataType>*p, ThreadTreeNode<DataType>*root) {
		if (root == NULL) return NULL;
		if (root->GetLeftChild() == p || root->GetRightChild() == p) return root;
		else if (FindFather(root->GetLeftChild(),root)==NULL){
			return FindFather(root->GetRightChild(),root);
		}
		else return FindFather(root->GetLeftChild(),root);
	}
};
#endif // !THEADTREE_H

#ifndef CREATE_THEAD_TREE_H
#define CREATE_THEAD_TREE_H
ThreadTreeNode<char>* CreateThreadTree(std::string preorder, std::string inorder) {
	if (preorder.length() == 0) return NULL;
	ThreadTreeNode<char>* root = new ThreadTreeNode<char>;
	unsigned int length = preorder.length();
	char c = preorder[0];
	unsigned int mid = inorder.find(c);
	std::string inA = inorder.substr(0, mid);
	std::string inB = inorder.substr(mid + 1, length);
	std::string preA = preorder.substr(1, inA.length());
	std::string preB = preorder.substr(inA.length() + 1, length);
	ThreadTreeNode<char>* LeftChild = CreateThreadTree(preA, inA);
	ThreadTreeNode<char>* RightChild = CreateThreadTree(preB, inB);
	root->SetData(c);
	root->SetLeftChild(LeftChild);
	root->SetRightChild(RightChild);
	return root;
}
template<typename DataType>
void PreOrderVisitWithNoStack(ThreadTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	std::cout << tree->GetData() << " ";
	PreOrderVisitWithNoStack(tree->GetLeftChild());
	PreOrderVisitWithNoStack(tree->GetRightChild());
}
template<typename DataType>
void InOrderVisitWithNoStack(ThreadTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	InOrderVisitWithNoStack(tree->GetLeftChild());
	std::cout << tree->GetData() << " ";
	InOrderVisitWithNoStack(tree->GetRightChild());
}
template<typename DataType>
void PostOrderVisitWithNoStack(ThreadTreeNode<DataType>* tree) {
	if (tree == NULL) return;
	PostOrderVisitWithNoStack(tree->GetLeftChild());
	PostOrderVisitWithNoStack(tree->GetRightChild());
	std::cout << tree->GetData() << " ";
}
template<typename DataType>
unsigned int GetTreeDepthWithNoStack(ThreadTreeNode<DataType>* tree) {
	if (tree == NULL) return 0;
	if (GetTreeDepthWithNoStack(tree->GetLeftChild()) > GetTreeDepthWithNoStack(tree->GetRightChild())) return 1 + GetTreeDepthWithNoStack(tree->GetLeftChild());
	else return 1 + GetTreeDepthWithNoStack(tree->GetRightChild());
}
template<typename DataType>
unsigned int GetTreeLeavesWithNoStack(ThreadTreeNode<DataType>* tree) {
	if (tree == NULL) return 0;
	if (tree->GetLeftChild() == NULL && tree->GetRightChild() == NULL) return 1;
	else  return GetTreeLeavesWithNoStack(tree->GetLeftChild()) + GetTreeLeavesWithNoStack(tree->GetRightChild());
}
#endif // !CREATE_THEAD_TREE_H
