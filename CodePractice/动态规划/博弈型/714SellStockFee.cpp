#include "../../header.h"


class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();

        if (n == 0) return 0;

        // buy 可买入
        // sell 可卖出
        vector<int> buy(n, 0), sell(n, 0);
        sell[0] = -prices[0]-fee;

        for (int i = 1; i < n; ++i) {
            buy[i] = max(buy[i - 1], sell[i - 1] + prices[i]);
            sell[i] = max(sell[i - 1], buy[i - 1] - prices[i] - fee);
        }

        return buy[n - 1];
    }
};