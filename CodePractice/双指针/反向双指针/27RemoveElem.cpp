#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int tail = n - 1;   // to swap
        for (int i = 0 ; i <= tail ; i++) {
            while (i <= tail && nums[i] == val) {
                swap(nums[i], nums[tail]);
                tail--;
            }
        }

        return tail + 1;        
    }
};