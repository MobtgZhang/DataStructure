#ifndef TREENODE_H
#define TREENODE_H
template<typename T,typename K>
class TreeNode{
private:
    TreeNode<T,K>* left;
    TreeNode<T,K>* right;
    T data;
    K key;
public:
    TreeNode(){
        this->left = NULL;
        this->right = NULL;
    }
    TreeNode(T& data,K& key){
        this->data = data;
        this->key = key;
        this->left = NULL;
        this->right = NULL;
    }
    ~TreeNode(){}
    TreeNode<T,K>* GetLeft(){ return this->left;}
    TreeNode<T,K>* GetRight(){ return this->right;}
    void SetKey(K key){this->key = key; }
    K& GetKey(){return this->key;}
    void SetData(T data){this->data = data; }
    T& GetData(){return this->data;}
    void SetLeft(TreeNode<T,K>* left){this->left = left;}
    void SetRight(TreeNode<T,K>* right){this->right = right;}
};
#endif

#ifndef BITREE_H
#define BITREE_H
// 二叉树
template<typename T,typename K>
class BiTree{
protected:
    TreeNode<T,K>* root;
    void _recur_clear_nodes(TreeNode<T,K>* root,TreeNode<T,K>* parent); // 递归删除二叉树结点
    void _stack_clear_nodes(); // 栈的DFS非递归删除二叉树结点
    void _queue_clear_nodes(); // 栈的BFS非递归删除二叉树结点
public:
    BiTree(){
        this->root = NULL;
    }
    ~BiTree(){
        this->_stack_clear_nodes();
    }
    void PreOrderTraverse(void (*func)(TreeNode<T,K>* root)); // 先序遍历
    void MiddleOrderTraverse(void (*func)(TreeNode<T,K>* root)); // 中序遍历
    void PostOrderTraverse(void (*func)(TreeNode<T,K>* root)); // 后序遍历
    void LevelOrderTraverse(void (*func)(TreeNode<T,K>* root)); // 层次遍历
};

#endif 

#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H
// 二叉排序树
template<typename T,typename K>
class BinarySortTree: public BiTree<T,K>{
public:
    BinarySortTree():BiTree<T,K>(){}
    ~BinarySortTree(){}
    void Insert(T& data,K& key); // 插入数据
    void Remove(K key); // 删除数据
    TreeNode<T,K>* Search(K key);  // 检索数据
};
#endif 

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
// 哈夫曼树
template<typename T,typename K>
class HuffmanTree: public BiTree<T,K>{
public:
    HuffmanTree():BiTree<T,K>(){};
    ~HuffmanTree(){};
    void CreateFromVector(std::vector<std::pair<T,K>>& vec);
};
#endif 
