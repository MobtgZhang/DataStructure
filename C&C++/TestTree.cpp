#include"BiTree.h"
#include <string>
# include <iostream>
using std::string;

int main() {
	string preorder = "ABDCFEGHIJKL";
	string inorder = "CDFBGEHAJIKL";
	BiTreeNode<char>* root = CreateBiTree(preorder, inorder);
	BiTree<char> Tree(root);
	std::cout << "preoder traversal:\t";
	Tree.PreOrderVisit(); std::cout << std::endl;
	std::cout << "inorder traversal:\t";
	Tree.InOrderVisit(); std::cout << std::endl;
	std::cout << "postorder traversal:\t";
	Tree.PostOrderVisit(); std::cout << std::endl;
	std::cout << "level traversal:\t";
	Tree.LevelVisit(); std::cout << std::endl;
	std::cout << "tree height:\t" << GetTreeDepthWithNoStack(root) << std::endl;
	std::cout << "tree Leaves:\t" << GetTreeLeavesWithNoStack(root) << std::endl;
	/*
	std::cout << "PreOrderList:\t";
	PreOrderVisitWithNoStack(tree); std::cout<<std::endl;
	std::cout << "InOrderList:\t";
	InOrderVisitWithNoStack(tree); std::cout << std::endl;
	std::cout << "PostOrderList:\t";
	PostOrderVisitWithNoStack(tree); std::cout << std::endl;
	/*
	system("pause");
	unsigned int length = preorder.length();
	char c = preorder[0];
	std::cout << c << std::endl;
	unsigned int mid = inorder.find(c);
	string inA = inorder.substr(0, mid);
	string inB = inorder.substr(mid + 1, length);
	std::cout << inA << std::endl;
	std::cout << inB << std::endl;
	system("pause");
	string preA = preorder.substr(1, inA.length());
	string preB = preorder.substr(inA.length() + 1, length);
	std::cout << preA << std::endl;
	std::cout << preB << std::endl;
	*/
	system("pause");
	return 0;
}
