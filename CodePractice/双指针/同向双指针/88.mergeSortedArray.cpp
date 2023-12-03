#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos = m + n - 1, p1 = m - 1, p2 = n - 1;
        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[pos] = nums1[p1];
                --p1;
            } else {
                nums1[pos] = nums2[p2];
                --p2;
            }
            --pos;
        }

        while (p2 >= 0) {
            nums1[pos--] = nums2[p2--];
        }

        return;
    }
};


int main() {
    Solution sl = Solution();
    vector<int> a {1,2,3,0,0,0};
    vector<int> b {2,5,6};
    sl.merge(a, 3, b, 3);

    return 0;
}