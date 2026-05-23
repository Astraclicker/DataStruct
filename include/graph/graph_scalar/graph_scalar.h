#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <functional>

//无向图基类
template<typename T>
class graph_scalar {
protected:
    size_t size = 0;
    std::vector<bool> visited;

public:
    //虚函数：析构
    virtual ~graph_scalar() = default;
};

//无向图邻接矩阵实现
template<typename T>
class graph_scalar_matrix : public graph_scalar<T> {
protected:
    std::vector<std::optional<T> > matrix_value;
    std::vector<std::vector<unsigned int> > matrix_link;

public:
    //初始化邻接矩阵无向图
    graph_scalar_matrix(size_t size);

    //对无向图 邻接矩阵对象 添加元素
    bool add_matrix(size_t index, T data);

    //链接两个元素，并赋权
    void link_matrix(size_t index_x, size_t index_y, int value);

    //基于无向图邻接矩阵的最小生成树
    graph_scalar_matrix make_min_tree_matrix(bool condition);

    //无向图 邻接矩阵对象 深度优先搜索（以index为起点，搜索target）
    bool dfs_scalar_matrix(size_t index, T target);

    //无向图 邻接矩阵对象 广度优先搜索（以index为起点，搜索target）
    bool bfs_scalar_matrix(size_t index, T target);

    //虚函数 ：析构无向图 邻接矩阵
    ~graph_scalar_matrix() override;
};

//初始化邻接矩阵无向图
template<typename T>
graph_scalar_matrix<T>::graph_scalar_matrix(size_t size) {
    this->visited = std::vector<bool>(size, false);
    this->size = size;
    matrix_value = std::vector<std::optional<T> >(size, std::nullopt);
    matrix_link = std::vector<std::vector<unsigned int> >(size, std::vector<unsigned int>(size, 0));
}

//对无向图 邻接矩阵对象 添加元素
template<typename T>
bool graph_scalar_matrix<T>::add_matrix(size_t index, T data) {
    if (matrix_value[index].has_value()) {
        return false;
    }
    matrix_value[index] = data;
    return true;
}

//链接两个元素，并赋权
template<typename T>
void graph_scalar_matrix<T>::link_matrix(size_t index_x, size_t index_y, int value) {
    if (index_x < matrix_value.size() && index_y < matrix_value.size()) {
        matrix_link[index_x][index_y] = value;
        matrix_link[index_y][index_x] = value;
    } else {
        std::cerr << "Index out of range" << std::endl;
    }
}

/**
 * @brief 基于无向图邻接矩阵的最小生成树
 * @tparam T
 * @param condition:如果为true，则使用prim算法，否则使用kruskal算法
 * @return graph_scalar_matrix<T> :返回最小生成树的邻接矩阵对象
*/
template<typename T>
graph_scalar_matrix<T> graph_scalar_matrix<T>::make_min_tree_matrix(bool condition) {
    //创建结果矩阵
    graph_scalar_matrix<T> result(matrix_value.size());
    //记录最小权值
    size_t min_cnt = ULONG_LONG_MAX;
    //记录最小权值的元素
    size_t min_index_x = 0;
    size_t min_index_y = 0;
    //记录已添加元素个数
    size_t added_count = 0;
    //记录有效元素个数
    size_t valid_count = 0;
    for (size_t i = 0; i < matrix_value.size(); ++i) {
        if (matrix_value[i].has_value()) {
            valid_count++;
        }
    }
    //查找第一个有效元素
    for (size_t i = 0; i < matrix_value.size(); ++i) {
        if (matrix_value[i].has_value()) {
            result.add_matrix(i, *matrix_value[i]);
            this->visited[i] = true;
            added_count++;
            break;
        }
    }

    if (condition) {
        //prim算法
        while (added_count < valid_count) {
            // 每次重置
            min_cnt = ULONG_LONG_MAX;
            min_index_x = 0;
            min_index_y = 0;

            for (size_t i = 0; i < matrix_value.size(); i++) {
                if (this->visited[i]) {
                    // 从已访问节点出发找最小边
                    for (size_t j = 0; j < matrix_value.size(); j++) {
                        if (!this->visited[j] && matrix_link[i][j] != 0 && matrix_link[i][j] < min_cnt) {
                            min_cnt = matrix_link[i][j];
                            min_index_x = j;
                            min_index_y = i;
                        }
                    }
                }
            }
            if (min_cnt == ULONG_LONG_MAX) break; // 无法找到更多边
            this->visited[min_index_x] = true; // 更新访问状态
            result.add_matrix(min_index_x, *matrix_value[min_index_x]);
            // 复制边权重到result

            result.matrix_link[min_index_x][min_index_y] = min_cnt;
            result.matrix_link[min_index_y][min_index_x] = min_cnt;

            added_count++;
        }
    } else {
        //kruskal算法
    }
    //重置visited
    this->visited = std::vector<bool>(matrix_value.size(), false);
    return result;
}

