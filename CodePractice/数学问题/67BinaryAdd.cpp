#include "../header.h"


class Solution {
public:
    string addBinary(string a, string b) {
        auto ra = a.rbegin();
        auto rb = b.rbegin();

        int carry = 0;
        string res;
        while (ra != a.rend() && rb != b.rend()) {
            int tmp = *ra - '0' + *rb - '0' + carry;
            carry = tmp / 2;
            res.push_back(tmp % 2 + '0');
            ra++;
            rb++;
        }

        while (ra != a.rend()) {
            int tmp = *ra - '0' + carry;
            carry = tmp / 2;
            res.push_back(tmp % 2 + '0');
            ra++;
        }

        while (rb != b.rend()) {
            int tmp = *rb - '0' + carry;
            carry = tmp / 2;
            res.push_back(tmp % 2 + '0');
            rb++;
        }

        if (carry) {
            res.push_back('1');
        }
        std::reverse(res.begin(), res.end());

        return res;
    }
};


// 
/**
 * @brief python 2 进制计算
 * 

class Solution:
    def addBinary(self, a, b) -> str:
        x, y = int(a, 2), int(b, 2)
        while y:
            answer = x ^ y
            carry = (x & y) << 1
            x, y = answer, carry
        return bin(x)[2:]

 */

