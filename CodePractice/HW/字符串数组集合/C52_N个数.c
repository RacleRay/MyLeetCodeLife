#include <stdio.h>
#include <stdlib.h>


int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}


int main() {
    int m;
    scanf("%d", &m);

    int arr[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
    }

    int n;
    scanf("%d", &n);


    // ==============================================

    if (n <= 0) {
        printf("%d\n", -1);
        return 0;
    }

    int set[1005] = {0};
    int set_size = 0;

    int distinct_arr[1005];
    int distinct_arr_size = 0;

    for (int i = 0; i < m; i++) {
        int num = arr[i];
        if (num < 0 || num > 1000) {
            printf("%d\n", -1);
            return 0;
        }

        if (!set[num]) {
            set_size++;
            set[num] = 1;
            distinct_arr[distinct_arr_size++] = num;
        }
    }

    if (set_size < n * 2) {
        printf("%d\n", -1);
        return 0;
    }

    qsort(distinct_arr, distinct_arr_size, sizeof(int), cmp);

    int l = 0;
    int r = distinct_arr_size - 1;
    int ans = 0;

    while (n > 0) {
        ans += distinct_arr[l++] + distinct_arr[r--];
        n--;
    }


    printf("%d\n", ans);

    return 0;
}
