#include "../header.h"


class Solution {
    vector<int> sums;
public:
    Solution(vector<int>& w): sums(std::move(w)) {
        std::partial_sum(sums.begin(), sums.end(), sums.begin());
    }
    
    int pickIndex() {
        int pos = (std::rand() % sums.back()) + 1;
        return std::lower_bound(sums.begin(), sums.end(), pos) - sums.begin();
    }
};