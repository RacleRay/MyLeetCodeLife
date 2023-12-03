#include "../../header.h"


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = s.length();
        vector<bool> dp(len + 1, false);
        
        dp[0] = true;
        for (int i = 1; i <= len; i++) {
            for (const string& word : wordDict) {
                int wordLen = word.length();
                if (i >= wordLen && s.substr(i - wordLen, wordLen) == word) {
                    dp[i] = dp[i] || dp[i - wordLen];
                }
            }
        }

        return dp[len];
    }
};

