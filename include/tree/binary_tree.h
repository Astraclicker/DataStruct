#pragma once
#include <iostream>


namespace astra {
    /**
     * @brief 二叉查找树节点
     * @tparam T 节点元素数据类型，必须有大于，小于，等于号的重载
     */
    template<typename T>
    struct binary_node {
        T data;
        binary_node *son_left;
        binary_node *son_right;
    };

    /**
     * @brief 二叉查找树
     * @tparam T 节点元素数据类型，必须有大于，小于，等于号的重载
     */
    template<typename T>
    class binary_tree {
    protected:
        binary_node<T> *root;

    public:
        //构造函数
        binary_tree() : root(nullptr) {
        }

        explicit binary_tree(T data) : root(new binary_node<T>{data, nullptr, nullptr}) {
        }

        //查找
        binary_node<T> *find(binary_node<T> *node, T data);

        //查找最大
        binary_node<T> *find_MAX(binary_node<T> *node);

        binary_node<T> *find_MAX() {
            return find_MAX(root);
        }

        //查找最小
        binary_node<T> *find_MIN(binary_node<T> *node);

        binary_node<T> *find_MIN() {
            return find_MIN(root);
        }

        //从node开始插入data
        binary_node<T> *insert(binary_node<T> *node, T data);

        void insert(T data) {
            root = insert(root, data);
        }

        //从node节点开始删除data
        binary_node<T> *del(binary_node<T> *node, T data);

        void del(T data) {
            root = del(root, data);
        }

        //先序遍历
        void pre_order_traversal(binary_node<T> *node);

        void pre_order_traversal() {
            pre_order_traversal(root);
        }

        //中序遍历
        void in_order_traversal(binary_node<T> *node);

        void in_order_traversal() {
            in_order_traversal(root);
        }

        //后序遍历
        void post_order_traversal(binary_node<T> *node);

        void post_order_traversal() {
            post_order_traversal(root);
        }
    };


    //查找
    template<typename T>
    binary_node<T> *binary_tree<T>::find(binary_node<T> *node, T data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data == node->data) {
            return node;
        }
        if (data < node->data) {
            return find(node->son_left, data);
        }
        if (data > node->data) {
            return find(node->son_right, data);
        }
        return node;
    }

    //查找最大
    template<typename T>
    binary_node<T> *binary_tree<T>::find_MAX(binary_node<T> *node) {
        auto temp = node;
        if (temp == nullptr) {
            return nullptr;
        }
        while (temp->son_right != nullptr) {
            temp = temp->son_right;
        }
        return temp;
    }

    //查找最小
    template<typename T>
    binary_node<T> *binary_tree<T>::find_MIN(binary_node<T> *node) {
        auto temp = node;
        if (temp == nullptr) {
            return nullptr;
        }
        while (temp->son_left != nullptr) {
            temp = temp->son_left;
        }
        return temp;
    }

    //插入
    template<typename T>
    binary_node<T> *binary_tree<T>::insert(binary_node<T> *node, T data) {
        if (node == nullptr) {
            return new binary_node<T>{data, nullptr, nullptr};
        }
        if (data < node->data) {
            node->son_left = insert(node->son_left, data);
        }
        if (data > node->data) {
            node->son_right = insert(node->son_right, data);
        }
        if (data == node->data) {
            return node;
        }
        return node;
    }

    //删除
    template<typename T>
    binary_node<T> *binary_tree<T>::del(binary_node<T> *node, T data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (data < node->data) {
            node->son_left = del(node->son_left, data);
        }
        if (data > node->data) {
            node->son_right = del(node->son_right, data);
        }
        if (data == node->data) {
            //左右孩子均为nullptr
            if (node->son_left == nullptr && node->son_right == nullptr) {
                auto temp = node;
                delete node;
                temp = nullptr;
                return temp;
            }

            //左孩子为nullptr
            if (node->son_left == nullptr && node->son_right != nullptr) {
                auto temp = node->son_right;
                delete node;
                return temp;
            }
            //右孩子为nullptr
            if (node->son_left != nullptr && node->son_right == nullptr) {
                auto temp = node->son_left;
                delete node;
                return temp;
            }

            //左右孩子均不为nullptr
            if (node->son_left != nullptr && node->son_right != nullptr) {
                auto new_root = find_MAX(node->son_left);
                auto temp = node->son_left;
                new_root->son_right = node->son_right;
                delete node;
                return temp;
            }
        }
        return node;
    }

    //先序遍历
    //对于每一个节点，进行中，左，右的顺序递归遍历
    template<typename T>
    void binary_tree<T>::pre_order_traversal(binary_node<T> *node) {
        if (node != nullptr) {
            std::cout << node->data << std::endl;
            pre_order_traversal(node->son_left);
            pre_order_traversal(node->son_right);
        }
    }

    //中序遍历
    //对于每一个节点，进行左，中，右的顺序递归遍历
    template<typename T>
    void binary_tree<T>::in_order_traversal(binary_node<T> *node) {
        if (node != nullptr) {
            in_order_traversal(node->son_left);
            std::cout << node->data << std::endl;
            in_order_traversal(node->son_right);
        }
    }

    //后序遍历
    //对于每一个节点，进行左，右，中的顺序递归遍历
    template<typename T>
    void binary_tree<T>::post_order_traversal(binary_node<T> *node) {
        if (node != nullptr) {
            post_order_traversal(node->son_left);
            post_order_traversal(node->son_right);
            std::cout << node->data << std::endl;
        }
    }
}
