#pragma once
#ifndef ABSTRACT_MATRIX
#define ABSTRACT_MATRIX
template<typename DataType>
class AbstractMatrix {
protected:
	//表示第一个元素的位置
	FourNode<DataType>*Head;
	//表示矩阵的大小
	unsigned int RowLength;
	unsigned int ColumnLength;
public:
	//获取行和列的大小
	unsigned int GetRow() { return this->RowLength; }
	unsigned int GetColumn() { return this->ColumnLength; }
	//获取头结点指针
	FourNode<DataType>*GetHead() { return this->Head; }
	// 将矩阵中的元素变为字符串
	virtual std::string toString()=0;
	//设置矩阵中的元素值
	virtual void SetValue(DataType Data, unsigned int row, unsigned int column)=0;
	//获取矩阵中的元素的值
	virtual DataType GetValue(unsigned int row, unsigned int column)=0;
};
#endif // !ABSTRACT_MATRIX

#ifndef MATRIX_H
#define MATRIX_H
#include"node.h"
#include<string>
#include<sstream>
template<typename DataType>
class Matrix :public AbstractMatrix<DataType> {
public:
	//构造函数
	Matrix(unsigned int RowLength, unsigned int ColumnLength);
	// 将矩阵中的元素变为字符串
	std::string toString();
	//设置矩阵中的元素值
	void SetValue(DataType Data, unsigned int row, unsigned int column);
	//获取矩阵中的元素的值
	DataType GetValue(unsigned int row, unsigned int column);
	//析构函数
	~Matrix();
};
//矩阵中函数的实现方法
//构造函数
template<typename DataType>
Matrix<DataType>::Matrix(unsigned int RowLength, unsigned int ColumnLength) {
	//矩阵以零矩阵初始化
	//定义矩阵的行和列的大小
	this->RowLength = RowLength;
	this->ColumnLength = ColumnLength;
	//创建每一列
	this->Head = new FourNode<DataType>(0, NULL, NULL, NULL, NULL);
	FourNode<DataType>*columnptr = this->Head;
	unsigned int index = 1;
	while (index < ColumnLength) {
		columnptr->SetRight(new FourNode<DataType>(0, columnptr, NULL, NULL, NULL));
		columnptr = columnptr->GetRight();
		index++;
	}
	//创建每一列
	columnptr = this->Head;
	//用于标记创建每一列元素左边一列的元素
	FourNode<DataType>*leftptr = NULL;
	while (columnptr != NULL) {
		FourNode<DataType>*rowptr = columnptr;
		index = 1;
		while (index < RowLength) {
			if (leftptr == NULL) rowptr->SetDown(new FourNode<DataType>(0, leftptr, NULL, columnptr, NULL));
			else {
				leftptr = leftptr->GetDown();
				rowptr->SetDown(new FourNode<DataType>(0, leftptr, NULL, columnptr, NULL));
				leftptr->SetRight(rowptr->GetDown());

			}
			rowptr = rowptr->GetDown();
			index++;
		}
		leftptr = columnptr;
		columnptr = columnptr->GetRight();
	}
}
//析构函数
template<typename DataType>
Matrix<DataType>::~Matrix() {
	FourNode<DataType>*rowptr = this->Head;
	//搜索行
	//记录上一个行指针
	FourNode<DataType>*prerowptr = NULL;
	while (rowptr != NULL) {
		prerowptr = rowptr;
		//记录上一个列指针，注意：第一行先不能删除
		FourNode<DataType>*columnptr = rowptr->GetDown();
		FourNode<DataType>*precolumnptr = NULL;
		while (columnptr != NULL) {
			precolumnptr = columnptr;
			columnptr = columnptr->GetDown();
			delete precolumnptr;
		}
		rowptr = rowptr->GetRight();
		delete prerowptr;
	}
}
//将矩阵中的元素转化为字符串
template<typename DataType>
std::string Matrix<DataType>::toString() {
	std::stringstream s_stream;
	std::string str_size;
	s_stream << "Size:[" << this->RowLength << "," << this->ColumnLength << "]";
	s_stream >> str_size;
	str_size = str_size + "\n";
	//注意用完s_stream要清除字符流
	s_stream.clear();
	std::string str_mat = "";
	FourNode<DataType>*rowptr = this->Head;
	//寻找行

	while (rowptr != NULL) {
		FourNode<DataType>*columnptr = rowptr;
		while (columnptr != NULL) {
			s_stream << columnptr->GetData();
			std::string line;
			s_stream >> line;
			str_mat = str_mat + line + "\t";
			columnptr = columnptr->GetRight();
			s_stream.clear();
		}
		str_mat = str_mat + "\n";
		rowptr = rowptr->GetDown();
	}

	return str_mat + str_size;
}
//获取矩阵中的元素的值
template<typename DataType>
DataType Matrix<DataType>::GetValue(unsigned int row, unsigned int column) {
	FourNode<DataType>*rowptr = this->Head;
	//寻找行
	unsigned int index = 0;
	while (index < row) {
		rowptr = rowptr->GetRight();
		index++;
	}
	FourNode<DataType>*columnptr = rowptr;
	//寻找列
	index = 0;
	while (index < column) {
		columnptr = columnptr->GetDown();
		index++;
	}
	return columnptr->GetData();
}
//设置矩阵中的元素值
template<typename DataType>
void Matrix<DataType>::SetValue(DataType Data, unsigned int row, unsigned int column) {
	FourNode<DataType>*rowptr = this->Head;
	//寻找行
	unsigned int index = 0;
	while (index < row) {
		rowptr = rowptr->GetRight();
		index++;
	}
	FourNode<DataType>*columnptr = rowptr;
	//寻找列
	index = 0;
	while (index < column) {
		columnptr = columnptr->GetDown();
		index++;
	}
	columnptr->SetData(Data);
}
#endif // !MATRIX_H
#ifndef CIRCLESPHERE_H
#define CIRCLESPHERE_H
//定义一个标准多重循环表
template<typename DataType>
class SphereTable :AbstractMatrix<DataType> {
public:
	SphereTable(unsigned int RowLength, unsigned int ColumnLength);
	~SphereTable();
	// 将矩阵中的元素变为字符串
	std::string toString();
	//设置矩阵中的元素值
	void SetValue(DataType Data, unsigned int row, unsigned int column);
	//获取矩阵中的元素的值
	DataType GetValue(unsigned int row, unsigned int column);
};
//函数的具体实现方法
//构造函数
template<typename DataType>
SphereTable<DataType>::SphereTable(unsigned int RowLength, unsigned int ColumnLength) {
	this->RowLength = RowLength;
	this->ColumnLength = ColumnLength;
	//创建循环多重表
	this->Head = new FourNode<DataType>(0, NULL, NULL, NULL, NULL);
	this->Head->SetRight(this->Head);
	this->Head->SetLeft(this->Head);
	this->Head->SetUp(this->Head);
	this->Head->SetDown(this->Head);
 
	FourNode<DataType>*columnptr = this->Head;
	unsigned int columnindex = 1;
	FourNode<DataType>*leftptr = NULL;
	FourNode<DataType>*headptr = NULL;
	while (true) {
		unsigned int rowindex = 1;
		FourNode<DataType>*rowptr = columnptr;
		while (rowindex < RowLength) {
			if (leftptr == NULL) {
				rowptr->SetDown(new FourNode<DataType>(0, NULL, NULL, rowptr, columnptr));
				rowptr = rowptr->GetDown();
			}
			else {
				leftptr = leftptr->GetDown();
				headptr = headptr->GetDown();
				rowptr->SetDown(new FourNode<DataType>(0, leftptr, headptr, rowptr, columnptr));
				rowptr = rowptr->GetDown();
				leftptr->SetRight(rowptr);
				headptr->SetLeft(rowptr);
			}
			
			rowindex++;
		}
		columnptr->SetUp(rowptr);
		if (columnindex >= ColumnLength) break;
		else {
			columnptr->SetRight(new FourNode<DataType>(0, columnptr, this->Head, columnptr, columnptr));
			leftptr = columnptr;
			columnptr = columnptr->GetRight();
			this->Head->SetLeft(columnptr);
			headptr = this->Head;//转向头结点
			columnindex++;
		}
	}
}
//析构函数
template<typename DataType>
SphereTable<DataType>::~SphereTable() {
	this->Head->GetUp()->SetDown(NULL);
	FourNode<DataType>*columnptr = this->Head;
	while (columnptr != NULL) {
		FourNode<DataType>*rowptr = columnptr->GetRight();
		FourNode<DataType>*ptr = rowptr;
		while (rowptr != columnptr) {
			ptr = rowptr;
			rowptr = rowptr->GetRight();
			delete ptr;
		}
		columnptr = columnptr->GetDown();
		delete rowptr;
	}
}
// 将矩阵中的元素变为字符串
template<typename DataType>
std::string  SphereTable<DataType>::toString() {
	std::stringstream s_stream;
	std::string str_size;
	s_stream << "Size:[" << this->RowLength << "," << this->ColumnLength << "]";
	s_stream >> str_size;
	str_size = str_size + "\n";
	//注意用完s_stream要清除字符流
	s_stream.clear();
	std::string str_mat = "";
	FourNode<DataType>*ptr = this->Head;
	unsigned int rowindex = 0;
	while (rowindex < this->RowLength) {
		unsigned int columnindex = 0;
		while (columnindex < this->ColumnLength) {
			s_stream << ptr->GetData();
			std::string line;
			s_stream >> line;
			str_mat = str_mat + line + "\t";
			ptr = ptr->GetRight();
			columnindex++;
			s_stream.clear();
		}
		str_mat = str_mat + "\n";
		ptr = ptr->GetDown();
		rowindex++;
	}
	return str_mat + str_size;
}
//设置矩阵中的元素值
template<typename DataType>
void SphereTable<DataType>::SetValue(DataType Data, unsigned int row, unsigned int column) {
	assert(row<this->RowLength && column<this->ColumnLength);
	unsigned int index = 0;
	FourNode<DataType>*ptr = this->Head;
	//搜索行
	while (index <= row) {
		ptr = ptr->GetDown();
		index++;
	}
	//搜索列
	index = 0;
	while (index <= column) {
		ptr = ptr->GetRight();
		index++;
	}
	ptr->SetData(Data);
}
//获取矩阵中的元素的值
template<typename DataType>
DataType SphereTable<DataType>::GetValue(unsigned int row, unsigned int column) {
	assert(row<this->RowLength && column<this->ColumnLength);
	unsigned int index = 0;
	FourNode<DataType>*ptr = this->Head;
	//搜索行
	while (index <= row) {
		ptr = ptr->GetDown();
		index++;
	}
	//搜索列
	index = 0;
	while (index <= column) {
		ptr = ptr->GetRight();
		index++;
	}
	return ptr->GetData();
}
#endif // !CIRCLESPHERE_H
