#include "../header.h"


class Solution {
public:
    // 质因数中5的个数，而不是2的。因为2明显会比5多
    int trailingZeroes(int n) {
        return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5);
    }
};