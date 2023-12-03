#include "../header.h"


class Solution {
public:
    int calculate(string s) {
        return parseExpr(s, 0);
    }

    int parseExpr(const string& s, int i) {
        char op = '+';
        long left = 0, right = 0;
        while (i < s.length()) {
            if (s[i] == ' ') {
                ++i;
                continue;
            }

            long num = parseNum(s, i);
            switch (op) {
                case '+': {
                    // current operands add, next num backup
                    left += right; right = num; break;
                }
                case '-': {
                    left += right; right = -num; break;
                }
                case '*': {
                    // 1 + 2 * 3 , higher priority goes first
                    right *= num; break;
                }
                case '/': {
                    right /= num; break;
                }
            }

            if (i < s.length()) {
                op = s[i];
            }
            ++i;
        }

        return left + right;
    }


    long parseNum(const string& s, int& i) {
        long n = 0;
        while (i < s.length() && isdigit(s[i])) {
            n = 10 * n + (s[i++] - '0');
        }
        return n;
    }
};