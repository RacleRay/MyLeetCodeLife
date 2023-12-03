#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        int n = prices.size();
        for (int i = 1; i < n; ++i) {
            res += max(0, prices[i] - prices[i - 1]);
        }
        return res;
    }

    int maxProfitDp(vector<int>& prices) {
        int n = prices.size();
        // dp0: 当天未持股的利润，dp1: 当天持股的利润
        int dp0 = 0, dp1 = -prices[0];

        for (int i = 1; i < n; ++i) {
            int dp0tmp = max(dp0, dp1 + prices[i]);
            int dp1tmp = max(dp1, dp0 - prices[i]);
            dp0 = dp0tmp;
            dp1 = dp1tmp;
        }

        return dp0;
    }
};