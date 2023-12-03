// https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        // if (points.empty()) return 0;

        // sort(points.begin(), points.end(), [](vector<int>& v1, vector<int>& v2) {
        //         // if (v1[0] < v1[0]) return true;
        //         // else if (v1[0] == v1[0]) return 
        //         return v1[1] < v1[1];
        //     }
        // );

        // int result = 1, prev_end = points[0][1];
        // int n = points.size();
        // for (size_t i = 1; i < n; ++i) {
        //     if (prev_end < points[i][0]) {
        //         ++result;
        //         prev_end = points[i][1];
        //     }
        // }

        // return result;

        if (points.empty()) return 0;

        sort(points.begin(), points.end(), [](vector<int>& v1, vector<int>& v2) {
            return v1[1] < v1[1];
        });

        int size = points.size();
        int result = 1, prev_end = points[0][1];
        for (int i = 1; i < size; ++i) {
            if (points[i][0] > prev_end) {
                ++result;
                prev_end = points[i][1];
            }
        }

        return result;
    }
};