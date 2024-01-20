#include <stdio.h>
#include <math.h>


#define MAX_SIZE (100001)

int main() {
    int n;
    scanf("%d", &n);

    int scores[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &scores[i]);
    }

    int k;
    scanf("%d", &k);

    k++;

    int dp[n];
    dp[0] = scores[0];

    // 单调队列
    int que[MAX_SIZE];
    int que_size = 0;

    que[que_size++] = scores[0];
    int que_first_idx = 0;

    for (int i = 1; i < fmin(k, n); i++) {
        dp[i] = que[que_first_idx] + scores[i];

        while (que_size > 0 && dp[i] > que[que_first_idx + que_size - 1]) {
            que_size--;
        }

        que[que_first_idx + que_size] = dp[i];
        que_size++;
    }

    for (int i = k; i < n; i++) {
        // 弹出队列头部元素
        if (dp[i - k] == que[que_first_idx]) {
            que_first_idx++;
            que_size--;
        }

        dp[i] = que[que_first_idx] + scores[i];

        while (que_size > 0 && dp[i] > que[que_first_idx + que_size - 1]) {
            que_size--;
        }

        que[que_first_idx + que_size] = dp[i];
        que_size++;
    }

    printf("%d\n", dp[n - 1]);

    return 0;
}