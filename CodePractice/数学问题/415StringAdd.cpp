#include "../header.h"

class Solution {
public:
    string addStrings(string num1, string num2) {
        string output{""};

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        int len1 = num1.length();
        int len2 = num2.length();

        if (len1 <= len2) {
            swap(num1, num2);
            swap(len1, len2);
        }

        int carry = 0;
        for (int i = 0; i < len2; i++) {
            int cur = (num1[i] - '0') + (num2[i] - '0') + carry;
            output += to_string(cur % 10);
            carry = cur < 10 ? 0 : 1;
        }

        for (int i = len2; i < len1; i++) {
            int cur = (num1[i] - '0') + carry;
            output += to_string(cur % 10);
            carry = cur < 10 ? 0 : 1;
        }

        if (carry) {
            output += "1";
        }
        reverse(output.begin(), output.end());

        return output;
    }
};