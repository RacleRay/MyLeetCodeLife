#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
#include <queue>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;


class Solution {
public:
    int countDigitOne(int n) {
        if(n <= 0) return 0;
        if(n< 10 ) return 1;
        if(n == 10) return 2;

        int factor = 1, high = n, rest = 0;

        while (high >= 10){
            high /= 10;
            factor *= 10;
        }

        rest = n - high * factor;
        int cur = high == 1 ? rest + 1: factor;

        return cur + high * countDigitOne(factor - 1) + countDigitOne(rest);
    }


    int countDigitOne(int n) {
        if(n <= 0) return 0;
        if(n< 10 ) return 1;
        if(n == 10) return 2;

        long digit = 1, res=0;
        int high = n / 10;
        int cur = n % 10;
        int low = 0;

        while (high != 0 or cur != 0){
            if (cur == 0)
                res += high * digit;   // digit 位置为1 的个数
            else if (cur == 1)
                res += high * digit + low + 1;
            else
                res += (high + 1) * digit;

            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }

        return res;
    }
};