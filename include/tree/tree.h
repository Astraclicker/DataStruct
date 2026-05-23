#pragma once
#include <iostream>
#include "../array/array.h"

template<typename T>
struct node_tree {
    node_tree *father;
    T data;
    array<node_tree *> *son;
};

template<typename T>
class tree {
public:
    node_tree<T> *root;
    node_tree<T> *current_node_tree;


    //构造
    tree();

    tree(T data);

    //从current_node_tree建立son
    void grow(T data);

    //展示current_node_tree下所有目录
    void show();

    //从director开始遍历tree
    void list_dir(node_tree<T> *director, unsigned int depth);

    //切换到下级目录
    bool go_next(unsigned int index);

    //返回上级目录
    void go_back();
};


template<typename T>
tree<T>::tree() {
    root = new node_tree<T>;

    root->data = T();
    root->father = nullptr;
    root->son = nullptr;

    current_node_tree = root;
}

template<typename T>
tree<T>::tree(T data) {
    root = new node_tree<T>;

    root->data = data;
    root->father = nullptr;
    root->son = nullptr;

    current_node_tree = root;
}

template<typename T>
void tree<T>::grow(T data) {
    auto temp = new node_tree<T>;

    temp->father = current_node_tree;
    temp->data = data;
    temp->son = nullptr;

    if (current_node_tree->son == nullptr) {
        current_node_tree->son = new array<node_tree<T> *>;
    }
    current_node_tree->son->push_back(temp);
}

template<typename T>
void tree<T>::show() {
    unsigned int index = 0;
    node_tree<T> **temp = current_node_tree->son->first();
    while (temp != current_node_tree->son->current()) {
        std::cout << index++ << " : " << (*temp)->data << std::endl;
        ++temp;
    }
}

template<typename T>
void tree<T>::list_dir(node_tree<T> *director, const unsigned int depth) {
    // 打印当前节点
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << director->data << std::endl;

    // 如果有子节点，遍历所有子节点 (AI写的，来自地狱的力量)
    if (director->son != nullptr) {
        node_tree<T> **child = director->son->first();
        while (child != director->son->current()) {
            list_dir(*child, depth + 1);
            ++child;
        }
    }
}

template<typename T>
bool tree<T>::go_next(unsigned int index) {
    if (current_node_tree->son->feedback(index) == NULL) {
        std::cerr << "index is invalid" << std::endl;
        return false;
    }
    current_node_tree = current_node_tree->son->feedback(index);
    return true;
}

template<typename T>
void tree<T>::go_back() {
    current_node_tree = current_node_tree->father;
}
