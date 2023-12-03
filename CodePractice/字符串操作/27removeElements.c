
#include <stdio.h>


int removeElement(int* nums, int numsSize, int val){
    int valid_i = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != val) {
            nums[valid_i++] = nums[i];
        }
    }
    return valid_i;
}


// int removeElement2(int* nums, int numsSize, int val) {
//     int res_len = 0, tail = numsSize - 1;



//     return 
// }