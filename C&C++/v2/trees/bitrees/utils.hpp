#include<iostream>
#ifndef UTILS_H
#define UTILS_H
template<typename T,typename K>
void print_nodes(TreeNode<T,K>* root);
std::string generateRandomString(const size_t length);
// 定义可能的字符集合，包括大小写字母和数字
const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
#endif
