#include "../header.h"


class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length();

        if (len < 2) {
            return s;
        }

        // dp[i][j] = true if s[i..j] is a palindrome, else false
        vector<vector<bool>> dp(len, vector<bool>(len, false));

        int max_sub_len = 1;
        int start_pos = 0;

        for (int i = 0; i < len; i++) {
            dp[i][i] = true;
            if (i == len - 1) [[unlikely]] { break; }
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                max_sub_len = 2;
                start_pos = i;
            }
        }

        // 3 开始是因为 dp[i + 1][j - 1] 状态转移判断需要
        for (int slen = 3; slen <= len; slen++) {
            for (int begin = 0; begin < len - slen + 1; begin++) {
                int end = begin + slen - 1;
                if (s[begin] == s[end] && dp[begin + 1][end - 1]) {
                    dp[begin][end] = true;
                    max_sub_len = slen;   // 一定是变大的，所以无需max
                    start_pos = begin;
                }
            }
        }

        return s.substr(start_pos, max_sub_len);
    }

    string longestPalindrome2(string s) {
        int len = s.length();

        if (len < 1) {
            return "";
        }

        string tmp;
        for (int i = 0; i < len; i++) {
            tmp += "#";
            tmp += s[i];
        }
        tmp += "#";

        len = tmp.length();
        // 中间变量有点多
        int max_right = 0;       // 已遍历部分的最大右边界
        int axis_max_right = 0;  // 最大右边界对应的中心轴

        int max_radius = 0;      // 已遍历部分的最大半径
        int axis_max_radius = 0; // 最大半径对应的中心轴

        vector<int> radius_axisby_i(len, 0);

        for (int i = 0; i < len; i++) {
            if (i < max_right) { // 关于 axis_max_right 对称，有一部分相同
                // 一定会成立的对称部分
                radius_axisby_i[i] = min(radius_axisby_i[2 * axis_max_right - i], max_right - i);
            } else {
                radius_axisby_i[i] = 1;  // 重新开始向两边扩展
            }

            // 中心扩展
            while (i - radius_axisby_i[i] >= 0 
                   && i + radius_axisby_i[i] < len
                   && tmp[i - radius_axisby_i[i]] == tmp[i + radius_axisby_i[i]]) 
            {
                radius_axisby_i[i]++;
            }
            // 退出循环时，radius是第一个不满足条件的index
    
            if (i + radius_axisby_i[i] - 1 > max_right) {
                max_right = i + radius_axisby_i[i] - 1;
                axis_max_right = i;
            }

            if (radius_axisby_i[i] - 1 >= max_radius) {
                max_radius = radius_axisby_i[i] - 1;
                axis_max_radius = i;
            }
        }

        return s.substr((axis_max_radius - max_radius) / 2, max_radius);
    }
};