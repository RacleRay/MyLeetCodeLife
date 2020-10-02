//
// Created by Raclerrr on 2020/10/2.
//

#include <map>
#include <unordered_map>
#include <vector>
#include "heap.h"

using namespace racledomain;
using pii=pair<int, int>;

class Cmp {
public:
    // In heap, stored by value(frequence).
    bool operator()(const pii &a, const pii &b) { return a.first < b.first; }
};

vector<int> topKFrequent(const vector<int> &nums, int k) {
    // min heap
    priority_queue<pii, Cmp> pq;
    unordered_map<int, int> map;
    for (auto &num: nums) map[num]++;

    for (auto &item: map) {
        if (k > 0) {
            pq.push(make_pair(item.second, item.first));
            k--;
        } else if (item.second > pq.top().first) {  // top k
            pq.pop();
            pq.push(make_pair(item.second, item.first));
        }
    }

    vector<int> res;
    while (!pq.isempty()) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}

int main() {
    vector<int> nums = {
            5, 1, -1, -8, -7, 8, -5, 0, 1, 10, 8, 0, -4, 3, -1, -1, 4,
            -5, 4, -3, 0, 2, 2, 2, 4, -2, -4, 8, -7, -7, 2, -8, 0, -8,
            10, 8, -8, -2, -9, 4, -7, 6, 6, -1, 4, 2, 8, -3, 5, -9, -3,
            6, -8, -5, 5, 10, 2, -5, -1, -5, 1, -3, 7, 0, 8, -2, -3, -1,
            -5, 4, 7, -9, 0, 2, 10, 4, 4, -4, -1, -1, 6, -8, -9, -1, 9,
            -9, 3, 5, 1, 6, -1, -2, 4, 2, 4, -6, 4, 4, 5, -5};

    int k = 7;

    vector<int> res = topKFrequent(nums, k);
    for (auto elem : res) {
        cout << elem << " ";
    }
    cout << endl;

    map<int, int> m;
    m.insert(make_pair(1, 2));
    m.insert(make_pair(1, 3));
    cout << m[1] << endl;
    unordered_map<int, int> um;
    um.insert(make_pair(1, 2));
    um.insert(make_pair(1, 3));
    cout << um[1] << endl;
    return 0;
}