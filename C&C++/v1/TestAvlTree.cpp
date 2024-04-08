#include<iostream>
#include"avltree.h"
int main() {
	//int NumList[] = { 5,4,7,8,9,3,1,2,6,0,10,12,11,15,14,13 }; int Num = 16;
	//int NumList[] = { 34,107,23,15,98,115,28 }; int Num = 7;
	int NumList[] = { 25,18,51,42,34,9,14,38,27 }; int Num = 9;
	AvlTree<int> Tree;
	for (int k = 0; k < Num; k++) {
		Tree.AddNode(NumList[k]);
		/*std::cout << "List: " << std::endl;
		Tree.LevelTraversal(); std::cout << std::endl;
		system("pause");*/
		//std::cout << NumList[k] << " ";
	}
	std::cout << std::endl;
	BiTreeNode<int>* ptr = Tree.GetRoot();
	//std::cout << ptr->GetRightChild()->GetData() << std::endl;
	std::cout << "Level Traversal:" << std::endl;
	Tree.LevelTraversal();
	std::cout << std::endl;
	/*Tree.DeleteNode(7);
	std::cout << "Level Traversal:" << std::endl;
	Tree.LevelTraversal();
	std::cout << std::endl;
	std::cout << "Height:" << Tree.GetSortedTreeHeight() << std::endl;
	std::cout << std::endl;*/
	system("pause");
	return 0;
}