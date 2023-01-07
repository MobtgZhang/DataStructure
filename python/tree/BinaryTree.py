class Node:
    def __init__(self,data = None,left = None,right = None):
        self.data = data
        self.left = left
        self.right = right
class BinaryTree:
    def __init__(self,root = None):
        self.root = root
    def is_empty(self):
        return self.root == None
    def preOrder(self,NodeBin):
        if NodeBin == None:
            return 
        print(NodeBin.data)
        self.preOrder(NodeBin.left)
        self.preOrder(NodeBin.right)
    def inOrder(self,NodeBin):
        if NodeBin == None:
            return 
        self.inOrder(NodeBin.left)
        print(NodeBin.data)
        self.inOrder(NodeBin.right)
    def postOrder(self,NodeBin):
        if NodeBin == None:
            return 
        self.postOrder(NodeBin.left)
        self.postOrder(NodeBin.right)
        print(NodeBin.data)
def Test_Node():
    n1 = Node(data = 'D')
    n2 = Node(data = 'E')
    n3 = Node(data = 'F')
    n4 = Node(data = 'B',left = n1,right = n2)
    n5 = Node(data = 'C',left = n3,right = None)
    root = Node(data = 'A',left = n4,right = n5)
    bt = BinaryTree(root)
    print("order list:")
    bt.preOrder(root)
    print("inorder list:")
    bt.inOrder(root)
    print("postorder list:")
    bt.postOrder(root)
if __name__ == "__main__":
    Test_Node()
