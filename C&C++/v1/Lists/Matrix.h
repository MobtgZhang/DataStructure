#pragma once
#ifndef ABSTRACT_MATRIX
#define ABSTRACT_MATRIX
template<typename DataType>
class AbstractMatrix {
protected:
	//��ʾ��һ��Ԫ�ص�λ��
	FourNode<DataType>*Head;
	//��ʾ����Ĵ�С
	unsigned int RowLength;
	unsigned int ColumnLength;
public:
	//��ȡ�к��еĴ�С
	unsigned int GetRow() { return this->RowLength; }
	unsigned int GetColumn() { return this->ColumnLength; }
	//��ȡͷ���ָ��
	FourNode<DataType>*GetHead() { return this->Head; }
	// �������е�Ԫ�ر�Ϊ�ַ���
	virtual std::string toString()=0;
	//���þ����е�Ԫ��ֵ
	virtual void SetValue(DataType Data, unsigned int row, unsigned int column)=0;
	//��ȡ�����е�Ԫ�ص�ֵ
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
	//���캯��
	Matrix(unsigned int RowLength, unsigned int ColumnLength);
	// �������е�Ԫ�ر�Ϊ�ַ���
	std::string toString();
	//���þ����е�Ԫ��ֵ
	void SetValue(DataType Data, unsigned int row, unsigned int column);
	//��ȡ�����е�Ԫ�ص�ֵ
	DataType GetValue(unsigned int row, unsigned int column);
	//��������
	~Matrix();
};
//�����к�����ʵ�ַ���
//���캯��
template<typename DataType>
Matrix<DataType>::Matrix(unsigned int RowLength, unsigned int ColumnLength) {
	//������������ʼ��
	//���������к��еĴ�С
	this->RowLength = RowLength;
	this->ColumnLength = ColumnLength;
	//����ÿһ��
	this->Head = new FourNode<DataType>(0, NULL, NULL, NULL, NULL);
	FourNode<DataType>*columnptr = this->Head;
	unsigned int index = 1;
	while (index < ColumnLength) {
		columnptr->SetRight(new FourNode<DataType>(0, columnptr, NULL, NULL, NULL));
		columnptr = columnptr->GetRight();
		index++;
	}
	//����ÿһ��
	columnptr = this->Head;
	//���ڱ�Ǵ���ÿһ��Ԫ�����һ�е�Ԫ��
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
//��������
template<typename DataType>
Matrix<DataType>::~Matrix() {
	FourNode<DataType>*rowptr = this->Head;
	//������
	//��¼��һ����ָ��
	FourNode<DataType>*prerowptr = NULL;
	while (rowptr != NULL) {
		prerowptr = rowptr;
		//��¼��һ����ָ�룬ע�⣺��һ���Ȳ���ɾ��
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
//�������е�Ԫ��ת��Ϊ�ַ���
template<typename DataType>
std::string Matrix<DataType>::toString() {
	std::stringstream s_stream;
	std::string str_size;
	s_stream << "Size:[" << this->RowLength << "," << this->ColumnLength << "]";
	s_stream >> str_size;
	str_size = str_size + "\n";
	//ע������s_streamҪ����ַ���
	s_stream.clear();
	std::string str_mat = "";
	FourNode<DataType>*rowptr = this->Head;
	//Ѱ����

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
//��ȡ�����е�Ԫ�ص�ֵ
template<typename DataType>
DataType Matrix<DataType>::GetValue(unsigned int row, unsigned int column) {
	FourNode<DataType>*rowptr = this->Head;
	//Ѱ����
	unsigned int index = 0;
	while (index < row) {
		rowptr = rowptr->GetRight();
		index++;
	}
	FourNode<DataType>*columnptr = rowptr;
	//Ѱ����
	index = 0;
	while (index < column) {
		columnptr = columnptr->GetDown();
		index++;
	}
	return columnptr->GetData();
}
//���þ����е�Ԫ��ֵ
template<typename DataType>
void Matrix<DataType>::SetValue(DataType Data, unsigned int row, unsigned int column) {
	FourNode<DataType>*rowptr = this->Head;
	//Ѱ����
	unsigned int index = 0;
	while (index < row) {
		rowptr = rowptr->GetRight();
		index++;
	}
	FourNode<DataType>*columnptr = rowptr;
	//Ѱ����
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
//����һ����׼����ѭ����
template<typename DataType>
class SphereTable :AbstractMatrix<DataType> {
public:
	SphereTable(unsigned int RowLength, unsigned int ColumnLength);
	~SphereTable();
	// �������е�Ԫ�ر�Ϊ�ַ���
	std::string toString();
	//���þ����е�Ԫ��ֵ
	void SetValue(DataType Data, unsigned int row, unsigned int column);
	//��ȡ�����е�Ԫ�ص�ֵ
	DataType GetValue(unsigned int row, unsigned int column);
};
//�����ľ���ʵ�ַ���
//���캯��
template<typename DataType>
SphereTable<DataType>::SphereTable(unsigned int RowLength, unsigned int ColumnLength) {
	this->RowLength = RowLength;
	this->ColumnLength = ColumnLength;
	//����ѭ�����ر�
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
			headptr = this->Head;//ת��ͷ���
			columnindex++;
		}
	}
}
//��������
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
// �������е�Ԫ�ر�Ϊ�ַ���
template<typename DataType>
std::string  SphereTable<DataType>::toString() {
	std::stringstream s_stream;
	std::string str_size;
	s_stream << "Size:[" << this->RowLength << "," << this->ColumnLength << "]";
	s_stream >> str_size;
	str_size = str_size + "\n";
	//ע������s_streamҪ����ַ���
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
//���þ����е�Ԫ��ֵ
template<typename DataType>
void SphereTable<DataType>::SetValue(DataType Data, unsigned int row, unsigned int column) {
	assert(row<this->RowLength && column<this->ColumnLength);
	unsigned int index = 0;
	FourNode<DataType>*ptr = this->Head;
	//������
	while (index <= row) {
		ptr = ptr->GetDown();
		index++;
	}
	//������
	index = 0;
	while (index <= column) {
		ptr = ptr->GetRight();
		index++;
	}
	ptr->SetData(Data);
}
//��ȡ�����е�Ԫ�ص�ֵ
template<typename DataType>
DataType SphereTable<DataType>::GetValue(unsigned int row, unsigned int column) {
	assert(row<this->RowLength && column<this->ColumnLength);
	unsigned int index = 0;
	FourNode<DataType>*ptr = this->Head;
	//������
	while (index <= row) {
		ptr = ptr->GetDown();
		index++;
	}
	//������
	index = 0;
	while (index <= column) {
		ptr = ptr->GetRight();
		index++;
	}
	return ptr->GetData();
}
#endif // !CIRCLESPHERE_H
