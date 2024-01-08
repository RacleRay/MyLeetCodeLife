#include <climits>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int min_diff = INT_MAX, res = 0;
        for (int i = 0; i < n - 2; i++) {
            while (i > 0 && i < n - 3 && nums[i] == nums[i - 1]) {
                i++;
            }

            int sum = nums[i] + nums[i + 1] + nums[i + 2];
            if (sum > target) {
                if (sum - target < min_diff) {
                    res = sum;                    
                }
                break;
            }

            sum = nums[i] + nums[n - 1] + nums[n - 2];
            if (sum < target) {
                if (target - sum < min_diff) {
                    min_diff = target - sum;
                    res = sum;
                }
                continue;
            }

            int left = i + 1, right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == target) {
                    return sum;
                }

                if (sum > target) {
                    if (sum - target < min_diff) {
                        min_diff = sum - target;
                        res = sum;
                    }
                    right--;
                    while (left + 1 < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                } else {
                    if (target - sum < min_diff) {
                        min_diff = target - sum;
                        res = sum;
                    }
                    left++;
                    while (left + 1 < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                }
            }
        }

        return res;
    }
};


int main() {
    vector<int> nums = {1,1,1,1};

    Solution s;
    s.threeSumClosest(nums, 4);

    return 0;
}