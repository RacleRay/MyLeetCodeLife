#include "../header.h"

class RandomizedSet {
    static array<int, 200010> nums;
    unordered_map<int, int> map;
    // random number generator
    int m_idx {-1};
    mt19937 random_generator;


public:
    RandomizedSet() = default;
    
    bool insert(int val) {
        if (map.count(val)) {
            return false;
        }
        nums[++m_idx] = val;
        map[val] = m_idx;
        return true;
    }
    
    bool remove(int val) {
        if (!map.count(val)) {
            return false;
        }
        int del_idx = map[val];

        // 保持 0 ~ m_idx 全部都存储着元素
        map[nums[m_idx]] = del_idx;
        nums[del_idx] = nums[m_idx];
        m_idx--;

        map.erase(val);
        return true;
    }
    
    int getRandom() {
        uniform_int_distribution<int> distribution(0, m_idx);
        return nums[distribution(random_generator)];
    }
};

array<int, 200010> RandomizedSet::nums = {0};


/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */