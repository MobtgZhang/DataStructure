#pragma once
#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include"BiTree.h"
#include"list.h"
#include"stack.h"
#include"queue.h"
template<typename DataType>
class HuffmanTree {
private:
	BiTreeNode<DataType>* root;
	void static DeleteTree(BiTreeNode<DataType> * tree) {
		if (tree != NULL) {
			if (tree->GetLeftChild() == NULL && tree->GetRightChild() == NULL) {
				delete tree;
			}
			else {
				HuffmanTree<DataType>::DeleteTree(tree->GetLeftChild());
				HuffmanTree<DataType>::DeleteTree(tree->GetRightChild());
			}
		}
	}
public:
	HuffmanTree() {
		this->root = NULL;
	}
	HuffmanTree(DataType Data) {
		this->root = new BiTreeNode<DataType>(Data,NULL,NULL);
	}
	BiTreeNode<DataType>*GetRoot() { return this->root; }
	void SetRoot(BiTreeNode<DataType>*root) {
		this->root = root;
	}
	void PreOrderTraversal() {
		BiTreeNode<DataType>*p = this->root;
		Stack<BiTreeNode<DataType>*>stack;
		while (p != NULL || !stack.IsEmpty()) {
			while (p != NULL) {
				stack.Push(p);
				std::cout << p->GetData() << " ";
				p = p->GetLeftChild();
			}
			p = stack.Pop();
			p = p->GetRightChild();
		}
	}
	void InOrderTraversal() {
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
	void PostOrderTraversal() {
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
	DataType CalculateWeight() {
		//The postorder to calculate the weights
		BiTreeNode<DataType>* ptr = this->root;
		BiTreeNode<DataType>* pre = NULL;
		Stack<BiTreeNode<DataType>*> stack;
		DataType Weight = 0;
		while (ptr != NULL || !stack.IsEmpty()) {
			while (ptr != NULL) {
				stack.Push(ptr);
				ptr = ptr->GetLeftChild();
			}
			ptr = stack.Top();
			if (ptr->GetRightChild() == NULL || ptr->GetRightChild() == pre) {
				if (ptr->GetRightChild() == NULL) {
					unsigned int Depth = stack.GetLength();
					Weight = Weight + (Depth - 1) * ptr->GetData();
				}
				pre = ptr;
				ptr = NULL;
				stack.Pop();
			}
			else ptr = ptr->GetRightChild();
		}
		return Weight;
	}
	~HuffmanTree() {
		HuffmanTree<DataType>::DeleteTree(this->root);
	}
};
#endif // !HUFFMAN_TREE_H
#ifndef HUFFMAN_TREE_FUNCTIONS_H
#define HUFFMAN_TREE_FUNCTIONS_H
// The sort functions
template<typename DataType>
void sortArray(DataType WeightNum[],unsigned int Num) {
	// Using the Bubble Sort
	for (unsigned int k = 0; k < Num; k++) {
		for (unsigned int j = Num - 1; j >k; j--) {
			if (WeightNum[j - 1] > WeightNum[j]) {
				DataType Temp = WeightNum[j - 1];
				WeightNum[j - 1] = WeightNum[j];
				WeightNum[j] = Temp;
			}
		}
	}
}
template<typename DataType>
void AddHuffmanTree(ListHead<HuffmanTree<DataType>*>&forestList,HuffmanTree<DataType>*ptr) {
	unsigned int k = 1;
	while(k < forestList.GetLength()) {
		HuffmanTree<DataType>*p = forestList[k];
		if (p->GetRoot()->GetData() < ptr->GetRoot()->GetData())k++;
		else {
			forestList.Insert(k - 1, ptr);
			break;
		}
	}
	if(k == forestList.GetLength())forestList.Insert(k - 1, ptr);
	else if(forestList.GetLength() == 0)forestList.Push_Back(ptr);
	else return;
}
template<typename DataType>
void PrintHuffmanTree(ListHead<HuffmanTree<DataType>*>&forestList) {
	for (unsigned int k = 0; k < forestList.GetLength(); k++) {
		HuffmanTree<DataType>* p = forestList[k];
		std::cout << p->GetRoot()->GetData() << " ";
	}
	std::cout << std::endl;
}
template<typename DataType>
void CreateHuffmanTree(DataType WeightNum[],unsigned int Num, HuffmanTree<DataType>& Tree) {
	//The input array has been sorted,from smaller one to big one.
	//Make a forest,using a list with a head.
	ListHead<HuffmanTree<DataType>*> forestList;
	//Initialize
	for (unsigned int k = 0; k < Num; k++) {
		HuffmanTree<DataType>* p = new HuffmanTree<DataType>(WeightNum[k]);
		forestList.Push_Back(p);
	}
	while (forestList.GetLength() > 1) {
		HuffmanTree<DataType>* p1 = forestList[0];
		HuffmanTree<DataType>* p2 = forestList[1];
		DataType Data = p1->GetRoot()->GetData() + p2->GetRoot()->GetData();
		HuffmanTree<DataType>* p = new HuffmanTree<DataType>(Data);
		p->GetRoot()->SetLeftChild(p1->GetRoot());
		p->GetRoot()->SetRightChild(p2->GetRoot());
		forestList.Pop_Front(); forestList.Pop_Front();
		AddHuffmanTree(forestList,p);
		/*std::cout << "PrintHuffmanTree:" << std::endl;
		PrintHuffmanTree(forestList);
		std::cout << "Length: " << forestList.GetLength() << std::endl;
		system("pause");*/
	}
	BiTreeNode<DataType>*p = forestList[0]->GetRoot();
	forestList.Clear();
	Tree.SetRoot(p);
}
#endif // !HUFFMAN_TREE_FUNCTIONS_H