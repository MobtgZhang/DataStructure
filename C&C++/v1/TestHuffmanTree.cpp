#include<iostream>
#include"HuffmanTree.h"
int main() {
	int WeightNum[] = {45,12,13,5,9,16};
	unsigned int Num = 6;
	for (unsigned int k = 0; k < Num; k++) std::cout << WeightNum[k] << " ";
	std::cout << std::endl;
	sortArray(WeightNum, Num);
	for (unsigned int k = 0; k < Num; k++) {
		std::cout << WeightNum[k] << " ";
	}
	std::cout << std::endl;
	HuffmanTree<int> Tree;
	CreateHuffmanTree(WeightNum, Num, Tree);
	std::cout << "Preorder Traversal:" << std::endl;
	Tree.PreOrderTraversal();
	std::cout << std::endl;
	std::cout << "Inorder Traversal:" << std::endl;
	Tree.InOrderTraversal();
	std::cout << std::endl;
	std::cout << "Postorder Traversal:" << std::endl;
	Tree.PostOrderTraversal();
	std::cout << std::endl;
	std::cout << "Level Traversal:" << std::endl;
	Tree.LevelTraversal();
	std::cout << std::endl;
	int Weights = Tree.CalculateWeight();
	std::cout << "WSL: " << Weights << std::endl;
	system("pause");
	return 0;
}