// https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1, sum;
        while (l < r) {
            if (numbers.at(l) + numbers.at(r) < target)
                ++l;
            else if (numbers.at(l) + numbers.at(r) > target)
                --r;
            else
                break;
        }
        return vector<int>{l + 1, r + 1};
    }
};