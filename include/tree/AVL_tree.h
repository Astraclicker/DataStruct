#pragma once
#include <iostream>

namespace astra {
    /**
     * @brief avl树节点
     * @tparam T 节点元素数据类型，必须有大于，小于，等于号的重载
     */
    template<typename T>
    struct avl_tree_node {
        T data;
        avl_tree_node *son_left;
        avl_tree_node *son_right;
        int height;
    };

    /**
     * @brief 平衡二叉搜索树
     * @tparam T 节点元素数据类型，必须有大于，小于，等于号的重载
     */
    template<typename T>
    class avl_tree {
    protected:
        avl_tree_node<T> *root;

    public:
        //构造函数
        avl_tree() : root(nullptr) {
        }

        explicit avl_tree(T data) : root(new avl_tree_node<T>{data, nullptr, nullptr, 1}) {
        }

        //返回树高
        static int get_tree_height(avl_tree_node<T> *node);

        //返回平衡因子
        int get_balance(avl_tree_node<T> *node);

        //返回最大值
        static int max(const int x, const int y) {
            return x > y ? x : y;
        }

        //左旋
        avl_tree_node<T> *left_rotate(avl_tree_node<T> *node);

        //右旋
        avl_tree_node<T> *right_rotate(avl_tree_node<T> *node);

        //插入
        avl_tree_node<T> *insert(avl_tree_node<T> *node, T data);

        void insert(T data);

        //查找
        avl_tree_node<T> *find(avl_tree_node<T> *node, T data);

        avl_tree_node<T> *find(T data) {
            return find(root, data);
        }

        //查找node下最大元素
        static avl_tree_node<T> *find_MAX(avl_tree_node<T> *node);

        avl_tree_node<T> *find_MAX() {
            return find_MAX(root);
        }

        //查找node下最小元素
        static avl_tree_node<T> *find_MIN(avl_tree_node<T> *node);

        avl_tree_node<T> *find_MIN() {
            return find_MIN(root);
        }

        //删除
        avl_tree_node<T> *del(avl_tree_node<T> *node, T data);

        //先序遍历
        void pre_order_traversal(avl_tree_node<T> *node);

        void pre_order_traversal() {
            pre_order_traversal(root);
        }

        //中序遍历
        void in_order_traversal(avl_tree_node<T> *node);

        void in_order_traversal() {
            in_order_traversal(root);
        }

        //后序遍历
        void post_order_traversal(avl_tree_node<T> *node);

        void post_order_traversal() {
            post_order_traversal(root);
        }
    };


    //返回树高
    template<typename T>
    int avl_tree<T>::get_tree_height(avl_tree_node<T> *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    //返回平衡因子
    template<typename T>
    int avl_tree<T>::get_balance(avl_tree_node<T> *node) {
        return get_tree_height(node->son_left) - get_tree_height(node->son_right);
    }

    //左旋
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::left_rotate(avl_tree_node<T> *node) {
        if (node == nullptr || node->son_right == nullptr) {
            return node;
        }
        auto new_root = node->son_right;

        node->son_right = new_root->son_left;
        new_root->son_left = node;

        node->height = max(get_tree_height(node->son_left), get_tree_height(node->son_right)) + 1;
        new_root->height = max(get_tree_height(new_root->son_left), get_tree_height(new_root->son_right)) + 1;

        return new_root;
    }

    //右旋
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::right_rotate(avl_tree_node<T> *node) {
        if (node == nullptr || node->son_left == nullptr) {
            return node;
        }

        auto new_root = node->son_left;

        node->son_left = new_root->son_right;
        new_root->son_right = node;

        node->height = max(get_tree_height(node->son_left), get_tree_height(node->son_right)) + 1;
        new_root->height = max(get_tree_height(new_root->son_left), get_tree_height(new_root->son_right)) + 1;
        return new_root;
    }

    //插入
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::insert(avl_tree_node<T> *node, T data) {
        if (node == nullptr) {
            return new avl_tree_node<T>{data, nullptr, nullptr, 1};
        }
        if (data < node->data) {
            node->son_left = insert(node->son_left, data);
        } else if (data > node->data) {
            node->son_right = insert(node->son_right, data);
        } else {
            return node;
        }
        //更新树高
        node->height = max(get_tree_height(node->son_left), get_tree_height(node->son_right)) + 1;

        //LL型失衡
        if (get_balance(node) > 1 && get_balance(node->son_left) > 0) {
            return right_rotate(node);
        }

        //LR型失衡
        if (get_balance(node) > 1 && get_balance(node->son_left) < 0) {
            node->son_left = left_rotate(node->son_left);
            return right_rotate(node);
        }

        //RR型失衡
        if (get_balance(node) < -1 && get_balance(node->son_right) < 0) {
            return left_rotate(node);
        }

        //RL型失衡
        if (get_balance(node) < -1 && get_balance(node->son_right) > 0) {
            node->son_right = right_rotate(node->son_right);
            return left_rotate(node);
        }

        return node;
    }

    template<typename T>
    void avl_tree<T>::insert(T data) {
        root = insert(root, data);
    }

    //查找节点
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::find(avl_tree_node<T> *node, T data) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->data == data) {
            return node;
        }

