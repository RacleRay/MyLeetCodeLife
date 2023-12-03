#include "../../header.h"


class Solution {
public:
    bool isMatch(string s, string p) {
        int slen = s.size(), plen = p.size();

        // dp[i][j] 表示以 i 截止的字符串是否可以被以 j 截止的 正则表达式匹配
        vector<vector<bool>> dp(slen + 1, vector<bool>(plen + 1, false));
        dp[0][0] = true;

        // s: ""   p: "*"
        for (int j = 1; j < plen + 1; ++j) {
            if (p[j - 1] == '*' && j - 2 >= 0) {
                dp[0][j] = dp[0][j - 2];  // p 中 j - 1 为 * ，则 j - 2 的字符可以不匹配
                // 以 index 0 截止的 s 为空，所以需要 * 不进行匹配，直接忽略两个符号（x*）即可
            }
        }

        for (int i = 1; i < slen + 1; ++i) {
            for (int j = 1; j < plen + 1; ++j) {
                if (p[j - 1] == '.') {  // . 匹配任意字符
                    dp[i][j] = dp[i - 1][j - 1];  // 前一个字符匹配，则当前字符匹配
                } else if (p[j - 1] != '*') {  // 非通配符情况
                    dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1]);  // 分别考虑前面串，当前字符
                } else if (p[j - 2] != s[i - 1] && p[j - 2] != '.') {  // 通配符情况，且前一个字符不匹配
                    dp[i][j] = dp[i][j - 2];  // * 匹配0次，直接跳过
                } else {
                    // 通配符情况，且前一个字符匹配，或者前一个字符为 .
                    // dp[i][j - 1]: 匹配一次
                    // dp[i][j - 2]: 不对 * 进行匹配
                    // dp[i - 1][j]: 匹配多次，意思就是 s 中 i - 1 个字符是否可以被匹配， bbbb 会在递推状态转移时对 j 截至的模式串进行多次匹配，也就是匹配了多次
                    dp[i][j] = dp[i][j - 1] || dp[i][j - 2] || dp[i - 1][j];
                }
            }
        }

        return dp[slen][plen];
    }
};