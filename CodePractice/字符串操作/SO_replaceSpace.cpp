#include "../header.h"


/**
 * @brief 
 * 
 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
 例如，当字符串为 We Are Happy. 则经过替换之后的字符串为 We%20Are%20Happy.
 */


class Solution {

public:
    string replaceSpace(string s) {
        if (s.empty()) {
            return s;
        }

        int nspace = 0;
        for (char c : s) {
            nspace += c == ' ' ? 1 : 0;
        }

        int old_tail = s.size() - 1;
        int new_tail = old_tail + 2 * nspace;

        for (int i = old_tail; i >= 0 && i != new_tail; i--) {
            if (s[i] == ' ') {
                s[new_tail--] = '0';
                s[new_tail--] = '2';
                s[new_tail--] = '%';
            } else {
                s[new_tail--] = s[i];
            }
        }

        return s;
    }
};