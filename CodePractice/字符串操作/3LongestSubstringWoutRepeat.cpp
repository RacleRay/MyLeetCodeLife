#include "../header.h"


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        std::array<int, 256> char_counts;
        char_counts.fill(0);

        int si = 0, sub_tail = -1;
        int res = 0, len = s.size();

        while (si < len) {
            // erase the first char count.
            if (si >= 0) {
                char_counts[s[si]]--;
            }

            // move to legal tail.
            while (sub_tail < len && char_counts[s[sub_tail]] == 0) {
                char_counts[s[sub_tail]]++;
                sub_tail++;
            }

            // update the result.
            res = std::max(res, sub_tail - si);

            ++si;
        }

        return res;      
    }
};