#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))


int cmp(const void *a, const void *b) {
    int *pa = (int *)a;
    int *pb = (int *)b;
    return pa[0] != pb[0] ? pa[0] - pb[0] : pb[1] - pa[1];
}


int getResult(int n, int ranges[][2]) {
    int ans = 0;

    qsort(ranges, n, sizeof(ranges[0]), cmp);

    int t = ranges[0][1];

    for (int i = 1; i < n; i++) {
        int s = ranges[i][0];
        int e = ranges[i][1];

        if (t >= s) {
            t = MAX(e, t);
        } else {
            ans += s - t;
            t = e;
        }
    }

    return ans;
}


int main() {
    int n;
    scanf("%d", &n);

    int ranges[n][2];
    for (int i = 0; i < n; i++) {
        int center = i * 100;

        int radius;
        scanf("%d", &radius);

        ranges[i][0] = center - radius;
        ranges[i][1] = center + radius;
    }

    printf("%d\n", getResult(n, ranges));

    return 0;
}