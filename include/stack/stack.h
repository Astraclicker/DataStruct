#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <linkedList/singlyLinkedList/singlyLinkedList.h>

namespace astra {
    /**
     * @brief 默认以单向链表实现的栈
     * @tparam T 对象类型
     * @tparam alloc 分配器类型
     */
    template<typename T, typename alloc =singlyLinkedList<T> >
    class stack {
    protected:
        alloc *container;

    public:
        //构造函数
        stack();

        //入栈
        void push(T data);

        //出栈
        void pop();

        //返回栈顶迭代器
        T top();

        //析构函数
        ~stack();
    };


    //构造函数
    template<typename T, typename alloc>
    stack<T, alloc>::stack() {
        container = new alloc;
    }

    //入栈
    template<typename T, typename alloc>
    void stack<T, alloc>::push(T data) {
        try {
            if (!container->push_head(data)) {
                std::__throw_runtime_error("out of range");
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
    }

    //出栈
    template<typename T, typename alloc>
    void stack<T, alloc>::pop() {
        try {
            if (!container->remove_head()) {
                std::__throw_runtime_error("the stack is empty");
            }
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
    }

    //返回栈顶元素迭代器
    template<typename T, typename alloc>
    T stack<T, alloc>::top() {
        return *container->curr();
    }

    //析构函数
    template<typename T, typename alloc>
    stack<T, alloc>::~stack() {
        delete container;
    }
}
