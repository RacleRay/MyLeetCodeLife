#include "../header.h"


class Solution {
    vector<int> origin;

public:
    Solution(vector<int>& nums): origin(std::move(nums)) {}
    
    vector<int> reset() {
        return origin;
    }
    
    vector<int> shuffle() {
        if (origin.empty()) return {};

        vector<int> shuffled = origin;

        // 反向洗牌 Fishser-Yates
        for (int i = shuffled.size() - 1; i >= 0; i--) {
            int j = rand() % (i + 1);
            swap(shuffled[i], shuffled[j]);
        }

        return shuffled;
    }
};