#include "../header.h"


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return {};

        int len = nums.size();

        vector<int> res(len, 1);

        for (int i = 1; i < len; ++i) {
            res[i] = res[i - 1] * nums[i - 1];
        }        

        int right_product = 1;
        for (int i = len - 1; i >= 0; --i) {
            res[i] *= right_product;
            right_product *= nums[i];
        }

        return res;
    }
    
};


int main() {
    Solution s;
    vector<int> data{-1,1,0,-3,3};
    vector<int> res =  s.productExceptSelf(data);
    for (auto i : res) {
        cout << i << endl;
    }
    return 0;
}