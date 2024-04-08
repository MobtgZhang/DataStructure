#include"bitree.hpp"
#include<vector>
#include<sort>
#include<algorithm>
// BiTree 二叉树实现方式
template<typename T,typename K>
void BiTree<T,K>::PreOrderTraverse(void (*func)(TreeNode<T,K>* root)){
    TreeNode<T,K>* ptr = this->root;
    std::stack<TreeNode<T,K>*> s_nodes;
    while(ptr!=NULL || !s_nodes.empty()){
        if(ptr!=NULL){
            func(ptr);
            s_nodes.push(ptr);
            ptr = ptr->GetLeft();
        }else{
            ptr = s_nodes.top();
            s_nodes.pop();
            ptr = ptr->GetRight();
        }
    }
}

template<typename T,typename K>
void BiTree<T,K>::MiddleOrderTraverse(void (*func)(TreeNode<T,K>* root)){
    TreeNode<T,K>* ptr = this->root;
    std::stack<TreeNode<T,K>*> s_nodes;
    while(ptr!=NULL || !s_nodes.empty()){
        if(ptr!=NULL){
            s_nodes.push(ptr);
            ptr = ptr->GetLeft();
        }else{
            ptr = s_nodes.top();
            func(ptr);
            s_nodes.pop();
            ptr = ptr->GetRight();
        }
    }
}
template<typename T,typename K>
void BiTree<T,K>::PostOrderTraverse(void (*func)(TreeNode<T,K>* root)){
    TreeNode<T,K>* curr = this->root;
    TreeNode<T,K>* prev = NULL;
    std::stack<TreeNode<T,K>*> s_nodes;
    while(curr!=NULL || !s_nodes.empty()){
        while(curr!=NULL){
            s_nodes.push(curr);
            curr = curr->GetLeft();
        }
        curr = s_nodes.top();
        if(curr->GetRight() == NULL || curr->GetRight() == prev){
            func(curr);
            prev = curr;
            s_nodes.pop();
            curr = NULL;
        }else curr = curr->GetRight();
    }
}
template<typename T,typename K>
void BiTree<T,K>::LevelOrderTraverse(void (*func)(TreeNode<T,K>* root)){
    if(root==NULL) return;
    std::queue<TreeNode<T,K>*> q_nodes;
    q_nodes.push(this->root);
    while(!q_nodes.empty()){
        TreeNode<T,K>* curr = q_nodes.front();
        func(curr);
        q_nodes.pop();
        if(curr->GetLeft()!=NULL) q_nodes.push(curr->GetLeft());
        if(curr->GetRight()!=NULL) q_nodes.push(curr->GetRight());
    }
}

template<typename T,typename K>
void BiTree<T,K>::_recur_clear_nodes(TreeNode<T,K>* root,TreeNode<T,K>* parent){
    if(root->GetLeft()!=NULL) this->_recur_clear_nodes(root->GetLeft(),root);
    if(root->GetRight()!=NULL) this->_recur_clear_nodes(root->GetRight(),root);
    if(parent!=NULL){
        if(parent->GetLeft()==root) parent->SetLeft(NULL);
        if(parent->GetRight()==root) parent->SetRight(NULL);
    }
    delete root;
    root = NULL;
}
template<typename T,typename K>
void BiTree<T,K>::_queue_clear_nodes(){
    if (this->root == NULL) return ;
    std::queue<TreeNode<T,K>*> q_nodes;
    q_nodes.push(this->root);
    while(!q_nodes.empty()){
        TreeNode<T,K>*ptr = q_nodes.front();
        q_nodes.pop();
        std::cout<<ptr->GetKey()<<std::endl;
        if (ptr->GetLeft()!=NULL) q_nodes.push(ptr->GetLeft());
        if (ptr->GetRight()!=NULL) q_nodes.push(ptr->GetRight());
        delete ptr;
        ptr = NULL;
    }
    this->root = NULL;
}

template<typename T,typename K>
void BiTree<T,K>::_stack_clear_nodes(){
    std::stack<TreeNode<T,K>*> s_nodes;
    TreeNode<T,K>*curr = this->root;
    while(!s_nodes.empty() || curr!=NULL){
        while(curr->GetLeft()!=NULL){
            s_nodes.push(curr);
            curr = curr->GetLeft();
        }
        if(curr->GetRight()==NULL){
            TreeNode<T,K>*prev;
            if (!s_nodes.empty()){
                prev = s_nodes.top();
                s_nodes.pop(); 
                if(prev->GetLeft()==curr) prev->SetLeft(NULL);
                else prev->SetRight(NULL);   
            } else prev = NULL;
            delete curr;
            curr = prev;
        }else{
            s_nodes.push(curr);
            curr = curr->GetRight();
        }
    }
    this->root = NULL;
}

