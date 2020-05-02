package main

import "fmt"

//单循环链表的定义
type CircleList struct {
	head *SingleNode
	length uint
}
//构造函数，注意头结点是保存元素信息的
func NewCircleList()*CircleList{
	return&CircleList{nil,0}
}
//在链表的最后面插入一个节点
func (this *CircleList)Push_Back(value Object){
	if this.head == nil{
		this.head = NewSingleNode(value)
		this.head.SetNext(this.head)
		this.length++
		return
	}
	var ptr *SingleNode = this.head
	for ptr.GetNext()!=this.head{
		ptr = ptr.GetNext()
	}
	newnode :=NewSingleNode(value)
	newnode.SetNext(this.head)
	ptr.SetNext(newnode)
	this.length++
}
//在链表的最前面插入一个节点
func (this *CircleList)Push_Front(value Object){
	if nil == this.head{
		this.head = NewSingleNode(value)
		this.head.SetNext(this.head)
		this.length++
		return
	}
	newnode :=NewSingleNode(value)
	newnode.SetNext(this.head)
	var ptr *SingleNode = this.head
	for ptr.GetNext()!=this.head{
		ptr = ptr.GetNext()
	}
	ptr.SetNext(newnode)
	this.head = newnode
	this.length++
}
//在链表的最后面删除一个元素
func (this *CircleList)Pop_Back() Object{
	if this.length == 0{
		panic("The list is empty!")
	}
	if this.length == 1{
		data := this.head.GetValue()
		this.head = nil
		return data
	}
	var ptr *SingleNode = this.head
	var pre *SingleNode = this.head
	for ptr.GetNext() !=this.head{
		pre = ptr
		ptr = ptr.GetNext()
	}
	pre.SetNext(this.head)
	//是否可以删除节点指针？
	this.length--
	return ptr.GetValue()
}
//在链表的最前面删除一个元素
func (this *CircleList)Pop_Front() Object{
	if this.length == 0{
		panic("The list is empty!")
	}
	if this.length == 1{
		data := this.head.GetValue()
		this.head = nil
		return data
	}
	var ptr *SingleNode = this.head
	for ptr.GetNext()!= this.head{
		ptr = ptr.GetNext()
	}
	var return_ptr *SingleNode = this.head
	this.head = this.head.GetNext()
	ptr.SetNext(this.head)
	this.length--
	//需要删除指针吗？
	return return_ptr.GetValue()
}
//在index处添加一个值
func (this *CircleList)Insert(index uint,data Object){
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp <index{
		ptr = ptr.GetNext()
		tmp++
	}
	newnode := NewSingleNode(data)
	newnode.SetNext(ptr.GetNext())
	ptr.SetNext(newnode)
	this.length++
}
//删除index处的元素·
func (this *CircleList)Delete(index uint,data Object) Object{
	if index >=this.length{
		panic("Index is out of bounds")
	}else if index==0{
		data :=this.head.GetValue()
		this.head = nil
		return data
	}
	ptr := this.head
	pre := this.head
	var tmp uint = 0
	for tmp <index{
		pre = ptr
		ptr = ptr.GetNext()
		tmp++
	}
	//删除指针操作
	pre.SetNext(ptr.GetNext())
	this.length--
	return ptr.GetValue()
}
//获取index处的值
func (this *CircleList)Get(index uint) Object{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp <index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr.GetValue()
}
//设置index处的值
func (this *CircleList)Set(index uint,data Object){
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp <index{
		ptr = ptr.GetNext()
		tmp++
	}
	ptr.SetValue(data)
}
//获取index处的指针
func (this *CircleList)GetNode(index uint) *SingleNode{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp <index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr
}
//获取头指针
func (this *CircleList)GetHead() *SingleNode{
	return this.head
}
//获取链表的长度信息
func (this *CircleList)GetLength() uint{
	return this.length
}
//清除链表中的元素
func (this *CircleList)Clear(){
	this.head = nil
	this.length = 0
}
//将链表中的元素转化为string
func (this *CircleList)String() string{
	if this.head == nil{
		res := fmt.Sprintf("Array: size = %d\n", this.length)
		res += "[]"
		return res
	}
	res := fmt.Sprintf("Array: size = %d\n", this.length)
	res += "["
	ptr := this.head
	for ptr.GetNext()!= this.head{
		res += fmt.Sprint(ptr.GetValue())
		res += ", "
		ptr = ptr.GetNext()
	}
	res += fmt.Sprint(ptr.GetValue())
	res += "]"
	return res
}
//打印函数
func (this *CircleList)Print(){
	fmt.Println(this.String())
}

