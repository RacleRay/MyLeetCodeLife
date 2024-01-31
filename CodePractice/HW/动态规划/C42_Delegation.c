#include <stdio.h>


#define MAX_SIZE 30
#define MAX_ROWS 31
#define MAX_COLS 101


int getResult(int *nums, int nums_size, int bag) {
    int dp[MAX_ROWS][MAX_COLS] = {0};
    dp[0][0] = 1;

    // i is the index of group
    for (int i = 1; i <= nums_size; i++) {
        int num = nums[i - 1];

        // j is the size of bag
        for (int j = 0; j <= bag; j++) {
            if (j < num) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - num];
            }
        }
    }    

    return dp[nums_size][bag];
}


int main() {
    int nums[MAX_SIZE] = {0};
    int nums_size = 0;

    while (scanf("%d", &nums[nums_size++])) {
        if (getchar() != ',') {
            break;
        }
    }

    int bag;
    scanf("%d", &bag);

    printf("%d\n", getResult(nums, nums_size, bag));

    return 0;
}