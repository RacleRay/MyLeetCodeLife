#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// https://leetcode.cn/problems/queue-reconstruction-by-height/solutions/1493335/by-ac_oier-fda2/

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if (people.size() == 1) return people;

        sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] > b[0];
        });

        int n = people.size();
        vector<vector<int>> res;
        res.reserve(n + 1);

        // 贪心
        for (auto& tmp: people) {
            res.insert(res.begin() + tmp[1], tmp);
        }

        return res;
    }


    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
        if (people.size() == 1) return people;

        sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        gn = people.size();
        treeArray.resize(gn + 1, 0);
        vector<vector<int>> res(people);

        for (vector<int>& tmp: people) {
            int l = 1, r = gn;
            while (l < r) {
                int mid = (l + r) >> 1;
                // mid左侧0的数量刚好等于 k + 1
                if (mid - query(mid) >= tmp[1] + 1)
                    r = mid;
                else
                    l = mid + 1;
            }
            res[r - 1] = tmp;
            add(r, 1);
        }

        return res;
    }

private:
    // 理解树状数组，是独立于原数组，根据二进制变换，形成的新的记录有规律的区间和的数组。

    // 区间查询单点修改，树状数组
    int gn;
    vector<int> treeArray;

    // 最左边1的位置
    int lowbit(int x) {
        return x & -x;
    }

    void add(int idx, int val) {
        for (int i = idx; i <= gn; i += lowbit(i))
            treeArray[i] += val;
    }

    int query(int idx) {
        int ans = 0;
        for (int i = idx; i > 0; i -= lowbit(i))
            ans += treeArray[i];
        return ans;
    }
};