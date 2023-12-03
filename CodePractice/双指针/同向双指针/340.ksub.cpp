#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


// TODO: simplify 
class Solution {
    public:
    int lengthOfLongestSubstringKDistinct(const string& s, int k) {
        if (s.size() == 0 || k == 0) return 0;

        unordered_map<char, int> dict;
        dict.emplace(s.at(0), 1);
        int start = 0, end = 0, max_len = -1, cnt = 0;
        while (end < s.size() - 1) {
            if (cnt < k) {
                ++end;
                // 遇到新的字符
                if (dict.find(s.at(end)) == dict.end()) {
                    dict[s.at(end)] = 1;
                    ++cnt;
                } else {
                    ++dict[s.at(end)];
                }
            } else {
                if (max_len < end - start + 1) {
                    max_len = end - start + 1;
                }
                --dict[s.at(start)];
                if (dict[s.at(start)] == 0) {
                    dict.erase(s.at(start));
                    --cnt;
                }
                ++start;
            }
        }

        return max_len;
    }
};