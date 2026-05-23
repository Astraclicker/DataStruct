#pragma once

#include <array/array.h>

namespace astra {
    template<typename T, size_t N>
    struct b_tree_node {
        T data;

        array<b_tree_node<T, N>, N> *son_left;
        array<b_tree_node<T, N>, N> *son_right;
    };

    template<typename T, size_t N>
    class b_tree {
    protected:
        array<b_tree_node<T, N>, N> *root;

    public:
        //构造
        b_tree();

        //插入
        array<b_tree_node<T, N>, N> *push(T data, array<b_tree_node<T, N>, N> *column);

        void push(T data) {
            root = push(data, root);
        }
    };

    template<typename T, size_t N>
    b_tree<T, N>::b_tree() {
        root = new array<b_tree_node<T, N>, N>;
    }

    template<typename T, size_t N>
    array<b_tree_node<T, N>, N> *b_tree<T, N>::push(T data, array<b_tree_node<T, N>, N> *column) {
        //检查数组是否为空
        if (column->address() == column->curr()) {
            auto temp = new b_tree_node<T, N>;
            temp->data = data;
            temp->son_left = nullptr;
            temp->son_right = nullptr;
            column->push_back(*temp);
            return column;
        }
    }
}
