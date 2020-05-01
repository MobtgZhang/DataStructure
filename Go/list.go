package List

import "errors"

//表示单链表
type SingleList struct{
	head *SingleNode
	length uint
}
//链表的构造函数，注意头结点不存储元素信息
func NewSingleList() *SingleList{
	return &SingleList{NewSingleNode(0),0}
}
//在链表的最后面插入一个元素
func (this *SingleList)push_back(v interface{}){
	var ptr *SingleNode = this.head
	for nil != ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	newnode := NewSingleNode(v)
	ptr.SetNode(newnode)
}
//在链表的最前面插入一个元素
//在链表的最后面删除一个元素
//在链表最前面删除一个元素
//在某个节点后面插入一个节点
//获取第k个节点的元素
func (this *SingleList)Get(index uint) interface{}{
	if index >= this.length{
		errors.New("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp<=index{
		ptr=ptr.GetNext()
		tmp++
	}
	return ptr.GetValue()
}
func (this *SingleList)Insert(ptr*SingleNode,v interface{}) bool{
	if nil == ptr{
		return false
	}
	oldnode :=ptr.GetNext()
	newnode := NewSingleNode(v)
	newnode.SetNode(oldnode)
	ptr.SetNode(newnode)
	return true
}



