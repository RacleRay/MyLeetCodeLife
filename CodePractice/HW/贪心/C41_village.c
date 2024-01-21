#include <stdio.h>
#include <math.h>

#define MAX_SIZE (1000)


int main() {
    int nums[MAX_SIZE] = {0};
    int nums_size = 0;

    while (scanf("%d", &nums[nums_size++])) {
        if (getchar() != ' ') { break; }
    }

    int counts[MAX_SIZE] = {0};
    for (int i = 0; i < nums_size; i++) {
        int num = nums[i];
        counts[num]++;
    }

    int ans = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        int total = i + 1;
        ans += (int)ceil(counts[i] * 1.0 / (double)total) * total;
    }

    printf("%d\n", ans);

    return 0;
}