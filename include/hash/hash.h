//分离链接散列表
#pragma once
#include <iostream>
#include <forward_list>

template<typename T>
class hash {
protected:
    unsigned int table_size;
    std::forward_list<T> *table;

public:
    //构造
    hash(const unsigned int &length);

    //插入
    void insert_hash(const T &data);

    //查找
    std::forward_list<T>::iterator find_hash(T data);

    //删除
    bool del_hash(const T &data);

    //析构
    ~hash();
};

template<typename T>
hash<T>::hash(const unsigned int &length) : table_size(length) {
    table = new std::forward_list<T>[table_size + 1];
}

template<typename T>
void hash<T>::insert_hash(const T &data) {
    table[data % table_size].push_front(data);
}

template<typename T>
std::forward_list<T>::iterator hash<T>::find_hash(T data) {
    if (table[data % table_size].empty()) {
        std::cerr << "can't find" << std::endl;
        return table[data % table_size].end();
    }
    auto temp = table[data % table_size].begin();

    while (temp != table[data % table_size].end() && *temp != data) {
        ++temp;
    }
    if (temp == table[data % table_size].end()) {
        std::cerr << "can't find" << std::endl;
    }
    return temp;
}

template<typename T>
bool hash<T>::del_hash(const T &data) {
    auto &lst = table[data % table_size];
    if (lst.empty()) {
        std::cerr << "can't find" << std::endl;
        return false;
    }

    auto temp = lst.begin();

    while (temp != lst.end() && *temp != data) {
        ++temp;
    }

    if (temp == lst.end()) {
        return false;
    }

    if (temp == lst.begin()) {
        lst.pop_front();
        return true;
    } else {
        auto prev = lst.begin();
        auto next = prev++;
        while (next != temp) {
            ++prev;
            next = prev++;
        }
        lst.erase_after(prev);
        return true;
    }
}

template<typename T>
hash<T>::~hash() {
    delete [] table;
}
