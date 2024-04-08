#include<iostream>
#include<string>
#include"theadtree.h"
int main() {
	std::string preorder = "ABDCFEGHIJKL";
	std::string inorder = "CDFBGEHAJIKL";
	ThreadTreeNode<char>*root = CreateThreadTree(preorder, inorder);
	ThreadTree<char>tree(root);
	std::cout << "PreOrderList:\t";
	PreOrderVisitWithNoStack(root); std::cout << std::endl;
	std::cout << "InOrderList:\t";
	InOrderVisitWithNoStack(root); std::cout << std::endl;
	std::cout << "PostOrderList:\t";
	PostOrderVisitWithNoStack(root); std::cout << std::endl;
	std::cout << "Leaves:\t";
	std::cout<<GetTreeLeavesWithNoStack(root) << std::endl;
	std::cout << "Depth:\t";
	std::cout << GetTreeDepthWithNoStack(root) << std::endl;
	system("pause");
	std::cout << "Using the thread to perform the data:" << std::endl<<std::endl;
	ThreadTree<char>::CreateInThreadTreePreorder(tree);
	std::cout << "PreOrderList:\t";
	tree.Preorder(); std::cout << std::endl;
	tree.ClearTag();
	ThreadTree<char>::CreateInThreadTreeInorder(tree);
	std::cout << "InOrderList:\t";
	tree.Inorder(); std::cout << std::endl;
	tree.ClearTag();
	ThreadTree<char>::CreateInThreadTreePostorder(tree);
	std::cout << "PostOrderList:\t";
	tree.Postorder(); std::cout << std::endl;
	tree.ClearTag();
	tree.ClearTree();
	ThreadTree<char>::DeleteTree(root);
	system("pause");
	return 0;
}
