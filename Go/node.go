package List
//表示链表的节点
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
func (this *SingleNode)SetNode(newnode *SingleNode){
	this.next = newnode
}
func (this *SingleNode)SetValue(value interface{}){
	this.value = value
}
