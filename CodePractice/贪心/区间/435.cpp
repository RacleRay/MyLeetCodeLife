// https://leetcode.cn/problems/non-overlapping-intervals/

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(), [](vector<int>& iv1, vector<int>& iv2) {
                return iv1[1] < iv2[1];
            }
        );

        int prev_end = intervals[0][1], result = 0;
        int n = intervals.size();
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] < prev_end)
                ++result;
            else
                prev_end = intervals[i][1];
        }

        return result;
    }
};