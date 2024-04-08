#pragma once
#define NULL 0
template<typename DataType>
class ThreadTreeNode {
private:
	DataType value;
	ThreadTreeNode<DataType>* LeftChild;
	ThreadTreeNode<DataType>* RIghtChild;
	unsigned int ltag, rtag;
public:
	ThreadTreeNode(DataType value, ThreadTreeNode<DataType>* LeftChild, ThreadTreeNode<DataType>* RightChild) {
		this->LeftChild = LeftChild;
		this->RIghtChild = RightChild;
		this->value = value;
		this->ltag = 0;
		this->rtag = 0;
	}
	ThreadTreeNode(DataType value) {
		this->LeftChild = NULL;
		this->RIghtChild = NULL;
		this->value = value;
		this->ltag = 0;
		this->rtag = 0;
	}
	ThreadTreeNode(DataType value,
		ThreadTreeNode<DataType>* LeftChild, ThreadTreeNode<DataType>* RightChild,
		unsigned int ltag,unsigned int rtag) {
		this->LeftChild = LeftChild;
		this->RIghtChild = RightChild;
		this->value = value;
		this->ltag = ltag;
		this->rtag = rtag;
	}
	ThreadTreeNode<DataType>* GetLeftChild() { return this->LeftChild; }
	void SetLeftChild(ThreadTreeNode<DataType>* node) { this->LeftChild = node; }
	ThreadTreeNode<DataType>* GetRightChild() { return this->RIghtChild; }
	void SetRightChild(ThreadTreeNode<DataType>* node) { this->RIghtChild = node; }
	DataType GetValue() { return this->value; }
	void SetValue(DataType value) { this->value = value; }
	unsigned int GetLeftTag() { return this->ltag; }
	void SetLeftTag(unsigned int tag) { this->ltag = tag; }
	unsigned int GetRightTag() { return this->rtag; }
	void SetRightTag(unsigned int tag) { this->rtag = tag; }
	~ThreadTreeNode() {}
};

template<typename DataType>
class ThreadTree {
protected:
	ThreadTreeNode<DataType>* root;
public:
	virtual void CreateThreadTree() = 0;
};
template<typename DataType>
class InOrderThreadTree :public ThreadTree<DataType> {
protected:
	static ThreadTreeNode<DataType>* InThread(ThreadTreeNode<DataType>* p, ThreadTreeNode<DataType>* pre) {
		if (p != NULL) {
			InThread(p->GetLeftChild(), pre);
			if (p->GetLeftChild() == NULL) {
				p->SetLeftChild(pre);
				p->SetLeftTag(1);
			}
			if (pre != NULL && pre->GetRightChild() == NULL) {
				pre->SetRightChild(p);
				pre->SetRightTag(1);
			}
			pre = p;
			InThread(p->GetRightChild(), pre);
		}
	}
public:
	InOrderThreadTree() {

	}
	void CreateThreadTree() {
		ThreadTreeNode<DataType>pre = NULL;
		if (this->root != NULL) {
			InOrderThreadTree::InThread(this->root, pre);
			//Here has some of problems
			pre->SetRightChild(NULL);
			pre->SetRightTag(1);
		}
	}
};