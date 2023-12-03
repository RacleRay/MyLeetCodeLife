#include "../../header.h"


class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        vector<int> dp(n, 1);
        sort(pairs.begin(), pairs.end());

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n - 1];
    }

    int findLongestChain2(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());

        int n = pairs.size();
        vector<int> fit_ubounds;
        fit_ubounds.reserve(n);
        for (auto p: pairs) {
            int low = p[0], high = p[1];
            if (fit_ubounds.size() == 0 || low > fit_ubounds.back()) {
                fit_ubounds.push_back(high);
            } else {
                // 尽可能找到小的 upper bound
                int idx = lower_bound(fit_ubounds.begin(), fit_ubounds.end(), low) - fit_ubounds.begin();
                fit_ubounds[idx] = min(fit_ubounds[idx], high);
            }
        }

        return fit_ubounds.size();
    }
};