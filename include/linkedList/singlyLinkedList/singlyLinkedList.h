#pragma once

namespace astra {
    /**
     * @namespace astra
     * @brief 单向链表节点
     * @tparam T
     */
    template<typename T>
    struct nodeSinglyList {
        T data;
        nodeSinglyList *next;
    };

    /**
     * @namespace astra
     * @brief 单向链表链表
     * @tparam T
     */
    template<typename T>
    class singlyLinkedList {
    protected:
        nodeSinglyList<T> *head;
        nodeSinglyList<T> *final;

    public:
        //构造函数
        singlyLinkedList();

        explicit singlyLinkedList(T data);

        //删除单向链表
        void del_singlyLinkList(nodeSinglyList<T> *node);

        void del_singlyLinkList();

        //头插法
        bool push_head(T data);

        //尾插法
        void push_back(T data);

        //返回头指针
        nodeSinglyList<T> *first() { return head; }

        //析构函数
        ~singlyLinkedList();

        class iterator {
        public:
            nodeSinglyList<T> *node;

            explicit iterator(nodeSinglyList<T> *obj) : node(obj) {
            }

            iterator &operator ++() {
                if (node != nullptr) {
                    node = node->next;
                }
                return *this;
            }

            bool operator ==(const iterator &other) const {
                return node == other.node;
            }

            bool operator !=(const iterator &other) const {
                return node != other.node;
            }

            T &operator *() const {
                return node->data;
            }

            nodeSinglyList<T> *operator ->() const {
                return node;
            }
        };

        iterator begin() {
            return iterator(head);
        }

        iterator end() {
            return iterator(nullptr);
        }

        iterator curr() {
            return iterator(head);
        }

        //插入
        void insert(const iterator &it, T data);

        void insert(const nodeSinglyList<T> *node, T data);

        //删除
        void remove_after(const iterator &it);

        void remove_after(const nodeSinglyList<T> *node);

        bool remove_head();

        //查找
        iterator &find(T data, nodeSinglyList<T> *start);

        iterator &find(T data);
    };

    //单向链表构造函数
    template<typename T>
    singlyLinkedList<T>::singlyLinkedList() : head(nullptr), final(nullptr) {
    }

    template<typename T>
    singlyLinkedList<T>::singlyLinkedList(T data) {
        auto temp = new nodeSinglyList<T>;
        temp->data = data;
        temp->next = nullptr;
        head = temp;
        final = temp;
    }

    //删除单项链表
    template<typename T>
    void singlyLinkedList<T>::del_singlyLinkList(nodeSinglyList<T> *node) {
        if (node != nullptr) {
            del_singlyLinkList(node->next);
            delete(node);
        }
    }

    //删除单向链表无参数重载：从head递归删除
    template<typename T>
    void singlyLinkedList<T>::del_singlyLinkList() {
        del_singlyLinkList(head);
    }

    //单链表头插法
    template<typename T>
    bool singlyLinkedList<T>::push_head(T data) {
        if (head == nullptr) {
            auto temp = new nodeSinglyList<T>;
            temp->data = data;
            temp->next = nullptr;
            head = temp;
            final = temp;
        } else {
            auto temp = new nodeSinglyList<T>;
            temp->data = data;
            temp->next = head;
            head = temp;
        }
        return true;
    }

    //单链表尾插法
    template<typename T>
    void singlyLinkedList<T>::push_back(T data) {
        if (final == nullptr) {
            auto temp = new nodeSinglyList<T>;
            temp->data = data;
            temp->next = nullptr;
            head = temp;
            final = temp;
        } else {
            auto temp = new nodeSinglyList<T>;
            temp->data = data;
            temp->next = nullptr;
            final->next = temp;
            final = temp;
        }
    }

    //单向链表插入数据
    template<typename T>
    void singlyLinkedList<T>::insert(const iterator &it, T data) {
        if (it.node == nullptr) return;
        if (it.node == this->final) {
            push_back(data);
        }
        auto temp = new nodeSinglyList<T>;
        temp->data = data;
        temp->next = it.node->next;
        it.node->next = temp;
    }

    template<typename T>
    void singlyLinkedList<T>::insert(const nodeSinglyList<T> *node, T data) {
        if (node == nullptr)return;
        if (node == this->final) {
            push_back(data);
        }
        auto temp = new nodeSinglyList<T>;
        temp->data = data;
        temp->next = node->next;
        node->next = temp;
    }

    //单链表删除数据
    template<typename T>
    void singlyLinkedList<T>::remove_after(const iterator &it) {
        if (it.node == nullptr || it.node->next == nullptr) return;
        auto temp = it.node->next;
        it.node->next = temp->next;
        delete temp;
    }

    template<typename T>
    void singlyLinkedList<T>::remove_after(const nodeSinglyList<T> *node) {
        if (node == nullptr || node->next == nullptr) return;
        auto temp = node->next;
        node->next = temp->next;
        delete temp;
    }

    template<typename T>
    bool singlyLinkedList<T>::remove_head() {
        if (head == nullptr)return false;
        auto temp = head;
        delete head;
        head = temp->next;
        return true;
    }

    //单向链表析构函数
    template<typename T>
    singlyLinkedList<T>::~singlyLinkedList() {
        del_singlyLinkList(head);
    }

    //查找
    template<typename T>
    singlyLinkedList<T>::iterator &singlyLinkedList<T>::find(T data, nodeSinglyList<T> *start) {
        if (start->data == data) {
            return iterator(start);
        }
        if (start != nullptr) {
            return find(data, start->next);
        }
        return iterator(nullptr);
    }

    template<typename T>
    singlyLinkedList<T>::iterator &singlyLinkedList<T>::find(T data) {
        return find(data, head);
    }
}
