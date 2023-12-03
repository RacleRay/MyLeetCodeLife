/*************************************************************************
    > File Name: x数之和/两数之和.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        ans.reserve(2);
        unordered_map<int, int> hashMap;
        for (size_t i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (hashMap.find(complement) != hashMap.end()) {
                ans.push_back(i);
                ans.push_back(hashMap[complement]);
                return ans;
            }
            hashMap[nums[i]] = i;
        }
        return ans;
    }

    /**
     * @brief 解法使用双向指针，后半部分主要是在找到原数组中的下标，有点麻烦
     *
     * @param nums
     * @param target
     * @return vector<int>
     */
    vector<int> twoSum2(vector<int>& nums, int target) {
        vector<int> temp = nums;
        sort(temp.begin(), temp.end());

        // find candidates, better use a function
        int i = 0, j = nums.size() - 1;
        while (i < j && temp[i] + temp[j] != target) {
            temp[i] + temp[j] > target ? --j : ++i;
        }

        vector<int> ans;
        ans.reserve(2);
        if (i >= j) return ans;

        // find index, i and j become flags
        for (size_t k = 0; k < nums.size(); k++) {
            if (i != -1 && nums[k] == temp[i]) {
                ans.push_back(k);
                i = -1;
            }
            else if (j != -1 && nums[k] == temp[j]) {
                ans.push_back(k);
                j = -1;
            }
            if (i == -1 && j == -1) return ans;
        }
        return ans;
    }
};

int main(int argc, char* argv[]) {
    cout << "Hello !" << endl;
    return 0;
}
