#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        if (s.size() == 0 || dictionary.size() == 0) return "";

        sort(dictionary.begin(), dictionary.end(), [](const string& sa, const string& sb) {
            if (sa.size() == sb.size())
                return sa < sb;
            return sa.size() > sb.size();
        });

        for (auto& str: dictionary) {
            int i = 0, j = 0;
            while (i < s.size() && j < str.size()) {
                if (s[i] == str[j]) {
                    ++i, ++j;
                } else {
                    ++i;
                }
            }

            if (j == str.size()) return str;
        }

        return "";
    }
};