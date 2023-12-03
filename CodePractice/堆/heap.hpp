#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>


using namespace std;

template <typename T, typename Cmp = std::less<T>>
class Heap {
private:
    vector<T> data_;
    Cmp cmp;

public:
    Heap() {};
    
    Heap(T capacity) {data_ = vector<T>(capacity);}

    // construct a heap
    // Note: the start index is what (0 or 1).
    Heap(vector<T>& heap) {
        data_ = heap;
        T last_not_leaf = _getParent(data_.size() - 1);
        while (last_not_leaf >= 0) {
            _siftDown(last_not_leaf);
            --last_not_leaf;
        } 
    }

    void _siftDown(size_t idx);
    void _siftUp(size_t idx);

    T _getParent(size_t idx);
    T _getLeftChild(size_t idx);
    T _getRightChild(size_t idx);

    void _swap(size_t idx1, size_t idx2);

    void push(T val);
    void pop();
    void top();

    void heapSort(vector<int>& nums);

    vector<T> getData(vector<T>& data);
    size_t getSize();
    bool empty();
};

template <typename T, typename Cmp>
void  Heap<T, Cmp>::_siftDown(size_t idx) {
    size_t child = _getLeftChild(idx);
    while (child < data_.size()) {
        child = _getLeftChild(idx);
        // 完全二叉树
        if (child + 1 < data_.size() && \
            cmp(data_[child + 1], data_[child]))
            child = _getRightChild(idx);
        if (cmp(data_[idx], data_[child])) break;
        _swap(idx, child);
        idx = child;
    }
}

template <typename T, typename Cmp>
void  Heap<T, Cmp>::_siftUp(size_t idx) {
    size_t pi = _getParent(idx);
    while (idx > 0 && cmp(data_[idx], pi)) {
        pi = _getParent(idx);
        swap(idx, pi);
        idx = pi;
    }
}

