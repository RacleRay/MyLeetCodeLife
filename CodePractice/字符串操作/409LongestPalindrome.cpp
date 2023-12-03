#include "../header.h"


class Solution {
public:
    int longestPalindrome(string s) {
        if (s.length() <= 1) {
            return s.length();
        } 

        unordered_map<char, int> char_cnt_map;
        for (char c: s) {
            char_cnt_map[c]++;
        }

        int res = 0;
        for (auto item: char_cnt_map) {
            int cnt = item.second;
            res += cnt / 2 * 2;  // lowerbound even number
            if (res % 2 == 0 && cnt % 2 == 1) {  // consider odd number
                res++;
            }
        }

        return res;
    }
};