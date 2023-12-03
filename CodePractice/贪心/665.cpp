#include <algorithm>
#include <functional>
#include <vector>


using namespace std;


class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int count = 0, n = nums.size();
        for (int i = 0; i < n - 1 && count < 2; ++i) {
            if (nums[i] > nums[i + 1]) {
                ++count;
                if (i > 0 && nums[i - 1] > nums[i + 1]) {
                    nums[i + 1] = nums[i];
                } else {
                    nums[i] = nums[i + 1];
                }
            }
        }
        return count < 2;
    }
};

int main() {
    Solution sl = Solution();
    vector<int> t {4,2,3};
    bool res = sl.checkPossibility(t);
    return 0;
}