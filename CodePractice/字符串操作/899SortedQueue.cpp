#include <string>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k != 1) {
            std::sort(s.begin(), s.end());
            return s;
        } 

        size_t i = 0, j = 1, max_len = 0;
        size_t n = s.size();
        while (i < n && j < n && max_len < n) {
            if (s[(i + max_len) % n] == s[(j + max_len) % n]) {
                max_len++;
            } else {
                if (s[(i + max_len) % n] < s[(j + max_len) % n]) {
                    j = j + max_len + 1;
                } else {
                    i = i + max_len + 1;
                }

                if (i == j) {
                    j++;
                }
                max_len = 0;
            }
        }

        i = min(i, j);

        string res = s.substr(i) + s.substr(0, i);
        return res;
    }
};