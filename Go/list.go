package main

import "fmt"

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
func (this *SingleList)Push_back(v interface{}){
	var ptr *SingleNode = this.head
	for nil != ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	newnode := NewSingleNode(v)
	ptr.SetNode(newnode)
	this.length++
}
//在链表的最前面插入一个元素
func (this *SingleList)Push_front(v interface{}){
	newnode := NewSingleNode(v)
	newnode.SetNode(this.head.GetNext())
	this.head.SetNode(newnode)
	this.length++
}
//在链表的最后面删除一个元素
func (this *SingleList)Pop_back() interface{}{
	if nil ==this.head.GetNext(){
		panic("The List is empty!")
	}
	var ptr *SingleNode = this.head
	var pre *SingleNode = nil
	for nil != ptr.GetNext(){
		pre = ptr
		ptr = ptr.GetNext()
	}
	pre.SetNode(nil)
	this.length--
	//这个需要删除指针吗？
	return ptr.GetValue()
}
//在链表最前面删除一个元素
func (this *SingleList)Pop_front() interface{}{
	if nil == this.head.GetNext(){
		panic("The List is empty!")
	}
	var ptr *SingleNode = this.head.GetNext()
	this.head.SetNode(ptr.GetNext())
	this.length--
	//这里需要删除指针吗？
	return ptr.GetValue()
}
//在某个节点后面插入一个节点
func (this *SingleList)Insert(index uint,v interface{}){
	if index >= this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp<=index{
		ptr=ptr.GetNext()
		tmp++
	}
	newnode := NewSingleNode(v)
	newnode.SetNode(ptr.GetNext())
	ptr.SetNode(newnode)
	this.length++
}
//删除index节点处的元素
func (this *SingleList)Delete(index uint) interface{}{
	if index >= this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var pre *SingleNode = nil
	var tmp uint = 0
	for tmp<=index{
		pre = ptr
		ptr=ptr.GetNext()
		tmp++
	}
	pre.SetNode(ptr.GetNext())
	//这里可以删除节点吗？
	this.length--
	return ptr.GetValue()
}
//获取第k个节点的元素
func (this *SingleList)Get(index uint) interface{}{
	if index >= this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp<=index{
		ptr=ptr.GetNext()
		tmp++
	}
	return ptr.GetValue()
}
//判断链表是否为空链表
func (this*SingleList)Empty()bool{
	return this.length==0
}
//将链表中的元素清空
//这里不知道是否清除没有用到的指针
func (this *SingleList)Clear(){
	this.head = nil
}
//获取index处的指针
func (this *SingleList)GetNode(index uint) *SingleNode{
	if index>=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp<=index{
		ptr=ptr.GetNext()
		tmp++
	}
	return ptr
}
//将链表中的index处的元素设置为data
func (this *SingleList)Set(index uint,data interface{}){
	if index>=this.length{
		panic("Index is out of bounds")
	}
	ptr := this.head
	var tmp uint = 0
	for tmp<=index{
		ptr=ptr.GetNext()
		tmp++
	}
	ptr.SetValue(data)
}
//获取链表的长度信息
func (this *SingleList)GetLength() uint{
	return this.length
}
//获取链表中尾部的数据值
func (this *SingleList)Back() interface{}{
	if this.length==0{
		panic("The length of list is zero!")
	}
	ptr := this.head
	for nil != ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	return ptr.GetValue()
}
//获取链表中头部的元素
func (this *SingleList)Front() interface{}{
	if this.length==0{
		panic("The length of list is zero!")
	}
	return this.head.GetNext().GetValue()
}
//将链表中的元素转化为string
func (this *SingleList)String() string{
	res := fmt.Sprintf("Array: size = %d\n", this.length)
	res += "["
	var k uint = 0
	for k = 0; k < this.length; k++ {
		res += fmt.Sprint(this.Get(k))
		if k != this.length-1 {
			res += ", "
		}
	}
	res += "]"
	return res
}
//打印函数
func (this *SingleList)Print(){
	fmt.Println(this.String())
}

//表示双链表信息