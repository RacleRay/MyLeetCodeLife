#include <stdio.h>
#include <math.h>


#define MAX_SIZE (1000)
#define MAX_ROWS (1001)
#define MAX_COLS (1474560 / 512 + 1)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 栈溢出
int dp[MAX_ROWS][MAX_COLS] = { 0 };

int getResult(int*s, int n) {
    int bag = 1474560 / 512;

    for (int i = 1; i <= n; i++) {
        int weight = (int)ceil(s[i - 1] / 512.0);
        int worth = s[i - 1];

        for (int j = 0; j <= bag; j++) {
            if (weight > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = MAX(dp[i - 1][j], dp[i - 1][j - weight] + worth);
            }
        }
    }

    return dp[n][bag];
}


int main() {
    int n;
    scanf("%d", &n);

    int s[MAX_SIZE] = { 0 };
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }

    printf("%d\n", getResult(s, n));

    return 0;
}