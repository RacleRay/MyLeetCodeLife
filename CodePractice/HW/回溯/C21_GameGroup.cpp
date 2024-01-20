#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>


using namespace std;

int res = INT_MAX;
int total =  0;
int target = 0;


void dfs(vector<int>& nums, int idx, int count, int current_sum) {
    if (current_sum > target) { return ; }

    if (count == 5) {
        int rest_sum = total - current_sum;
        res = min(res, abs(current_sum - rest_sum));
        return;
    }

    if (idx == 10) { return; }

    dfs(nums, idx + 1, count + 1, current_sum + nums[idx]);

    dfs(nums, idx + 1, count, current_sum);
}


int main() {
    vector<int> nums(10);

    for (int i = 0; i < 10; ++i) {
        cin >> nums[i];
        total += nums[i];
    }

    target = total / 2;

    dfs(nums, 0, 0, 0);
    cout << res << endl;

    return 0;
}