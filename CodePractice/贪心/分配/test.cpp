#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        if (people.size() == 1) return people;

        sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) return a[1] < b[1];
            return a[0] > b[0];
        });

        vector<vector<int>> result;
        result.reserve(people.size() + 1);

        for (auto& tmp: people) {
            result.insert(result.begin() + tmp[1], tmp);
        }

        return result;
    }

    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
        if (people.size() == 1)  return people;

        sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        gn = people.size();
        treeArray.resize(gn + 1, 0);
        vector<vector<int>> res(people);

        for (auto& tmp: people) {
            int l = 1, r = gn;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (mid - query(mid) >= tmp[1] + 1)
                    r = mid;
                else
                    l = mid + 1;
            }
            res[r - 1] = tmp;
            update(r, 1);
        }

        return res;
    }

private:
    int gn;
    vector<int> treeArray;

    int lowbit(int x) {
        return x & -x;
    }

    void update(int idx, int x) {
        for (int i = idx; i <= gn; i += lowbit(i)) {
            treeArray[i] += x;
        }
    }

    int query(int idx) {
        int res = 0;
        for (int i = idx; i > 0; i -= lowbit(i)) {
            res += treeArray[i];
        }
        return res;
    }

};


int main() {
    Solution sl;

    vector<vector<int>> v = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};

    vector<vector<int>> res = sl.reconstructQueue2(v);
    return 0;
}