//无向图 邻接矩阵对象 深度优先搜索
template<typename T>
bool graph_scalar_matrix<T>::dfs_scalar_matrix(size_t index, T target) {
    this->visited[index] = true;
    for (size_t i = 0; i < matrix_value.size(); i++) {
        if (matrix_link[index][i] == 0) {
            continue;
        }
        if (*matrix_value[i] == target) {
            this->visited = std::vector<bool>(matrix_value.size(), false);
            return true;
        }
        if (!this->visited[i] && dfs_scalar_matrix(i, target)) {
            return true;
        }
    }
    return false;
}

//无向图 邻接矩阵对象 广度优先搜索
template<typename T>
bool graph_scalar_matrix<T>::bfs_scalar_matrix(size_t index, T target) {
}

//虚函数 ：析构无向图 邻接矩阵
template<typename T>
graph_scalar_matrix<T>::~graph_scalar_matrix() {
}

//无向图邻接表实现
template<typename T>
class graph_scalar_table : public graph_scalar<T> {
protected:
    std::vector<std::optional<T> > *table_value;
    std::vector<std::forward_list<std::pair<size_t, int> > > *table_link;

public:
    //初始化邻接表无向图
    graph_scalar_table(size_t size);

    //对无向图 邻接表对象 添加元素
    bool add_table(size_t index, T data);

    //链接两个元素并赋权
    void link_table(size_t index_x, size_t index_y, int value);

    //基于无向图邻接表的最小生成树
    graph_scalar_table make_min_tree_table(bool condition);

    //虚函数 ：析构无向图 邻接表
    ~graph_scalar_table() override;
};

//初始化邻接表无向图
template<typename T>
graph_scalar_table<T>::graph_scalar_table(size_t size) {
    table_value = new std::vector<std::optional<T> >(size, std::nullopt);
    table_link = new std::vector<std::forward_list<std::pair<size_t, int> > >(
        size, std::forward_list<std::pair<size_t, int> >());
}

//对无向图 邻接表对象 添加元素
template<typename T>
bool graph_scalar_table<T>::add_table(size_t index, T data) {
    if ((*table_value)[index].has_value()) {
        return false;
    }
    (*table_value)[index] = data;
    return true;
}

//链接两个元素并赋权
template<typename T>
void graph_scalar_table<T>::link_table(size_t index_x, size_t index_y, int value) {
    if (index_x < table_value->size() && index_y < table_value->size()) {
        table_link->at(index_x).emplace_front(index_y, value);
        table_link->at(index_y).emplace_front(index_x, value);
    } else {
        std::cerr << "Index out of range" << std::endl;
    }
}

//基于无向图邻接表的最小生成树
template<typename T>
graph_scalar_table<T> graph_scalar_table<T>::make_min_tree_table(bool condition) {
    // TODO 最小生成树算法 无向图 邻接表
    if (condition) {
        //prim算法
    } else {
        //kruskal算法
    }
}

template<typename T>
graph_scalar_table<T>::~graph_scalar_table() {
    delete table_value;
    delete table_link;
}
