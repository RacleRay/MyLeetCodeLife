#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE (10000)


int check(long long limit, int m, const int requie[], int require_size) {
    int l = 0;
    int r = require_size - 1;

    int need = 0;
    while (l <= r) {
        if (requie[l] + requie[r] <= limit) {
            l++;
        }
        r--;
        need++;
    }

    return m >= need;
}


int cmp(const void *a, const void *b) {
    return *((int*)a) - *((int*)b);
}


long long getResult(int m, int require[], int require_size) {
    qsort(require, require_size, sizeof(int), cmp);

    long long min = require[require_size - 1];
    long long max = require[require_size - 1] + require[require_size - 2];
    long long ans = max;

    while (min <= max) {
        long long mid = min + (max - min) / 2;
        if (check(mid, m, require, require_size)) {
            ans = mid;
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    return ans;
}


int main() {
    int m;
    scanf("%d", &m);

    int require[MAX_SIZE];
    int require_size = 0;

    while (scanf("%d", &require[require_size++])) {
        if (getchar() != ' ') break;
    }

    printf("%lld\n", getResult(m, require, require_size));

    return 0;
}