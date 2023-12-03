#include "../header.h"


// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int res = 0;
        do {
            res = (rand7() - 1) * 7 + rand7() - 1;

            if (res > 10 || res < 1) continue;
            break;
        } while (1);

        return res;
    }
};