#include "node.h"
#include "List.h"
#include<iostream>
#include<vector>
#include"circlelist.h"
using std::cout;
using std::endl;
void test(LinkedList<int>& mylist) {
	int N = 10;
	for (int k = 0; k < N; k++) {
		mylist.Push_Back(k);
	}
	for (int k = 0; k < N; k++) {
		mylist.Push_Front(k);
	}

	mylist.print();
	mylist.Pop_Back();
	mylist.print();
	mylist.Pop_Front();
	mylist.print();

	mylist.Insert(0, 88888);
	mylist.print();

	mylist.Insert(3, 77777);
	mylist.print();

	mylist.Insert(mylist.GetLength() - 1, 9999);
	mylist.print();

	mylist.Delete(0);
	mylist.print();
	mylist.Delete(mylist.GetLength() - 1);
	mylist.print();
	mylist.Delete(2);
	mylist.print();
	cout << "front:" << mylist.Front() << endl;
	cout << "back:" << mylist.Back() << endl;
	system("pause");
}
int main() {
	DoubleList<int>mylist1;
	SingleList<int>mylist2;
	CircleList<int>mylist3;
	BiCircleList<int>mylist;
	test(mylist1);
	test(mylist2);
	test(mylist3);
	test(mylist);
	return 0;
}