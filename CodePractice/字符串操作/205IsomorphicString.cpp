#include "../header.h"


class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> s_prev_index(256, 0), t_prev_index(256, 0);

        for (int i = 0; i < s.size(); ++i) {
            if (s_prev_index[s[i]] != t_prev_index[t[i]]) { return false; }
            s_prev_index[s[i]] = t_prev_index[t[i]] = i + 1;
        }

        return true;
    }
};