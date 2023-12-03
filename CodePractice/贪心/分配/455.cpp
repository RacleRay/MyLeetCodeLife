#include <vector>
#include <algorithm>

using namespace std;


class Solution {
    int findContentChildren(vector<int>& children, vector<int>& cookies) {
        sort(children.begin(), children.end());
        sort(cookies.begin(), cookies.end());

        int ch_i = 0, co_i = 0;
        while (ch_i < children.size() && co_i < cookies.size()) {
            if (children[ch_i] <= cookies[co_i])
                ++ch_i;
            ++co_i;
        }

        return ch_i;
    }
};