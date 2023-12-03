#include "../header.h"


class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = n;

        do {
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        } while (slow != fast);

        return slow == 1;
    }

    int getNext(int n) {
        int res = 0;

        while (n) {
            int tmp = n % 10;
            res += tmp * tmp;
            n /= 10;
        }

        return res;
    }
};