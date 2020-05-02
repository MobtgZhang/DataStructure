package main

import (
	"fmt"
)

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
func (this *SingleList)Push_Back(v interface{}){
	var ptr *SingleNode = this.head
	for nil != ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	newnode := NewSingleNode(v)
	ptr.SetNext(newnode)
	this.length++
}
//在链表的最前面插入一个元素
func (this *SingleList)Push_Front(v interface{}){
	newnode := NewSingleNode(v)
	newnode.SetNext(this.head.GetNext())
	this.head.SetNext(newnode)
	this.length++
}
//在链表的最后面删除一个元素
func (this *SingleList)Pop_Back() interface{}{
	if nil ==this.head.GetNext(){
		panic("The List is empty!")
	}
	var ptr *SingleNode = this.head
	var pre *SingleNode = nil
	for nil != ptr.GetNext(){
		pre = ptr
		ptr = ptr.GetNext()
	}
	pre.SetNext(nil)
	this.length--
	//这个需要删除指针吗？
	return ptr.GetValue()
}
//在链表最前面删除一个元素
func (this *SingleList)Pop_Front() interface{}{
	if nil == this.head.GetNext(){
		panic("The List is empty!")
	}
	var ptr *SingleNode = this.head.GetNext()
	this.head.SetNext(ptr.GetNext())
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
	newnode.SetNext(ptr.GetNext())
	ptr.SetNext(newnode)
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
	pre.SetNext(ptr.GetNext())
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
	this.length =0
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
//获取表头的节点
func (this *SingleList)GetHead()*SingleNode{
	return this.head
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
type DoubleList struct {
	head *DoubleNode
	length uint
}
//构造函数,注意表头不存储信息
func NewDoubleList()*DoubleList{
	return &DoubleList{NewDoubleNode(8888),0}
}
//在链表的最后面插入一个元素
func (this *DoubleList)Push_Back(value interface{}){
	var ptr *DoubleNode= this.head
	for nil != ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	newnode := NewDoubleNode(value)
	ptr.SetNext(newnode)
	newnode.SetPrevious(ptr)
	this.length++
}
//在链表的最前面插入一个元素
func (this *DoubleList)Push_Front(value interface{}){
	newnode := NewDoubleNode(value)
	newnode.SetPrevious(this.head)
	newnode.SetNext(this.head.GetNext())
	this.head.SetNext(newnode)
	this.length++
}
//在链表的最后面删除一个元素
func (this *DoubleList)Pop_Back() interface{}{
	if this.length == 0{
		panic("The length of the list is empty!")
	}
	ptr := this.head
	if nil == ptr.GetNext(){
		ptr = ptr.GetNext()
	}
	pre := ptr.GetPrevious()
	pre.SetNext(nil)
	//这里是否删除指针？
	this.length--
	return ptr.GetValue()
}
//在链表的最前面删除一个元素
func (this *DoubleList)Pop_Front() interface{}{
	if this.length == 0{
		panic("The length of the list is empty!")
	}
	ptr :=this.head.GetNext()
	this.head.SetNext(ptr.GetNext())
	ptr.GetNext().SetPrevious(this.head)
	//这里是否删除指针吗？
	return ptr.GetValue()
}
//在某个节点后面插入一个节点
func (this *DoubleList)Insert(index uint,data interface{}){
	if index >=this.length{
		panic("Index is out of bounds")
	}
	var tmp uint = 0
	ptr := this.head
	for tmp <=index{
		ptr = ptr.GetNext()
		tmp++
	}
	newnode := NewDoubleNode(data)
	newnode.SetNext(ptr.GetNext())
	newnode.SetPrevious(ptr)
	ptr.SetNext(newnode)
	this.length++
}
//删除index的节点
func (this *DoubleList)Delete(index uint) interface{}{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	var tmp uint = 0
	ptr := this.head
	for tmp <=index{
		ptr = ptr.GetNext()
		tmp++
	}
	pre := ptr.GetPrevious()
	pre.SetNext(ptr.GetNext())
	ptr.GetNext().SetPrevious(pre)
	//这里是否要删除节点指针？
	this.length--
	return ptr.GetValue()
}
//获取在index处的节点的值
func (this *DoubleList)Get(index uint) interface{}{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	var tmp uint = 0
	ptr := this.head
	for tmp<=index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr.GetValue()
}
//获取在index处的节点
func (this *DoubleList)GetNode(index uint)*DoubleNode{
	if index >=this.length{
		panic("Index is out of bounds")
	}
	var tmp uint = 0
	ptr := this.head
	for tmp<=index{
		ptr = ptr.GetNext()
		tmp++
	}
	return ptr
}
//将index处的值设置为data
func (this *DoubleList)Set(index uint,data interface{}){
	ptr := this.GetNode(index)
	ptr.SetValue(data)
}
//获取链表的头结点
func (this *DoubleList)GetHead()*DoubleNode{
	return this.head
}
//获取链表的长度信息
func (this *DoubleList)GetLength() uint{
	return this.length
}
//判断链表是否为空链表
func (this *DoubleList)Empty()bool{
	return this.length == 0
}
//清除链表中的元素信息
func (this *DoubleList)Clear(){
	//这里是否要清除指针呢？
	this.head = nil
	this.length = 0
}
//获取链表中最后一个元素
func (this *DoubleList)Back() interface{}{
	if this.length == 0{
		panic("The list is Empty!")
	}
	return this.Get(this.length-1)
}
//获取链表中的第一个元素
func (this *DoubleList)Front() interface{}{
	if this.length == 0{
		panic("The list is Empty!")
	}
	return this.head.GetValue()
}
//将链表中的元素转化为string
func (this *DoubleList)String() string{
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
func (this *DoubleList)Print(){
	fmt.Println(this.String())
}
