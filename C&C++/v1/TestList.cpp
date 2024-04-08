#include<iostream>
# include"list.h"
int main() {
	CircleBiList<int> list;
	for (int k = 0; k < 8; k++) {
		list.Push_Back(k); std::cout << "Rear Address:" << list.Rear << " Head Address:" << list.Head <<  std::endl;;
		list.Push_Front(-k); std::cout << "Rear Address:" << list.Rear << " Head Address:" << list.Head <<std::endl;;
		
	}
	
	std::cout << "Length:" << list.GetLength() << std::endl;
	/*
	for (unsigned int k = 0; k < list.GetLength(); k++) {
		std::cout<< list[k] << " ";
		//std::cout << "Address:" << (list[k]->GetNextNode()->GetPreviousNode()) << " Data:" << list[k]->GetData()<< "\n";
	}*/
	std::cout << std::endl;
	while (list.GetLength()>0) {
		std::cout << "Rear Address:"<<list.Rear<< " Head Address:" << list.Head << " Data:"<<list.Front() << "\n";
		list.Pop_Front();
	}
	/*
	std::cout << std::endl;
	std::cout << "Length:" << list.GetLength() << std::endl;
	std::cout <<list.Head <<std::endl;
	std::cout << list.Rear<< std::endl;
	*/
	system("pause");
	return 0;
}