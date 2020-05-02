package main
//表示单链表的节点
type SingleNode struct{
	next *SingleNode
	value interface{}
}
//构造函数
func NewSingleNode(v interface{}) *SingleNode{
	return &SingleNode{nil,v}
}
func (this *SingleNode)GetNext() *SingleNode{
	return this.next
}
func (this *SingleNode)GetValue() interface{}{
	return this.value
}
func (this *SingleNode)SetNext(newnode *SingleNode){
	this.next = newnode
}
func (this *SingleNode)SetValue(value interface{}){
	this.value = value
}

//表示双链表节点
type DoubleNode struct {
	next *DoubleNode
	previous *DoubleNode
	value interface{}
}
//构造函数
func NewDoubleNode(v interface{}) *DoubleNode{
	return &DoubleNode{nil,nil,v}
}
func (this *DoubleNode)GetNext()*DoubleNode{
	return this.next
}
func (this *DoubleNode)GetPrevious()*DoubleNode{
	return this.previous
}
func (this *DoubleNode)GetValue() interface{}{
	return this.value
}
func (this *DoubleNode)SetNext(next *DoubleNode){
	this.next = next
}
func (this *DoubleNode)SetPrevious(prevoius *DoubleNode){
	this.previous = prevoius
}
func (this *DoubleNode)SetValue(value interface{}){
	this.value = value
}
