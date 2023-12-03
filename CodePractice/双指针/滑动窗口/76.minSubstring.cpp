#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> dict;

        for (size_t i = 0; i < t.size(); ++i)
        {
            if (dict.find(t[i]) == dict.end())
                dict[t[i]] = 1;
            else
                dict[t[i]] += 1; 
        }
        
        // TODO:
        // 1. find dict[] is negetive.
        // 2. #38 line ++dict[] > 0.
        // 3. 
        size_t cnt_in_t = 0, l = 0, min_l = 0, min_size = s.size() + 1;
        for (size_t r = 0; r < s.size(); ++r) {
            if (dict.find(s[r]) != dict.end()) {  // s[r]是在 t 中
                // find sr in t
                if (--dict[s[r]] >= 0)  // true: 1 2 3; false: 0 (前面已经将某一个字符匹配完毕)
                    ++cnt_in_t;
                // check first legel
                while (cnt_in_t == t.size()) {
                    // check optimal result
                    if (r - l + 1 < min_size) {
                        min_l = l;
                        min_size = r - l + 1;
                    }
                    // move left to next char in t
                    // At the beginning, sl may be not in t.
                    if (dict.find(s[l]) != dict.end() && ++dict[s[l]] > 0) {
                        --cnt_in_t;
                    }
                    ++l;
                }
            }
        }

        return min_size > s.size() ? "": s.substr(min_l, min_size);
    }
};


int main() {
    Solution sl = Solution();
    sl.minWindow("ADOBECODEBANC", "ABC");
    return 0;
}