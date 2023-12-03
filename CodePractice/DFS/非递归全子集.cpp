#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    // 转化为 二进制位 数值遍历组合
    vector<vector<int>> subsets(vector<int> & nums) {
        vector<vector<int>> result;

        const int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < ( 1 << n ); ++i) {
            vector<int> subset;
            for (int j = 0; j < n; ++j) {
                if ((i & (1 << j)) != 0) {
                    subset.push_back(nums[j]);
                }
            }
            result.push_back(std::move(subset));
        }

        return result;
    }

    // BFS不常用来求全子集，但是也能用
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> results;
        sort(nums.begin(), nums.end());

        queue<vector<int>> que;
        que.push({});

        while (!que.empty()) {
            vector<int> subset = que.front();
            que.pop();
            results.push_back(subset);

            for (int i = 0; i < nums.size(); ++i) {
                if (subset.size() == 0 || subset.back() < nums[i]) {
                    vector<int> temp = subset;
                    temp.push_back(nums[i]);
                    que.push(subset);
                }
            }
        }

        return results;
    }
};