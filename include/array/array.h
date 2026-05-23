#pragma once

namespace astra {
    /**
     * @namespace astra
     * @brief 数组
     * @tparam T
     */
    using size_t = unsigned long long;

    template<typename T, const size_t>
    class array {
    protected:
        T *head;
        T *final;
        T *current;

    public:
        //构造函数
        array();

        //返回下标所在的元素引用
        T &at(size_t index);

        //返回数组指针
        T *address() { return head; }

        T *curr() { return current; }

        //提供push_back方法
        bool push_back(T data);

        //提供remove_head方法
        bool remove_head();

        //返回数组长度
        static size_t size();

        //返回已用数组长度(仅支持使用push_back方法插入的数组)
        size_t current_length() const { return current - head; }

        //重载[]运算符
        T &operator[](size_t index) {
            return head[index];
        }

        //迭代器
        class iterator {
        public:
            T *data;
            //构造
            explicit iterator(T *data) {
                this->data = data;
            }

            //重载前置--运算符
            iterator &operator--() {
                --data;
                return *this;
            }

            //重载前置++运算符
            iterator &operator++() {
                ++data;
                return *this;
            }

            //重载*运算符
            T &operator*() {
                return *this->data;
            }

            //重载==运算符
            bool operator==(const iterator &other) const {
                return other.data == this->data;
            }

            //重载!=运算符
            bool operator!=(const iterator &other) const {
                return other.data != this->data;
            }
        };

        iterator begin() {
            return iterator(head);
        }

        iterator end() {
            return iterator(final);
        }

        //析构数组
        ~array();
    };

    //构造数组
    template<typename T, size_t length>
    array<T, length>::array() {
        head = new T [length + 1];
        final = &head[length];
        current = head;
    }

    //返回下标所在的元素引用
    template<typename T, size_t length>
    T &array<T, length>::at(size_t index) {
        return head[index];
    }

    //push_back方法
    template<typename T, size_t length>
    bool array<T, length>::push_back(T data) {
        if (current == final) return false;

        *current = data;
        ++current;
        return true;
    }


    //remove_head方法
    template<typename T, size_t length>
    bool array<T, length>::remove_head() {
        if (current == head) return false;

        --current;
        return true;
    }

    //返回数组长度
    template<typename T, size_t length>
    size_t array<T, length>::size() {
        return length;
    }

    //析构数组
    template<typename T, size_t length>
    array<T, length>::~array() {
        delete[] head;
    }
}
