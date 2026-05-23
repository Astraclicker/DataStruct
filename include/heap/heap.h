#pragma once
#include <iostream>

//堆节点
template<typename T>
struct heap_node {
    heap_node *father;
    T data;
    heap_node *son_left_heap;
    heap_node *son_right_heap;
};

//基类
template<typename T>
class heap {
protected:
    heap_node<T> *root = nullptr;
    heap_node<T> *end = nullptr;
    size_t count_heap = 0;

public:
    //插入
    void insert_heap(T data);
};

//继承类 小根堆
template<typename T>
class heap_tiny : public heap<T> {
public:
    //构造小根堆
    heap_tiny(T data);

    //从数组构造小根堆
    heap_tiny(T *array, T *end);

    //下滤
    void down_tiny(heap_node<T> *dir);

    //上滤
    void up_tiny(heap_node<T> *dir);

    //弹出root
    T pop_tiny();

    //返回排序后的数组
    T *sort_heap_tiny();
};

//继承类 大根堆
template<typename T>
class heap_large : public heap<T> {
public:
    //构造大根堆

    //从数组构造大根堆
    heap_large(T *array, T *end);
};

template<typename T>
void heap<T>::insert_heap(T data) {
    // 构造要插入的节点
    auto temp = new heap_node<T>;
    temp->data = data;
    temp->son_left_heap = nullptr;
    temp->son_right_heap = nullptr;
    count_heap++;

    // If this is the first node (shouldn't happen via insert, but handle it)
    if (count_heap == 1) {
        root = temp;
        temp->father = nullptr;
        end = temp;
        return;
    }

    // 获取count_heap的最高位所在位数
    unsigned int count_temp = count_heap;
    unsigned int height_bit = 0;
    while (count_temp > 1) {
        count_temp >>= 1;
        height_bit++;
    }
    // 获取count_heap的每一位
    count_temp = count_heap;
    bool *bits = new bool[height_bit];
    for (unsigned int i = 0; i < height_bit; i++) {
        bits[i] = count_temp & 1;
        count_temp >>= 1;
    }
    // 根据数组找到插入位置
    auto temp_node = this->root;
    for (int i = static_cast<int>(height_bit) - 1; i > 0; i--) {
        if (bits[i]) {
            temp_node = temp_node->son_right_heap;
        } else {
            temp_node = temp_node->son_left_heap;
        }
    }
    if (bits[0]) {
        temp_node->son_right_heap = temp;
    } else {
        temp_node->son_left_heap = temp;
    }
    temp->father = temp_node;
    this->end = temp;
    delete[] bits;
}

template<typename T>
heap_tiny<T>::heap_tiny(T data) {
    this->root = new heap_node<T>;
    this->root->father = nullptr;
    this->root->data = data;
    this->root->son_left_heap = nullptr;
    this->root->son_right_heap = nullptr;
    this->end = this->root;
    this->count_heap = 1;
}

template<typename T>
heap_tiny<T>::heap_tiny(T *array, T *end) {
    T *temp = array;
    this->root = new heap_node<T>;
    this->root->father = nullptr;
    this->root->data = *array;
    this->root->son_left_heap = nullptr;
    this->root->son_right_heap = nullptr;
    this->count_heap = 1;
    this->end = this->root;
    while (temp != end) {
        ++temp;
        this->insert_heap(*temp);
        this->up_tiny(this->end);
    }
}

template<typename T>
void heap_tiny<T>::down_tiny(heap_node<T> *dir) {
    if (dir != nullptr) {
        if (dir->son_left_heap != nullptr && dir->son_right_heap != nullptr) {
            auto min = dir->son_left_heap->data < dir->son_right_heap->data ? dir->son_left_heap : dir->son_right_heap;
            if (dir->data > min->data) {
                T temp = dir->data;

                dir->data = min->data;
                min->data = temp;
                down_tiny(min);
            }
        } else if (dir->son_left_heap != nullptr && dir->son_left_heap->data < dir->data) {
            T temp = dir->data;

            dir->data = dir->son_left_heap->data;
            dir->son_left_heap->data = temp;
            down_tiny(dir->son_left_heap);
        } else if (dir->son_right_heap != nullptr && dir->son_right_heap->data < dir->data) {
            T temp = dir->data;

            dir->data = dir->son_right_heap->data;
            dir->son_right_heap->data = temp;
            down_tiny(dir->son_right_heap);
        }
    }
}

template<typename T>
void heap_tiny<T>::up_tiny(heap_node<T> *dir) {
    if (dir != nullptr && dir->father != nullptr) {
        if (dir->data < dir->father->data) {
            T temp = dir->data;
            dir->data = dir->father->data;
            dir->father->data = temp;
            up_tiny(dir->father);
        }
    }
}

template<typename T>
T heap_tiny<T>::pop_tiny() {
    T temp = this->root->data;

    // 处理只有一个节点的情况
    if (this->count_heap == 1) {
        delete this->root;
        this->root = nullptr;
        this->end = nullptr;
        this->count_heap = 0;
        return temp;
    }

    // 清理
    if (this->end->father) {
        if (this->end->father->son_left_heap == this->end) {
            this->end->father->son_left_heap = nullptr;
        } else {
            this->end->father->son_right_heap = nullptr;
        }
    }

    this->root->data = this->end->data;
    delete this->end;
    this->end = nullptr;

    // 更新总节点数
    this->count_heap -= 1;

    // 查找新的end
    unsigned int count_temp = this->count_heap;
    unsigned int height_bit = 0;
    while (count_temp > 1) {
        count_temp >>= 1;
        height_bit++;
    }
    count_temp = this->count_heap;
    bool bits[height_bit];
    for (unsigned int i = 0; i < height_bit; i++) {
        bits[i] = count_temp & 1;
        count_temp >>= 1;
    }
    auto temp_node = this->root;
    for (int i = static_cast<int>(height_bit) - 1; i >= 0; i--) {
        if (bits[i]) {
            temp_node = temp_node->son_right_heap;
        } else {
            temp_node = temp_node->son_left_heap;
        }
    }

    this->end = temp_node;

    down_tiny(this->root);
    return temp;
}

template<typename T>
T *heap_tiny<T>::sort_heap_tiny() {
    const size_t size = this->count_heap;
    T *array = new T[size];

    for (size_t cnt = 0; cnt < size; cnt++) {
        array[cnt] = this->pop_tiny();
    }
    return array;
}