// 二叉排序树
template<typename T,typename K>
void BinarySortTree<T,K>::Insert(T& data,K& key){
    if(this->root==NULL){
        this->root = new TreeNode<T,K>();
        this->root->SetData(data);
        this->root->SetKey(key);
    }else{
        TreeNode<T,K>* ptr = this->root;
        TreeNode<T,K>* pre = NULL;
        while(ptr!=NULL){
            pre = ptr;
            if(ptr->GetKey()==key) break;
            else if(ptr->GetKey()<key) ptr = ptr->GetRight();
            else ptr = ptr->GetLeft();
        }
        TreeNode<T,K>* new_ptr = new TreeNode<T,K>(data,key);
        //std::cout<<"Key: "<<"("<<pre->GetKey()<<","<<key<<")"<<std::endl;
        if(pre->GetKey()<key) pre->SetRight(new_ptr);
        else pre->SetLeft(new_ptr);
    }
}

template<typename T,typename K>
void BinarySortTree<T,K>::Remove(K key){
    TreeNode<T,K>* ptr = this->root;
    TreeNode<T,K>* pre = NULL;
    while(ptr!=NULL){
        if(key>ptr->GetKey()){
            pre = ptr;
            ptr=ptr->GetRight();
        }
        else if (key<ptr->GetKey()){
            pre = ptr;
            ptr = ptr->GetLeft();
        }
        else{
            TreeNode<T,K>* children = NULL;
            // 找到上一个结点
            if(ptr->GetLeft()!=NULL && ptr->GetRight()!=NULL){              
                // 右子树的最小结点
                /*
                children = ptr->GetRight();
                TreeNode<T,K>* tmp_pre = ptr;
                while(children->GetLeft()!=NULL){
                    tmp_pre = children;
                    children = children->GetLeft();
                }
                if(tmp_pre->GetLeft()==children) tmp_pre->SetLeft(children->GetRight());
                else tmp_pre->SetRight(children->GetRight());
                children->SetRight(ptr->GetRight());
                children->SetLeft(ptr->GetLeft());
                */
                // 另外一种方法，左子树的最大结点
                children = ptr->GetLeft();
                TreeNode<T,K>* tmp_pre = ptr;
                while(children->GetRight()!=NULL){
                    tmp_pre = children;
                    children = children->GetRight();
                }
                if(tmp_pre->GetRight()==children) tmp_pre->SetRight(children->GetLeft());
                else tmp_pre->SetLeft(children->GetLeft());
                children->SetRight(ptr->GetRight());
                children->SetLeft(ptr->GetLeft());
            }else{
                if(ptr->GetLeft()!= NULL) children = ptr->GetLeft();
                if(ptr->GetRight()!=NULL) children = ptr->GetRight();
            }
            if(pre!=NULL){
                if(pre->GetLeft()==ptr) pre->SetLeft(children);
                else pre->SetRight(children);
            }else this->root = children;
            // 删除结点
            delete ptr;
            ptr = NULL;
            break;
        }
    }
}
template<typename T,typename K>
TreeNode<T,K>* BinarySortTree<T,K>::Search(K key){
    TreeNode<T,K>* ptr = this->root;
    TreeNode<T,K>* pre = NULL;
    while(ptr!=NULL){
        if(ptr->GetKey() == key) break;
        else{
            pre = ptr;
            if(key<ptr->GetKey()) ptr=ptr->GetLeft();
            else ptr=ptr->GetRight();
        }
    }
    return ptr;
}

