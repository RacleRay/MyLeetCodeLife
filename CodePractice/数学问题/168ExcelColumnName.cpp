#include "../header.h"


class Solution {
public:
    string convertToTitle(int columnNumber) {
        if (columnNumber == 1) return "A";

        string res;
        while (columnNumber > 0) {
            res.push_back((columnNumber - 1) % 26 + 'A');
            // res.insert(res.begin(), (columnNumber - 1) % 26 + 'A'); // 慢
            columnNumber = (columnNumber - 1) / 26;
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};