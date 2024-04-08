#pragma once
#include "stack.h"
#include "node.h"
#include "list.h"
#include "queue.h"
/*unsigned int abs(int data) {
	if (data > 0) return data;
	else return -data;
}*/
int max(int a, int b) {
	return a > b ? a : b;
}
template<typename DataType>
class BiTree {
protected:
	BiTreeNode<DataType>* root;
	unsigned int depth;
	unsigned int size;
	static void DeleteTreeNodes(BiTreeNode<DataType>* root) {
		if (root == NULL) return;
		if (root->GetLeftChild() == NULL && root->GetRightChild() == NULL) {
			delete root;
		}
		else {
			DeleteTreeNodes(root->GetLeftChild());
			DeleteTreeNodes(root->GetRightChild());
		}
	}
	static void PreOrder(BiTreeNode<DataType>* tree, LinkedList<BiTreeNode<DataType>*>list) {
		if (tree == NULL) return;
		list.Push_Back(tree);
		BiTree::PreOrder(tree->GetLeftChild(), list);
		BiTree::PreOrder(tree->GetRightChild(), list);
	}
	static void InOrder(BiTreeNode<DataType>* tree, LinkedList<BiTreeNode<DataType>*>list) {
		if (tree == NULL) return;
		BiTree::InOrder(tree->GetLeftChild(), list);
		list.Push_Back(tree);
		BiTree::InOrder(tree->GetRightChild(), list);
	}
	static void PostOrder(BiTreeNode<DataType>* tree, LinkedList<BiTreeNode<DataType>*>list) {
		if (tree == NULL) return;
		BiTree::PostOrder(tree->GetLeftChild(), list);
		BiTree::PostOrder(tree->GetRightChild(), list);
		list.Push_Back(tree);
	}
	static unsigned int GetTreeDepth(BiTreeNode<DataType>* tree) {
		if (tree == NULL) return 0;
		unsigned int left = BiTree::GetTreeDepth(tree->GetLeftChild());
		unsigned int right = BiTree::GetTreeDepth(tree->GetRightChild());
		if (left > right) return 1 + left;
		else return 1 + right;
	}
	static unsigned int GetTreeLeaves(BiTreeNode<DataType>* tree) {
		if (tree->GetLeftChild() == NULL && tree->GetRightChild() == NULL) return 1;
		else return BiTree::GetTreeLeaves(tree->GetLeftChild()) + BiTree::GetTreeLeaves(tree->GetRightChild());
	}
	static BiTreeNode<DataType>* GetAncestor(BiTreeNode<DataType>*root, BiTreeNode<DataType>*p, BiTreeNode<DataType>*q) {
		if (root == p || root == q || root != NULL)return root;
		BiTreeNode<DataType>* left = GetAncestor(root->GetLeftChild(),p,q);
		BiTreeNode<DataType>* right = GetAncestor(root->GetRightChild(), p, q);
		if (left == NULL && right == NULL) return NULL;
		else if (left != NULL && right == NULL)return left;
		else if (left == NULL && right != NULL)return right;
		return root;
	}
	static unsigned int TreeSize(BiTreeNode<DataType>* tree) {
		if (tree == NULL)return 0;
		return BiTree::TreeSize(tree->GetLeftChild()) + BiTree::TreeSize(tree->GetRightChild()) + 1;
	}
public:
	BiTree() {
		this->root = NULL;
		this->depth = 0;
		this->size = 0;
	}
	BiTree(BiTreeNode<DataType>* root) {
		this->root = root;
		this->depth = BiTree::GetTreeDepth(root);
		this->size = BiTree::GetSize(root);
	}
	bool IsEmpty() {
		return this->root == NULL;
	}
	void PreOrderVisit(LinkedList<BiTreeNode<DataType>*>&list) {
		BiTreeNode<DataType>* ptr = this->root;
		list.Clear();
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr!=NULL) {
				stack.Push(ptr);
				list.Push_Back(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Pop();
			ptr = ptr->GetRightChild();
		}
	}
	void InOrderVisit(LinkedList<BiTreeNode<DataType>*>& list) {
		BiTreeNode<DataType>* ptr = this->root;
		list.Clear();
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				stack.Push(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Pop();
			list.Push_Back(ptr);
			ptr = ptr->GetRightChild();
		}
	}
	void PostOrderVisit(LinkedList<BiTreeNode<DataType>*>& list) {
		BiTreeNode<DataType>* ptr = this->root;
		BiTreeNode<DataType>* pre = NULL;
		list.Clear();
		Stack<BiTreeNode<DataType>*> stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				stack.Push(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Top();
			if (ptr->GetRightChild() == NULL || ptr->GetRightChild() == pre) {
				list.Push_Back(ptr);
				pre = ptr;
				ptr = NULL;
				stack.Pop();
			}
			else ptr = ptr->GetRightChild();
		}
	}
	void LevelVisit(LinkedList<BiTreeNode<DataType>*>&list) {
		BiTreeNode<DataType>* ptr;
		Queue<BiTreeNode<DataType>*> queue;
		list.Clear();
		queue.EnQueue(this->root);
		while (!queue.IsEmpty()) {
			ptr = queue.DeQueue();
			list.Push_Back(ptr);
			if (ptr->GetLeftChild() != NULL) queue.EnQueue(ptr->GetLeftChild());
			if (ptr->GetRightChild() != NULL)queue.EnQueue(ptr->GetRightChild());
		}
	}
	BiTreeNode<DataType>* GetParent(BiTreeNode<DataType>* node){
		if (node == this->root) return NULL;
		//Using the inorder traversal to find its parent node
		BiTreeNode<DataType>* ptr = this->root;
		Stack<BiTreeNode<DataType>*>stack;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				if (ptr->GetLeftChild() == node)return ptr;
				else {
					ptr = ptr->GetLeftChild();
					stack.Push(ptr);
				}
			}
			ptr = stack.Pop();
			if (ptr->GetRightChild() == node) return ptr;
			else ptr = ptr->GetRightChild();
		}
	}
	BiTreeNode<DataType>* LowestCommonAncestor(BiTreeNode<DataType>*p, BiTreeNode<DataType>*q) {
		return BiTree::GetAncestor(this->root, p, q);
	}
	LinkedList<BiTreeNode<DataType>*> PreOrderVisitWithNoStack() {
		LinkedList<BiTreeNode<DataType>*>list;
		this->PreOrder(this->root, list);
		return list;
	}
	LinkedList<BiTreeNode<DataType>*> InOrderVisitWithNoStack() {
		LinkedList<BiTreeNode<DataType>*>list;
		this->InOrder(this->root, list);
		return list;
	}
	LinkedList<BiTreeNode<DataType>*> PostOrderVisitWithNoStack() {
		LinkedList<BiTreeNode<DataType>*>list;
		this->PostOrder(this->root, list);
		return list;
	}
	unsigned int GetDepth() {
		return BiTree::GetTreeDepth(this->root);
	}
	unsigned int GetSize() {
		return BiTree::TreeSize(this->root);
	}
	unsigned int GetLeaves() {
		return BiTree::GetTreeLeaves(this->root);
	}
	~BiTree() {
		DeleteTreeNodes(this->root);
	}
};
template<typename DataType>
class HaffmanTree :public BiTree<DataType> {
protected:
	static void sort(LinkedList<BiTreeNode<DataType>*>&list) {
		for (unsigned int k = 0; k < list.GetLength(); k++) {
			for (unsigned int j = 0; j < list.GetLength() - k - 1; j++) {
				if (list[j + 1]->GetData() < list[j]->GetData()) {
					Node<BiTreeNode<DataType>*>* ptr = list.GetNode(j);
					BiTreeNode<DataType>* TmpData = ptr->GetData();
					ptr->SetData(ptr->GetNode()->GetData());
					ptr->GetNode()->SetData(TmpData);
				}
			}
		}
	}
	static DataType getweight(BiTreeNode<DataType>*root,unsigned int length) {
		if (root == NULL)return 0;
		if (root->GetLeftChild() == NULL && root->GetRightChild() == NULL) {
			return root->GetData() * length;
		}
		else {
			return HaffmanTree::getweight(root->GetLeftChild(),length+1)+ getweight(root->GetRightChild(), length + 1);
		}
	}
public:
	HaffmanTree() {
		BiTree<DataType>();
	}
	void CreateTree(DataType list[],unsigned int indexes) {
		LinkedList<BiTreeNode<DataType>*>TmpList;
		for (unsigned int k = 0; k < indexes; k++) {
			BiTreeNode<DataType>* ptr = new BiTreeNode<DataType>(list[k], NULL, NULL);
			TmpList.Push_Back(ptr);
		}
		while (TmpList.GetLength()>1) {
			/*
			* 1.sort the number
			*/
			HaffmanTree::sort(TmpList);
			/*
			*2.add node
			*/
			BiTreeNode<DataType>* newnode = new BiTreeNode<int>(TmpList[0]->GetData() + TmpList[1]->GetData(), NULL, NULL);
			newnode->SetLeftChild(TmpList[0]);
			newnode->SetRightChild(TmpList[1]);
			/*
			*3.remove node
			*/
			TmpList.Delete(0);
			TmpList.Set(0, newnode);
		}
		this->root = TmpList[0];
		this->depth = BiTree<DataType>::GetTreeDepth(this->root);
		this->size = BiTree<DataType>::TreeSize(this->root);
	}
	DataType GetWeights() {
		return HaffmanTree::getweight(this->root, 0);
	}
	~HaffmanTree() {
		
	}
};
class CharNodeTree :public BiTree<char> {
protected:
	static BiTreeNode<char>* CreateBiTree(std::string preorder,std::string inorder) {
		if (preorder.length() == 0)return NULL;
		unsigned int length = preorder.length();
		char c = preorder[0];
		unsigned int mid = inorder.find(c);
		std::string inA = inorder.substr(0, mid);
		std::string inB = inorder.substr(mid + 1, length);
		std::string preA = preorder.substr(1, inA.length());
		std::string preB = preorder.substr(inA.length() + 1, length);
		BiTreeNode<char>* left = CharNodeTree::CreateBiTree(preA, inA);
		BiTreeNode<char>* right = CharNodeTree::CreateBiTree(preB, inB);
		BiTreeNode<char>* root = new BiTreeNode<char>(c, left,right);
		return root;
	}
public:
	CharNodeTree(std::string preorder,std::string inorder) {
		this->root = CharNodeTree::CreateBiTree(preorder,inorder);
	}
	~CharNodeTree() {}
};
template<typename DataType>
class AVLTree :public BiTree<DataType> {
protected:
	//get the height of the node
	static int get_height(BiTreeNode<DataType>* node) {
		if (node == NULL)return -1;
		return max(AVLTree::get_height(node->GetLeftChild()),AVLTree::get_height(node->GetRightChild()))+1
	}
	// LL
	static BiTreeNode<DataType>* left_rotation(BiTreeNode<DataType>* x) {
		BiTreeNode<DataType>* y = x->GetRightChild();
		x->SetRightChild(y->GetLeftChild());
		y->SetLeftChild(x);
		return y;
	}
	// RR
	static BiTreeNode<DataType>* right_rotation(BiTreeNode<DataType>* x) {
		BiTreeNode<DataType>* y = x->GetLeftChild();
		x->SetLeftChild(y->GetRightChild());
		y->SetRightChild(x);
		return y;
	}
	// get balance factor
	static int get_balance(BiTreeNode<DataType>* node) {
		if (node == NULL)return 0;
		int hleft = AVLTree::get_height(node->GetLeftChild());
		int hright = AVLTree::get_height(node->GetRightChild());
		return hleft - hright;
	}
	static BiTreeNode<DataType>* insert(BiTreeNode<DataType>* node, DataType& value) {
		if (node == NULL) node = new BiTreeNode<DataType>(value, NULL, NULL);
		else if (value < node->GetData()) node->SetLeftChild(AVLTree::insert(node->GetLeftChild(), value);
		else if (value > node->GetData()) node->SetRightChild(AVLTree::insert(node->GetRightChild()), value);
		else return node;
		int balance = AVLTree::get_balance(node);
		// RR
		if (balance > 1 && value < node->GetLeftChild()->GetData()) return AVLTree::right_rotation(node);
		// LR
		if (balance > 1 && value > node->GetLeftChild()->GetData()) {
			node->SetLeftChild(AVLTree::left_rotation(node->GetLeftChild()));
			return AVLTree::right_rotation(node->GetRightChild());
		}
		// LL
		if (balance<-1 && value>node->GetRightChild()->GetData())return AVLTree::left_rotation(node);
		// RL
		if (balance < -1 && value < node->GetRightChild()->GetData()) {
			node->SetRightChild(AVLTree::right_rotation(node->GetRightChild()));
			return AVLTree::left_rotation(node->GetLeftChild());
		}
		return node;
	}
	static BiTreeNode<DataType>* successor(BiTreeNode<DataType>* node) {
		while (node->GetLeftChild() != NULL)node = node->GetLeftChild();
		return node;
	}
	static BiTreeNode<DataType>* delete_node(BiTreeNode<DataType>*node,DataType& value) {
		if (node == NULL)return node;
		else if (value < node->GetData())node->SetLeftChild(AVLTree::delete_node(node->GetLeftChild(), value));
		else if (value > node->GetData())node->SetRightChild(AVLTree::delete_node(node->GetRightChild(), value);
		else {
			BiTreeNode<DataType>* TmpNode = NULL;
			if (node->GetLeftChild() != NULL && node->GetRightChild() != NULL) {
				TmpNode = AVLTree::successor(node->GetRightChild());
				node->SetRightChild(AVLTree::delete_node(node->GetRightChild(), TmpNode->GetData()));
				node->SetData(TmpNode->GetData());
			}
			else if (node->GetLeftChild() == NULL) {
				TmpNode = node;
				node = node->GetRightChild();
				delete TmpNode;
			}
			else if (node->GetRightChild() == NULL) {
				TmpNode = node;
				node = node->GetLeftChild();
				delete TmpNode;
			}
			else delete node;
		}
		if (node == NULL)return node;
		int balance = AVLTree::get_balance(node);
		if (balance > 1) {
			if(AVLTree::get_balance(node->GetLeftChild()) >= 0)
				return AVLTree::right_rotation(node);
			else {
				node->SetLeftChild(AVLTree::left_rotation(node->GetLeftChild()));
				return AVLTree::right_rotation(node);
			}
		}
		if (balance < -1) {
			if (AVLTree::get_balance(node->GetRightChild()) <= 0)
				return AVLTree::left_rotation(node);
			else {
				node->SetRightChild(AVLTree::right_rotation(node->GetRightChild()));
				return AVLTree::left_rotation(node);
			}
		}
		return node;
	}
public:
	AVLTree() {
		this->root = NULL;
		this->depth = 0;
	}
	void insert(DataType& value) {
		this->root = AVLTree::insert(this->root, value);
	}
	void avl_delete(DataType& value) {
		this->root = AVLTree::delete_node(this->root, value);
	}
	~AVLTree() {

	}
};