//平衡二叉树
template<typename T,typename K>
class AVLTree : public BiTree<T,K>{
public:
    AVLTree():BiTree<T,K>(){}
    ~AVLTree(){}
    void Insert(T& data,K& key);
    void Remove(K key);
protected:
    void RotateLL(TreeNode<T,K>*root,TreeNode<T,K>*parent);
    void RotateLR(TreeNode<T,K>*root,TreeNode<T,K>*parent);
    void RotateRR(TreeNode<T,K>*root,TreeNode<T,K>*parent);
    void RotateRL(TreeNode<T,K>*root,TreeNode<T,K>*parent);
    int Height(TreeNode<T,K>* root);
};
template<typename T,typename K>
void AVLTree<T,K>::Insert(T& data,K& key){
    // 插入数据
    TreeNode<T,K>* newNode = new TreeNode<T,K>(data,key);
    TreeNode<T,K>* current = this->root;
    TreeNode<T,K>* parent = NULL;
    std::stack<TreeNode<T,K>*> s_ptrs;

    
    while(current!=NULL){
        parent = current;
        s_ptrs.push(current);
        if(newNode->GetKey()<current->GetKey()) current = current->GetLeft();
        else current = current->GetRight();
    }
    if(parent==NULL) this->root = newNode;
    else if (newNode->GetKey()<parent->GetKey()) parent->SetLeft(newNode);
    else parent->SetRight(newNode);
    // 平衡树
    while(!s_ptrs.empty()){
        parent = s_ptrs.top();
        int balanceFactor = this->Height(newNode->GetLeft()) - this->Height(newNode->GetRight());
        if(balanceFactor==-2){
            TreeNode<T,K>* tmp_ptr = newNode->GetRight();
            int tpbalance = this->Height(tmp_ptr->GetLeft()) - this->Height(tmp_ptr->GetRight());
            if(tpbalance==-1) this->RotateLL(newNode,parent);
            else this->RotateRL(newNode,parent); 
        }else if(balanceFactor==2){
            TreeNode<T,K>* tmp_ptr = newNode->GetLeft();
            int tpbalance = this->Height(tmp_ptr->GetLeft()) - this->Height(tmp_ptr->GetRight());
            if(tpbalance==1) this->RotateRR(newNode,parent);
            else this->RotateLR(newNode, parent);
        }else {}
        newNode = parent;
        s_ptrs.pop();
    }
}
template<typename T,typename K>
void AVLTree<T,K>::Remove(K key){
    TreeNode<T,K>* ptr = this->root;
    std::stack<TreeNode<T,K>*>s_ptrs;
    while(ptr!=NULL){
        if(key!=ptr->GetKey()){
            s_ptrs.push(ptr);
            if(key>ptr->GetKey()) ptr = ptr->GetRight();
            else ptr = ptr->GetLeft();
        }
        else{
            TreeNode<T,K>* children = NULL;
            TreeNode<T,K>* pre = NULL;
            if(!s_ptrs.empty()) pre = s_ptrs.top();
            if(ptr->GetLeft()!=NULL && ptr->GetRight()!=NULL) {
                children = ptr->GetRight();
                TreeNode<T,K>* tmp_pre = ptr;
                while(children->GetLeft()!=NULL){
                    tmp_pre = children;
                    children = children->GetLeft();
                }
                if(tmp_pre->GetLeft()==children) tmp_pre->SetLeft(children->GetRight());
                else tmp_pre->SetRight(children->GetRight());
                children->SetRight(ptr->GetRight());
                children->SetLeft(ptr->GetLeft());
                // 另外一种方法，左子树的最大结点
                /*
                children = ptr->GetLeft();
                TreeNode<T,K>* tmp_pre = ptr;
                while(tmp_ptr->GetRight()!=NULL){
                    tmp_pre = children;
                    tmp_ptr = children->GetRight();
                }
                if(tmp_pre->GetRight()==children) tmp_pre->SetRight(children->GetLeft());
                else tmp_pre->SetLeft(children->GetLeft());
                children->SetRight(ptr->GetRight());
                children->SetLeft(ptr->GetLeft());
                */
            }else{
                if(ptr->GetLeft()!=NULL) children = ptr->GetLeft();
                if(ptr->GetRight()!=NULL) children = ptr->GetRight();
            }
            if(pre!=NULL){
                if(pre->GetLeft()==ptr) pre->SetLeft(children);
                else pre->SetRight(children);
            }else this->root = children;
            delete ptr;
            ptr = NULL;
            break;
        }
    }
    // 平衡二叉树
    bool stop_flag = false;
    while(!s_ptrs.empty()){
        TreeNode<T,K>* tempory_root = s_ptrs.top(); s_ptrs.pop();
        TreeNode<T,K>* tempory_pre =  NULL;
        if (!s_ptrs.empty()){
            tempory_pre = s_ptrs.top();
        }
        int balanceFactor = this->Height(tempory_root->GetLeft()) - this->Height(tempory_root->GetRight());
        if(balanceFactor==2){
            TreeNode<T,K>* tmp_ptr = tempory_root->GetLeft();
            int tpbalance = this->Height(tmp_ptr->GetLeft()) - this->Height(tmp_ptr->GetRight());
            TreeNode<T,K>*fake_ptr = tempory_pre;
            if(tempory_pre==NULL){
                fake_ptr = new TreeNode<T,K>();
                fake_ptr->SetRight(tempory_root);
            }
            if(tpbalance==1) this->RotateRR(tempory_root,fake_ptr);
            else this->RotateLR(tempory_root,fake_ptr);
            if(tempory_pre==NULL){
                this->root = fake_ptr->GetRight();
                delete fake_ptr;
            }
        }else if (balanceFactor==-2){
            TreeNode<T,K>* tmp_ptr = tempory_root->GetRight();
            int tpbalance = this->Height(tmp_ptr->GetLeft()) - this->Height(tmp_ptr->GetRight());
            TreeNode<T,K>*fake_ptr = tempory_pre;
            if(tempory_pre==NULL){
                fake_ptr = new TreeNode<T,K>();
                fake_ptr->SetRight(tempory_root);
            }
            if(tpbalance==-1)this->RotateLL(tempory_root,fake_ptr);
            else this->RotateRL(tempory_root,fake_ptr);
            if(tempory_pre==NULL){
                this->root = fake_ptr->GetRight();
                delete fake_ptr;
            }
        }else {}
    }
}
template<typename T,typename K>
void AVLTree<T,K>::RotateLR(TreeNode<T,K>*node,TreeNode<T,K>*parent){
    TreeNode<T,K>* leftChild = node->GetLeft();
    TreeNode<T,K>* lrChild = leftChild->GetRight();
    node->SetLeft(lrChild);
    leftChild->SetRight(lrChild->GetLeft());
    lrChild->SetLeft(leftChild);
    this->RotateRR(node,parent);
}
template<typename T,typename K>
void AVLTree<T,K>::RotateRR(TreeNode<T,K>*node,TreeNode<T,K>*parent){
    TreeNode<T, K>* leftChild = node->GetLeft();
    if(parent->GetLeft()==node) parent->SetLeft(leftChild);
    else parent->SetRight(leftChild);
    node->SetLeft(leftChild->GetRight());
    leftChild->SetRight(node);
}
template<typename T,typename K>
void AVLTree<T,K>::RotateLL(TreeNode<T,K>*node,TreeNode<T,K>*parent){
    TreeNode<T,K>*rightChild = node->GetRight();
    if(parent->GetRight()==node) parent->SetRight(rightChild);
    else parent->SetLeft(rightChild);
    node->SetRight(rightChild->GetLeft());
    rightChild->SetLeft(node);
}
template<typename T,typename K>
void AVLTree<T,K>::RotateRL(TreeNode<T,K>*node,TreeNode<T,K>*parent){
    TreeNode<T,K>* rightChild = node->GetRight();
    TreeNode<T,K>* rlChild = rightChild->GetLeft();
    node->SetRight(rlChild);
    rightChild->SetLeft(rlChild->GetRight());
    rlChild->SetRight(rightChild);
    this->RotateLL(node,parent);
}

