#include <iostream>

class Solution {
public:
    bool checkPerfectNumber(int num) {
        int res = 1;
        for (int i = 2; i * i < num; ++i) {
            if (num % i == 0) {
                res += i;
                res += num / i;
            }
        }

        return res;
    }
};