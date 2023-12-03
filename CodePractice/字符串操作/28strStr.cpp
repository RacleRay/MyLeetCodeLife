#include "../header.h"


class Solution {
public:
    int strStr(string haystack, string needle) {
        return sunday(haystack, needle);
    }

    void buildMatch(const string& pattern, vector<int>& match) {
        int plen = pattern.length();

        match[0] = -1;
        int prefix_idx = 0, suffix_idx = 0;
        for (suffix_idx = 1; suffix_idx < plen; ++suffix_idx) {
            prefix_idx = match[suffix_idx - 1];  // 准备匹配下一个模式字符
            // 不匹配则回退，从已经匹配过的前缀后缀部分，回退到上一个相同的匹配
            while (prefix_idx >= 0 && (pattern[prefix_idx + 1] != pattern[suffix_idx])) {
                prefix_idx = match[prefix_idx];
            }
            if (pattern[prefix_idx + 1] == pattern[suffix_idx]) {
                match[suffix_idx] = prefix_idx + 1;
            } else {
                match[suffix_idx] = -1;
            }
        }        
    }

    int kmp(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        if (m > n) return -1;

        vector<int> match(m, -1);
        buildMatch(pattern, match);

        int si = 0, pi = 0;
        while (si < n && pi < m) {
            if (text[si] == pattern[pi]) {
                ++si;
                ++pi;
            } else if (pi > 0) {
                pi = match[pi - 1] + 1;  // 回退
            } else {
                ++si;
            }
        }

        return (pi == m) ? si - m : -1;
    }

    int sunday(const string& text, const string& pattern) {
        int plen = pattern.length();
        int tlen = text.length();
        array<int, 256> last_present;
        last_present.fill(-1);
        
        for (int i = 0; i < plen; ++i) {
            last_present[pattern[i]] = i;
        }

        for (int i = 0; i + plen <= tlen; i += (plen - last_present[text[i + plen]])) {
            int flag = 1;
            for (int j = 0; j < plen; ++j) {
                if (text[i + j] == pattern[j]) continue;
                flag = 0;
                break;
            }
            if (flag) return i;
        }

        return -1;
    }

};


int main() {
    Solution s;
    s.strStr("sadbutsad", "sad");
    return 0;
}