template<typename T,typename K>
int AVLTree<T,K>::Height(TreeNode<T,K>* node){
    int height = 0;
    if(node==NULL) return 0;
    std::queue<TreeNode<T,K>*>q;
    q.push(node);
    while(!q.empty()){
        ++height;
        int levelSize = q.size();
        for(int k=0;k<levelSize;k++){
            TreeNode<T,K>* ptr = q.front();
            q.pop();
            if(ptr->GetLeft()!=NULL) q.push(ptr->GetLeft());
            if(ptr->GetRight()!=NULL) q.push(ptr->GetRight());
        }
    }
    return height;
}

// 哈夫曼树
template<typename T,typename K>
void HuffmanTree<T,K>::CreateFromVector(std::vector<std::pair<T,K>>& vec){
    
    std::vector<TreeNode<T,K>*>ptr_vec;
    for(int k=0;k<vec.size();k++){
        TreeNode<T,K>* ptr = new TreeNode<T,K>(vec[k].first,vec[k].second);
        ptr_vec.push_back(ptr);
    }
    std::vector<TreeNode<T,K>*> new_vec;
    while(true){
        //排序
        std::sort(ptr_vec.begin(),ptr_vec.end(),[](TreeNode<T,K>* a,TreeNode<T,K>* b){
            return a->GetKey() < b->GetKey();
        });
        //构建树
        for(int k=0;k<ptr_vec.size()-1;k+=2){
            int key = ptr_vec[k]->GetKey() + ptr_vec[k+1]->GetKey();
            T data;
            TreeNode<T,K>* ptr = new TreeNode<T,K>(data,key);
            ptr->SetLeft(ptr_vec[k]);
            ptr->SetRight(ptr_vec[k+1]);
            new_vec.push_back(ptr);
        }
        std::cout<<"Size: "<<new_vec.size()<<std::endl;
        if((ptr_vec.size()+1)%2==0) new_vec.push_back(ptr_vec[ptr_vec.size()-1]);
        if(new_vec.size()==1)break;
        ptr_vec.clear();
        ptr_vec.resize(new_vec.size()); // 预先分配足够空间
        std::copy(new_vec.begin(), new_vec.end(), ptr_vec.begin());
        new_vec.clear();
    }
    this->root = new_vec[0];
}