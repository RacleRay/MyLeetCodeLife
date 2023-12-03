#include "../header.h"


class Solution {
public:
    string convertToBase7(int num) {
        if (num == 0) { return "0"; }

        bool is_negative = num < 0;
        if (is_negative) { num = -num; }
        string res;
        while (num > 0) {
            int tmp = num / 7, b = num % 7;
            res = to_string(b) + res;
            num = tmp;
        }

        return is_negative ? "-" + res : res;
    }
};