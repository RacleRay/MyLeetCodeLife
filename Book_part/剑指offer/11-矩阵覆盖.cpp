#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>

using namespace std;


// 解法本质还是一个动态规划，每次增加有两种方式得到 2 的边长
// 和上台阶一个解法

class Solution {
public:
    int rectCover(int number) {
        if (number <= 2) { return number; }

        int dp[3] = {1, 2, 3};
        for (int i = 3; i < number; i++) {
            dp[i % 3] = dp[(i - 1) % 3] + dp[(i - 2) % 3];
        }

        return dp[(number - 1) % 3];
    }
};