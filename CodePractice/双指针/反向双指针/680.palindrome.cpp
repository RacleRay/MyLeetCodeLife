#include <iostream>
#include <string>


using namespace std;

class Solution {
public:
    bool validPalindrome(string s) {
        int l = 0, r = s.size() - 1;

        while (l < r) {
            if (s[l] == s[r]) {
                ++l, --r;
                continue;
            }
            return __afterDelPalindrome(s, l + 1, r) || __afterDelPalindrome(s, l, r - 1);//check;
        }

        return true;
    }

    bool __afterDelPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s.at(l) == s.at(r)) {
                ++l, --r;
                continue;
            } else
                return false;
        }
        return true;
    }

    
};