#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))


static int pizza_size;
static int pizza[502];

static long long cache[500][500];


int check(int idx) {
    if (idx < 0) {
        idx = pizza_size - 1;
    } else if (idx >= pizza_size) {
        idx = 0;
    }
    return idx;
}


long long recursive(int l, int r) {
    // greedy taking
    if (pizza[l] > pizza[r]) {
        l = check(l - 1);
    } else {
        r = check(r + 1);
    }

    if (cache[l][r] != 0) {
        return cache[l][r];
    }

    // foodie taking
    if (l == r) {
        // return pizza[l];  
        cache[l][r] = pizza[l];
    } else {
        long long v1 = recursive(check(l - 1), r) + pizza[l];
        long long v2 = recursive(l, check(r + 1)) + pizza[r];
        // return MAX(v1, v2);   // foodie
        cache[l][r] = MAX(v1, v2);
    }

    return cache[l][r];
}


int main() {
    scanf("%d", &pizza_size);

    for (int i = 0; i < pizza_size; i++) {
        scanf("%d", &pizza[i]);
    }

    long long ans = 0;   // foodie
    for (int i = 0; i < pizza_size; i++) {
        long long v = recursive(check(i - 1), check(i + 1)) + pizza[i];
        ans = MAX(ans, v);
    }

    printf("%lld", ans);

    return 0;
}