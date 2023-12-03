#include "../../header.h"


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sell = 0, buy = INT_MAX;
        for (auto price : prices) {
            buy = min(buy, price);
            sell = max(sell, price - buy);
        }
        return sell;
    }
};