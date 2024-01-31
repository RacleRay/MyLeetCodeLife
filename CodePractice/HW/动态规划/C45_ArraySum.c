#include <stdio.h>


long getResult(int n, int x, int arr[]) {
    int preSum[n + 1];

    preSum[0] = 0;
    for (int i = 1; i <= n; i++) {
        preSum[i] = preSum[i - 1] + arr[i - 1];
    }

    int l = 0;
    int r = 1;
    long ans = 0;

    while (r <= n) {
        if (preSum[r] - preSum[l] >= x) {
            ans += n - r + 1;
            l++;
            r = l + 1;
        } else {
            r++;
        }
    }

    return ans;
}


int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%ld", getResult(n, x, arr));

    return 0;
}