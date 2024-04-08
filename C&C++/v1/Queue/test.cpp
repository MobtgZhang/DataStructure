#include "node.h"
#include "List.h"
#include<iostream>
#include<vector>
#include"circlelist.h"
#include"Sphere.h"
#include "Stack.h"
#include "Queue.h"
using std::cout;
using std::endl;
void testList(LinkedList<int>& mylist) {
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
void testQueue(Queue<int>myqueue) {
	for (int k = 0; k < 10; k++) {
		myqueue.Push(k);
	}
	while (!myqueue.Empty()) {
		cout << myqueue.Pop() << " ";
	}
	cout << endl;
	for (int k = 10; k < 20; k++) {
		myqueue.Push(k);
	}
	while (!myqueue.Empty()) {
		cout << myqueue.Pop() << " ";
	}
	cout << endl;
	for (int k = 20; k < 30; k++) {
		myqueue.Push(k);
	}
	cout << myqueue.Front() << endl;
	cout << myqueue.Rear() << endl;
	myqueue.Clear();
	cout << myqueue.Empty() << endl;
	system("pause");
}
void testDequeue(Dequeue<int>&myqueue) {
	for (int k = 0; k < 10; k++) {
		myqueue.Push_Front(k);
		myqueue.Push_Back(-k);
	}
	while (!myqueue.Empty()) {
		cout << myqueue.Pop_Front() << " ";
	}
	cout << endl;
	for (int k = 10; k < 20; k++) {
		myqueue.Push_Back(k);
		myqueue.Push_Front(-k);
	}
	while (!myqueue.Empty()) {
		cout << myqueue.Pop_Back() << " ";
	}
	cout << endl;
	for (int k = 20; k < 30; k++) {
		myqueue.Push_Back(k);
		myqueue.Push_Front(-k);
	}
	cout << myqueue.Front() << endl;
	cout << myqueue.Rear() << endl;
	myqueue.Clear();
	cout << myqueue.Empty() << endl;

	system("pause");
}
int main() {
	DoubleList<int>mylist1;
	SingleList<int>mylist2;
	CircleList<int>mylist3;
	BiCircleList<int>mylist;
	testList(mylist1);
	testList(mylist2);
	testList(mylist3);
	testList(mylist);
	Dequeue<int>myqueue;
	testDequeue(myqueue);
	return 0;
}