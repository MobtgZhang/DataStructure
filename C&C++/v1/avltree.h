#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#include "BiTree.h"
template<typename DataType>
class AvlTree {
private:
	BiTreeNode<DataType>*root;
private:
	void static LLRoute(AvlTree<DataType>&preNode, AvlTree<DataType>&p) {
		//Swap data
		DataType Data = preNode.GetRootData();
		preNode.SetRootData(p.GetRootData());
		p.SetRootData(Data);
		//route the node
		preNode.GetRoot()->SetLeftChild(p.GetRoot()->GetLeftChild());
		p.GetRoot()->SetLeftChild(p.GetRoot()->GetRightChild());
		p.GetRoot()->SetRightChild(preNode.GetRoot()->GetRightChild());
		preNode.GetRoot()->SetRightChild(p.GetRoot());
	}
	void static LRRoute(AvlTree<DataType>&preNode, AvlTree<DataType>&p) {
		AvlTree<DataType>q(p.GetRoot()->GetRightChild());
		//swap data 
		DataType Data = preNode.GetRootData();
		preNode.SetRootData(q.GetRootData());
		q.SetRootData(Data);
		//route
		p.GetRoot()->SetRightChild(q.GetRoot()->GetLeftChild());
		q.GetRoot()->SetLeftChild(q.GetRoot()->GetRightChild());
		q.GetRoot()->SetRightChild(preNode.GetRoot()->GetRightChild());
		preNode.GetRoot()->SetRightChild(q.GetRoot());
	}
	void static RRRoute(AvlTree<DataType>&preNode, AvlTree<DataType>&p) {
		//Swap the data
		DataType Data = preNode.GetRootData();
		preNode.SetRootData(p.GetRootData());
		p.SetRootData(Data);

		//route the node
		preNode.GetRoot()->SetRightChild(p.GetRoot()->GetRightChild());
		p.GetRoot()->SetRightChild(p.GetRoot()->GetLeftChild());
		p.GetRoot()->SetLeftChild(preNode.GetRoot()->GetLeftChild());
		preNode.GetRoot()->SetLeftChild(p.GetRoot());
	}
	void static RLRoute(AvlTree<DataType>&preNode, AvlTree<DataType>&p) {
		AvlTree<DataType>q(p.GetRoot()->GetLeftChild());
		//Swap the data
		system("pause");
		DataType Data = preNode.GetRootData();
		preNode.SetRootData(p.GetRootData());
		p.SetRootData(Data);
		//route the node
		p.GetRoot()->SetLeftChild(q.GetRoot()->GetRightChild());
		q.GetRoot()->SetRightChild(q.GetRoot()->GetLeftChild());
		q.GetRoot()->SetLeftChild(preNode.GetRoot()->GetLeftChild());
		preNode.GetRoot()->SetLeftChild(p.GetRoot());
	}
private:
	void static Insert(DataType Data,AvlTree<DataType>&root, AvlTree<DataType>&preNode) {
		/*std::cout << Data << std::endl;
		system("pause");*/
		if (Data < root.GetRootData()) {
			//Insert into Left subtree
			AvlTree<DataType>p(root.GetRoot()->GetLeftChild());
			if (p.GetRoot() == NULL) {
				BiTreeNode<DataType>*ptr = new BiTreeNode<DataType>(Data, NULL, NULL);
				root.GetRoot()->SetLeftChild(ptr);
			}
			else {
				Insert(Data,p,preNode);
			}
		}
		else {
			//Insert int right subtree
			AvlTree<DataType>p(root.GetRoot()->GetRightChild());
			if (p.GetRoot() == NULL) {
				BiTreeNode<DataType>*ptr = new BiTreeNode<DataType>(Data, NULL, NULL);
				root.GetRoot()->SetRightChild(ptr);
			}
			else {
				Insert(Data, p, preNode);
			}
		}
		AvlTree<DataType>p(preNode.GetRoot());
		preNode.SetRoot(root.GetRoot());
		int TreeBalance = GetHeight(preNode.GetRoot()->GetLeftChild()) - GetHeight(preNode.GetRoot()->GetRightChild());
		if (TreeBalance == 0 || TreeBalance == -1 || TreeBalance == 1) return;
		else {
			if (TreeBalance > 0) {
				//The Left subtree insert a node
				// LL
				if (preNode.GetRoot()->GetLeftChild() == p.GetRoot())AvlTree::LLRoute(preNode, p);
				//LR
				else AvlTree::LRRoute(preNode, p);
			}
			else{
				//The right subtree insert a node
				// RR
				if (preNode.GetRoot()->GetRightChild() == p.GetRoot()) RRRoute(preNode, p);
				//RL
				else AvlTree::RLRoute(preNode, p);
				preNode.SetRoot(NULL);
			}
		}
	}

