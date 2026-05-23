#pragma once
#include <linkedList/singlyLinkedList/singlyLinkedList.h>
#include <stdexcept>
#include <iostream>

namespace astra {
    /**
     * @brief 单向队列，基于单向链表
     * @tparam T 数据类型
     */
    template<typename T>
    class queue {
    protected:
        singlyLinkedList<T> *container;

    public:
        //构造函数
        queue();

        //入队
        void push(T data);

        //出队
        void pop();

        //返回队首元素迭代器
        T top();

        //析构函数
        ~queue();
    };

    template<typename T>
    queue<T>::queue() {
        container = new singlyLinkedList<T>;
    }

    //入队
    template<typename T>
    void queue<T>::push(T data) {
        container->push_back(data);
    }

    //出队
    template<typename T>
    void queue<T>::pop() {
        try {
            if (!container->remove_head()) {
                std::__throw_runtime_error("the queue is empty");
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
    }

    //返回队首元素迭代器
    template<typename T>
    T queue<T>::top() {
        return *container->curr();
    }

    //析构
    template<typename T>
    queue<T>::~queue() {
        delete container;
    }
}
