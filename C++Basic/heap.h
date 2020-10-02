//
// Created by Raclerrr on 2020/10/1.
//

#ifndef IMPLEMENTATION_HEAP_H
#define IMPLEMENTATION_HEAP_H

#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

namespace racledomain {
    template<typename T, typename Cmp=std::less<T>>
    class Heap {
    private:
        vector<T> data_;
        Cmp cmp;

    public:
        Heap() {}

        Heap(const int capacity) { data_ = vector<T>(capacity); }

        // heapify from a vector
        Heap(vector<T>
        & vec){
            data_ = vec;
            T last_not_leaf = getParent(data_.size() - 1);
            while (last_not_leaf >= 0) {
                siftDown(last_not_leaf);
                last_not_leaf--;
            }
        }

        void heapSort(vector<int> &vec) {
            while (data_.size() > 0) {
                vec.push_back(top());
                pop();
            }
        };

        void siftDown(int idx) {
            int leftChild = getLeftChild(idx);
            while (leftChild < data_.size()) {
                int maxChild = leftChild;
                if (leftChild + 1 < data_.size() && cmp(data_[leftChild + 1], data_[leftChild]))
                    maxChild = leftChild + 1;
                if (cmp(data_[idx], data_[maxChild])) break;  // parent is smaller, can`t down more
                swap(idx, maxChild);  // parent is bigger
                idx = maxChild;  // tracking the element
                leftChild = getLeftChild(idx);  // next loop
            }
        };

        void siftUp(int idx) {
            while (idx > 0 && cmp(data_[idx], data_[getParent(idx)])) {  // parent is bigger
                int pid = getParent(idx);
                swap(idx, pid);
                idx = pid;  // tracking the element
            }
        };

        void push(T element) {
            data_.push_back(element);
            siftUp(data_.size() - 1);
        };

        void pop() {
            swap(0, data_.size() - 1);
            data_.pop_back();
            siftDown(0);
        };

        void swap(int i, int j) {
            T tmp = data_[i];
            data_[i] = data_[j];
            data_[j] = tmp;
        };

        int getParent(int idx) { return (idx - 1) / 2; };

        int getLeftChild(int idx) { return 2 * idx + 1; };

        int getRightChild(int idx) { return 2 * idx + 2; };

        void getData(vector <T> &data) { data = data_; };

        int getSize() { return data_.size(); };

        T top() { return data_[0]; };

        bool isempty() { return data_.empty(); };
    };


    template<typename T, typename Cmp=std::less<T>>
    class priority_queue {
    private:
        Heap <T, Cmp> heap;
    public:
        priority_queue() {};

        int getSize() { return heap.getSize(); };

        void push(T value) { heap.push(value); };

        T top() { return heap.top(); };

        void pop() { heap.pop(); }

        bool isempty() { return heap.isempty(); }
    };
}


#endif //IMPLEMENTATION_HEAP_H
