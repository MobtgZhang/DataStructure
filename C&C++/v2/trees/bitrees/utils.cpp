#include<iostream>
#include<string>
#include<random>
#include "utils.hpp"
template<typename T,typename K>
void print_nodes(TreeNode<T,K>* root){
    std::cout<<"("<<root->GetKey()<<",'"<<root->GetData()<<"')"<<std::endl;
};


std::string generateRandomString(const size_t length) {
    // 使用std::mt19937作为随机数生成器，它基于Mersenne Twister算法，具有较好的随机性
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);

    std::string randomStr;
    randomStr.reserve(length); // 预留所需空间，避免不必要的内存重分配

    for (size_t i = 0; i < length; ++i) {
        randomStr += chars[dis(gen)]; // 从字符集中随机选择一个字符添加到字符串
    }

    return randomStr;
};
