#pragma once

namespace astra {
    template<typename T>
    struct nodeList {
        nodeList *least;
        T data;
        nodeList *next;
    };

    template<typename T>
    class list {
    protected:
        nodeList<T> *head;
        nodeList<T> *final;

    public:
        //构造函数
        list();

        explicit list(T data);

        //删除链表
        void del_list(nodeList<T> *node);

        void del_list();

        //头插法
        void push_head(T data);

        //尾插法
        void push_back(T data);

        //迭代器实现
        class iterator {
        public:
            nodeList<T> *node;
            //构造函数
            explicit iterator(nodeList<T> *obj) : node(obj) {
            }

            //重载前置++运算符
            iterator &operator++() {
                if (node != nullptr) {
                    node = node->next;
                }
                return *this;
            }

            //重载前置--运算符
            iterator &operator--() {
                if (node != nullptr) {
                    node = node->least;
                }
                return *this;
            }

            //重载==运算符
            bool operator==(const iterator &other) const {
                return node = other.node;
            }

            //重载!=运算符
            bool operator !=(const iterator &other) const {
                return node != other.node;
            }

            //重载*运算符
            T &operator*() {
                return node->data;
            }
        };

        //返回头迭代器
        iterator begin() const {
            return iterator(head);
        }

        //返回尾迭代器（nullptr）
        iterator end() const {
            return iterator(nullptr);
        }

        //插入节点
        void insert(const iterator &it, T data);

        void insert(const nodeList<T> *node, T data);


        //移除节点
        void remove(const iterator &it);

        void remove(const nodeList<T> *node);

        //移除头节点
        void remove_head();

        //移除尾节点
        void remove_final();

        //查找元素,返回迭代器
        iterator find(T data, nodeList<T> *strat);

        iterator find(T data);

        //析构函数
        ~list();
    };

    //构造函数
    template<typename T>
    list<T>::list() {
        head = nullptr;
        final = nullptr;
    }

    template<typename T>
    list<T>::list(T data) {
        auto temp = new nodeList<T>;
        temp->data = data;
        temp->least = nullptr;
        temp->next = nullptr;

        head = temp;
        final = temp;
    }

    //删除链表
    template<typename T>
    void list<T>::del_list(nodeList<T> *node) {
        if (node != nullptr) {
            del_list(node->next);
            delete node;
        }
    }

    template<typename T>
    void list<T>::del_list() {
        del_list(head);
    }

    //头插法
    template<typename T>
    void list<T>::push_head(T data) {
        if (head == nullptr) {
            auto temp = new nodeList<T>;
            temp->data = data;
            temp->least = nullptr;
            temp->next = nullptr;

            head = temp;
            final = temp;
            return;
        }
        auto temp = new nodeList<T>;
        temp->data = data;

        temp->next = head;
        temp->least = nullptr;

        head->least = temp;
        head = temp;
    }

    //尾插法
    template<typename T>
    void list<T>::push_back(T data) {
        if (final == nullptr) {
            auto temp = new nodeList<T>;
            temp->data = data;
            temp->least = nullptr;
            temp->next = nullptr;

            head = temp;
            final = temp;
            return;
        }
        auto temp = new nodeList<T>;
        temp->data = data;

        temp->next = nullptr;
        temp->least = final;

        final->next = temp;
        final = temp;
    }

    //插入节点
    template<typename T>
    void list<T>::insert(const iterator &it, T data) {
        if (it.node == nullptr)return;
        if (it.node == final) {
            push_back(data);
            return;
        }
        auto temp = new nodeList<T>;
        temp->data = data;

        temp->least = it.node;
        temp->next = it.node->next;

        it.node->next->least = temp;
        it.node->next = temp;
    }

    template<typename T>
    void list<T>::insert(const nodeList<T> *node, T data) {
        if (node == nullptr)return;
        if (node == final) {
            push_back(data);
            return;
        }
        auto temp = new nodeList<T>;
        temp->data = data;

        temp->least = node;
        temp->next = node->next;

        node->next->least = temp;
        node->next = temp;
    }

    //移除节点
    template<typename T>
    void list<T>::remove(const iterator &it) {
        if (it.node == nullptr)return;
        if (it.node == head) {
            remove_head();
            return;
        }
        if (it.node == final) {
            remove_final();
            return;
        }
        it.node->least->next = it.node->next;
        it.node->next->least = it.node->least;
        delete it.node;
    }

    template<typename T>
    void list<T>::remove(const nodeList<T> *node) {
        if (node == nullptr) return;
        if (node == head) {
            remove_head();
            return;
        }
        if (node == final) {
            remove_final();
            return;
        }
        node->least->next = node->next;
        node->next->least = node->least;
        delete node;
    }

    //移除头节点
    template<typename T>
    void list<T>::remove_head() {
        if (head == final) {
            delete head;
            head = nullptr;
            return;
        }
        auto temp = head;
        head = head->next;
        delete temp;

        head->least = nullptr;
    }

    //移除尾节点
    template<typename T>
    void list<T>::remove_final() {
        if (head == final) {
            delete final;
            final = nullptr;
            return;
        }
        auto temp = final;
        final = final->least;
        delete temp;
        final->next = nullptr;
    }

    //查找元素,返回迭代器
    template<typename T>
    list<T>::iterator list<T>::find(T data, nodeList<T> *strat) {
        if (strat->data == data) {
            return iterator(strat);
        }
        if (strat != nullptr) {
            return find(data, strat->next);
        }
        return iterator(nullptr);
    }

    template<typename T>
    list<T>::iterator list<T>::find(T data) {
        return find(data, head);
    }

    //析构链表
    template<typename T>
    list<T>::~list() {
        del_list(head);
    }
}