	bool static DeleteValue(AvlTree<DataType>&root, AvlTree<DataType>&preNode, DataType Data) {
		if (root == NULL) return false;
		if (Data < root.GetRoot()->GetData()) {
			preNode.SetRoot(root.GetRoot());
			if (root.GetRoot()->GetLeftChild() != NULL) return DeleteValue(root.GetRoot()->GetLeftChild(), preNode, Data);
			else return false;
		}
		else if (Data > root.GetRoot()->GetData()) {
			preNode.SetRoot(root.GetRoot());
			if (root.GetRoot()->GetRightChild() != NULL) return DeleteValue(root.GetRoot()->GetRightChild(), preNode, Data);
			else return false;
		}
		else if (Data == root.GetRoot()->GetData()) {
			AvlTree::Delete(root.GetRoot(), preNode);
			return true;
		}
		else return false;
	}
	void Delete(AvlTree<DataType>&root, AvlTree<DataType>&preNode) {
		if (root.GetRoot()->GetLeftChild() == NULL && root.GetRoot()->GetRightChild() == NULL) {
			if (root.GetRoot() == preNode.GetRoot()->GetRightChild()) preNode.GetRoot()->SetRightChild(NULL); 
			else preNode.GetRoot()->SetLeftChild(NULL);
			DataType Data = root.GetRoot()->GetData();
			delete root.GetRoot();
			ptr = NULL;
			return Data;
		}
		else if (root.GetRoot()->GetRightChild() == NULL || root.GetRoot()->GetLeftChild() == NULL) {
			BiTreeNode<DataType>* Temp = root.GetRoot()->GetRightChild() == NULL ? root.GetRoot()->GetLeftChild() : root.GetRoot()->GetRightChild();
			DataType Data = root.GetRoot()->GetData();
			root.GetRoot()->SetData(Temp->GetData());
			root.GetRoot()->SetLeftChild(Temp->GetLeftChild());
			root.GetRoot()->SetRightChild(Temp->GetRightChild());
			delete Temp;
			return Data;
		}
		else {
			BiTreeNode<DataType>* p = root.GetRoot();
			while (p->GetLeftChild() != NULL) p = p->GetLeftChild();
			preNode.SetRoot(root.GetRoot());
			DataType Datap = AvlTree::Delete(p, preNode);
			DataType Dataptr = root.GetRoot()->GetData();
			root.GetRoot()->SetData(Datap);
			return Dataptr;
		}
		// To Check the tree
		AvlTree<DataType>p(preNode.GetRoot());
		preNode.SetRoot(root.GetRoot());
		int TreeBalance = GetHeight(preNode.GetRoot()->GetLeftChild()) - GetHeight(preNode.GetRoot()->GetRightChild());
		if (TreeBalance == 0 || TreeBalance == -1 || TreeBalance == 1) return;
		else {
			if (TreeBalance > 0) {
				//The Left subtree insert a node
				// LL
				if (preNode.GetRoot()->GetLeftChild() == p.GetRoot())AvlTree::LLRoute(preNode, p);
				//LR
				else AvlTree::LRRoute(preNode, p);
			}
			else {
				//The right subtree insert a node
				// RR
				if (preNode.GetRoot()->GetRightChild() == p.GetRoot()) RRRoute(preNode, p);
				//RL
				else AvlTree::RLRoute(preNode, p);
				preNode.SetRoot(NULL);
			}
		}
	}
	static unsigned int GetHeight(BiTreeNode<DataType>*root) {
		if (root == NULL) return 0;
		if (GetHeight(root->GetLeftChild()) > GetHeight(root->GetRightChild())) return 1 + GetHeight(root->GetLeftChild());
		else return 1 + GetHeight(root->GetRightChild());
	}
public:
	AvlTree() {
		this->root = NULL;
	}
	AvlTree(BiTreeNode<DataType>*root) {
		this->root = root;
	}
	void SetRoot(BiTreeNode<DataType>*root) {
		this->root = root;
	}
	void AddNode(DataType Data) {
		if (this->root == NULL) this->root = new BiTreeNode<DataType>(Data, NULL, NULL);
		else {
			AvlTree<DataType>PreNode;
			AvlTree<DataType>Tree(this->root);
			AvlTree::Insert(Data, Tree, PreNode);
			this->root = Tree.GetRoot();
		}
	}
	void DeleteNode(DataType Data) {
		if (this->root == NULL) return false;
		else {
			AvlTree<DataType>root(this->root);
			AvlTree<DataType>preNode;
			return AvlTree::DeleteValue(root,preNode, Data);
		}
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
	DataType GetRootData() {
		assert(this->root != NULL);
		return this->root->GetData();
	}
	void SetRootData(DataType Data) {
		assert(this->root != NULL);
		this->root->SetData(Data);
	}
	unsigned int GetHeight() { return AvlTree<DataType>::GetHeight(this->root); }
	BiTreeNode<DataType>*GetRoot() { return this->root; }
	~AvlTree() {

	}
};
#endif // !AVLTREE_H
