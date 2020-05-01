# include "stack.h"
#include "queue.h"
int main() {
	
	Stack<int> MySt;
	for (int i = 0; i < 8; i++) {
		MySt.Push(i);
	}
	std::cout << MySt.Top() << std::endl;
	while (!MySt.IsEmpty()){
		std::cout <<"Data:"<< MySt.Pop() << std::endl;
		std::cout <<"Length:"<< MySt.GetLength() << std::endl;
	}
	/*
	Queue<int>MyQu;
	for (int i = 0; i < 8; i++) {
		MyQu.EnQueue(i);
	}
	std::cout << MyQu.GetLength()<< std::endl;
	system("pause");
	while (!MyQu.IsEmpty()) {
		std::cout << "Data:" << MyQu.DeQueue() << std::endl;
		std::cout << "Length:" << MyQu.GetLength() << std::endl;
	}
	*/
	system("pause");
	return 0;
}