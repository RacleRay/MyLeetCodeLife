#include "../header.h"


class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        int n = wall.size();
        unordered_map<int, int> map;

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            for (auto cur : wall[i]) {
                sum += cur;
                map[sum]++;
            }
            map.erase(sum);
            sum = 0;
        }

        int res = n;
        for (auto& it : map) {
            res = min(res, n - it.second);
        }

        return res;
    }
};