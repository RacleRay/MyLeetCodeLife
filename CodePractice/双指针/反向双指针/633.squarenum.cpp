#include <iostream>
#include <math.h>

class Solution {
public:
    bool judgeSquareSum(int c) {
        long small = 0, big = sqrt(c);
        while (small <= big) {
            long cur = small * small + big * big;
            if (cur > c)
                --big;
            else if (cur < c)
                ++small;
            else
                return true;
        }
        return false;
    }

    // 当且仅当一个自然数的质因数分解中，满足 4k+3 形式的质数次方数均为偶数时，该自然数才能被表示为两个平方数之和
    bool judgeSquareSum2(int c) {
        for (int i = 2, cnt = 0; i * i <= c; ++i, cnt = 0) {
            while (c % i == 0 && ++cnt > 0) c /= i;
            if (i % 4 == 3 && cnt % 2 != 0) return false;
        }
        // 此时检测为偶数
        // c % 4 == 3 ：为奇数，不满足定义
        return c % 4 != 3;
    }
};


int main() {
    Solution sl = Solution();
    sl.judgeSquareSum(4);
    return 0;
}