//双循环链表的定义，注意头结点存储信息
type BiCircleList struct {
	head *DoubleNode
	length uint
}
//构造函数
func NewBiCircleList()*BiCircleList{
	return &BiCircleList{nil,0}
}
//在链表的最后面添加一个元素
func (this *BiCircleList)Push_Back(value Object){
	if this.length == 0{
		this.head = NewDoubleNode(value)
		this.head.SetNext(this.head)
		this.head.SetPrevious(this.head)
		this.length++
		return
	}
	ptr := this.head
	for ptr.GetNext()!=this.head{
		ptr = ptr.GetNext()
	}
	newnode := NewDoubleNode(value)
	newnode.SetNext(this.head)
	newnode.SetPrevious(ptr)
	ptr.SetNext(newnode)
	this.head.SetPrevious(newnode)
	this.length++
}
//在链表的最前面插入一个元素
func (this *BiCircleList)Push_Front(value Object){
	if this.length == 0{
		this.head = NewDoubleNode(value)
		this.head.SetNext(this.head)
		this.head.SetPrevious(this.head)
		this.length++
		return
	}
	//在最后面的一个指针插入一个数据元素，并且将头指针指向这个元素
	lastptr := this.head.GetPrevious()
	newnode := NewDoubleNode(value)
	newnode.SetPrevious(lastptr)
	newnode.SetNext(this.head)
	lastptr.SetNext(newnode)
	this.head = newnode
	this.length++
}
//在链表的最前面删除一个元素
func (this *BiCircleList)Pop_Front()Object{
	headptr := this.head
	lastptr := this.head.GetPrevious()
	this.head = headptr.GetNext()
	this.head.SetPrevious(lastptr)
	lastptr.SetNext(this.head)
	this.length--
	return headptr.GetValue()
}
//在链表的最后面删除一个元素
func (this *BiCircleList)Pop_back()Object{
	headptr := this.head
	lastptr := this.head.GetPrevious()
	headptr.SetPrevious(lastptr.GetPrevious())
	lastptr.GetPrevious().SetNext(headptr)
	this.length--
	return lastptr.GetValue()
}
//获取index处的元素
func (this *BiCircleList)Get(index uint) Object{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp < index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr.GetValue()
}
//设置index处的元素
func (this *BiCircleList)Set(index uint,data Object){
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp < index{
		ptr = ptr.GetNext()
		tmp++
	}
	ptr.SetValue(data)
}
//获取index处的指针
func (this *BiCircleList)GetNode(index uint) *DoubleNode{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp < index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr
}
//在index处插入一个元素
func (this *BiCircleList)Insert(index uint,data Object){
	ptr :=this.GetNode(index)
	newnode := NewDoubleNode(data)
	newnode.SetPrevious(ptr)
	newnode.SetNext(ptr.GetNext())
	ptr.SetNext(newnode)
	this.length++
}
//删除index处的元素
func (this *BiCircleList)Delete(index uint) Object{
	ptr :=this.GetNode(index)
	pre :=ptr.GetPrevious()
	pre.SetNext(ptr.GetNext())
	ptr.GetNext().SetPrevious(pre)
	this.length--
	return ptr.GetValue()
}
//将链表中的元素转化为string
func (this *BiCircleList)String() string{
	if this.head == nil{
		res := fmt.Sprintf("Array: size = %d\n", this.length)
		res += "[]"
		return res
	}
	res := fmt.Sprintf("Array: size = %d\n", this.length)
	res += "["
	ptr := this.head
	for ptr.GetNext()!= this.head{
		res += fmt.Sprint(ptr.GetValue())
		res += ", "
		ptr = ptr.GetNext()
	}
	res += fmt.Sprint(ptr.GetValue())
	res += "]"
	return res
}
//打印函数
func (this *BiCircleList)Print(){
	fmt.Println(this.String())
}