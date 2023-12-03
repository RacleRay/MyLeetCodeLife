#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/daily-temperatures/
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> stack{0};
        vector<int> res(n, 0);  // 还要什么while结尾检测

        for (int i = 1; i < n; ++i) {
            if (temperatures[i] > temperatures[stack.back()]) {
                while (!stack.empty() && temperatures[i] > temperatures[stack.back()]) {
                    int s_top = stack.back();
                    stack.pop_back();                    
                    res[s_top] = (i - s_top);
                }
                // stack.push_back(i);
            }
            stack.push_back(i);
            // if (temperatures[i] <= temperatures[stack.back()]) {
            //     stack.push_back(i);
            // }
        }

        // 看看 res 的初始化，啊喂
        // while (!stack.empty()) {
        //     res.push_back(0);
        //     stack.pop_back();
        // }

        return res;
    }
};


int main() {
    Solution sl = Solution();
    vector<int> in{73,74,75,71,69,72,76,73};
    sl.dailyTemperatures(in);
    return 0;
}