        if (data < node->data) {
            return find(node->son_left, data);
        }
        if (data > node->data) {
            return find(node->son_right, data);
        }
        return nullptr;
    }

    //查找最大节点
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::find_MAX(avl_tree_node<T> *node) {
        auto temp = node;
        if (temp == nullptr) {
            return nullptr;
        }
        while (temp->son_right != nullptr) {
            temp = temp->son_right;
        }
        return temp;
    }

    //查找最小节点
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::find_MIN(avl_tree_node<T> *node) {
        auto temp = node;
        if (temp == nullptr) {
            return nullptr;
        }
        while (temp->son_left != nullptr) {
            temp = temp->son_left;
        }
        return temp;
    }

    //删除节点
    template<typename T>
    avl_tree_node<T> *avl_tree<T>::del(avl_tree_node<T> *node, T data) {
        //执行删除操作
        if (node == nullptr) {
            return nullptr;
        }
        if (data < node->data) {
            node->son_left = del(node->son_left, data);
            return node;
        }
        if (data > node->data) {
            node->son_right = del(node->son_right, data);
            return node;
        }
        if (data == node->data) {
            if (node->son_left == nullptr && node->son_right == nullptr) {
                auto temp = node;
                delete node;
                temp = nullptr;
                return temp;
            }
            if (node->son_right == nullptr && node->son_left != nullptr) {
                auto temp = node->son_left;
                delete node;
                return temp;
            }
            if (node->son_right != nullptr && node->son_left == nullptr) {
                auto temp = node->son_right;
                delete node;
                return temp;
            }
            if (node->son_left != nullptr && node->son_right != nullptr) {
                auto new_root = find_MAX(node->son_left);
                auto temp = node->son_left;
                new_root->son_right = node->son_right;
                delete node;
                return temp;
            }
        }

        //更新树高
        node->height = max(get_tree_height(node->son_left), get_tree_height(node->son_right)) + 1;

        //LL型失衡
        if (get_balance(node) > 1 && get_balance(node->son_left) >= 0) {
            return right_rotate(node);
        }

        //LR型失衡
        if (get_balance(node) > 1 && get_balance(node->son_left) < 0) {
            node->son_left = left_rotate(node->son_left);
            return right_rotate(node);
        }

        //RR型失衡
        if (get_balance(node) < -1 && get_balance(node->son_right) <= 0) {
            return left_rotate(node);
        }

        //RL型失衡
        if (get_balance(node) < -1 && get_balance(node->son_right) > 0) {
            node->son_right = right_rotate(node->son_right);
            return left_rotate(node);
        }
        return node;
    }

    //先序遍历
    //对于每一个节点，进行中，左，右的顺序递归遍历
    template<typename T>
    void avl_tree<T>::pre_order_traversal(avl_tree_node<T> *node) {
        if (node != nullptr) {
            std::cout << node->data << std::endl;
            pre_order_traversal(node->son_left);
            pre_order_traversal(node->son_right);
        }
    }

    //中序遍历
    //对于每一个节点，进行左，中，右的顺序递归遍历
    template<typename T>
    void avl_tree<T>::in_order_traversal(avl_tree_node<T> *node) {
        if (node != nullptr) {
            in_order_traversal(node->son_left);
            std::cout << node->data << std::endl;
            in_order_traversal(node->son_right);
        }
    }

    //后序遍历
    //对于每一个节点，进行左，右，中的顺序递归遍历
    template<typename T>
    void avl_tree<T>::post_order_traversal(avl_tree_node<T> *node) {
        if (node != nullptr) {
            post_order_traversal(node->son_left);
            post_order_traversal(node->son_right);
            std::cout << node->data << std::endl;
        }
    }
}
