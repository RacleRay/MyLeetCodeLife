// https://leetcode.cn/problems/can-place-flowers/

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        // if (flowerbed.size() < n) return false;

        // int len = flowerbed.size(), i = 0;
        // while (i < len - 1 && n > 0) {
        //     if (flowerbed[i] == 1)
        //         i += 2;
        //     else if (flowerbed[i + 1] == 0) {
        //         --n;
        //         i += 2;
        //     } else {
        //         i += 3;
        //     }
        // }

        // if (i == len - 1 && flowerbed[i] == 0)
        //     --n;

        // return n <= 0;

        if (flowerbed.size() < n) return false;

        int len = flowerbed.size(), i = 0;
        while (i < len - 1 && n > 0) {
            if (flowerbed[i] == 1) i += 2;
            else {
                if (flowerbed[i + 1] == 1) i += 3;
                else {
                    --n;
                    i += 2;
                }
            }
        }

        if (i == len - 1 && flowerbed[i] == 0)
            --n;

        return n <= 0;
    }
};