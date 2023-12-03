#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;

        while (left < right) {
            while (left < right && !my_isalnum(s[left]))
                ++left;
            while (left < right && !my_isalnum(s[right]))
                --right;
            if (left < right && tolower(s[left]) != tolower(s[right])) // or -32 if upper
                return false;
            ++left; --right;
        }

        return true;
    }

    bool my_isalnum(char ch) {
        return isalnum(static_cast<unsigned char>(ch));
    }

    bool my_isvalid(const char ch) {
        // 97-122  65-90  48-57
        if (ch >= 'A' && ch <= 'Z' ||
            ch >= 'a' && ch <= 'z' ||
            ch >= '0' && ch <= '9')
            return true;
        return false;
    }
};


int main() {
    Solution s = Solution();

    s.isPalindrome("A man, a plan, a canal: Panama");

    return 0;
}