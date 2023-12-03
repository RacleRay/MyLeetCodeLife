#include "../../header.h"


class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        size_t ndays = prices.size();
        if (ndays < 2) {
            return 0;
        }

        if (k >= ndays) {
            return nobrain_trade(prices);   
        }

        // buy[i] 第 i 次买入的最大收益；sell[i] 第 i 次卖出的最大收益
        vector<int> buy(k + 1, INT_MAX), sell(k + 1, 0);
        for (int i = 0; i < ndays; ++i) {
            for (int j = 1; j <= k; ++j) {
                buy[j] = max(buy[j], sell[j - 1] - prices[i]);
                sell[j] = max(sell[j], buy[j] + prices[i]);
            }
        }

        return sell[k];
    }

    int nobrain_trade(vector<int>& prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                res += prices[i] - prices[i - 1];
            }
        }
        return res; 
    }
};