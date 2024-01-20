#include <stdio.h>


int getResult(const int nums[], int n) {
    int result = 0;

    for (int i = 0; i < n; i++) {
        int tmp = nums[i];
        if (tmp > 4) {
            tmp--;
        }

        for (int j = n - i - 1; j > 0; j--) {
            tmp *= 9;
        }

        result += tmp;
    }

    return result;
}


int main() {
    int n;
    scanf("%d", &n);

    int nums[10];
    int n_size = 0;

    while (n > 0) {
        nums[n_size++] = n % 10;
        n /= 10;
    }

    int l = 0;
    int r = n_size - 1;

    while (l < r) {
        int tmp = nums[l];
        nums[l] = nums[r];
        nums[r] = tmp;
        l++;
        r--;
    }

    printf("%d\n", getResult(nums, n_size));

    return 0;
}