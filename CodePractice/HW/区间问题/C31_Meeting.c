#include <stdio.h>
#include <stdlib.h>


int rows = 0;


int cmp(const void* a, const void* b) {
    return (*(int**)a)[0] - (*(int **)b)[0];
}


int** merge(int **times, int size) {
    qsort(times, size, sizeof(int*), cmp);

    int** res = (int**)malloc(sizeof(int*) * size);

    int* pre = times[0];
    for (int i = 1; i < size; i++) {
        int *cur = times[i];

        if (cur[0] <= pre[1]) {
            if (cur[1] > pre[1]) {
                pre[1] = cur[1];
            }
        } else {
            res[rows++] = pre;
            pre = cur;
        }
    }

    res[rows++] = pre;

    return res;
}


int main() {
    int n;
    scanf("%d", &n);

    int **times = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        times[i] = (int*)malloc(sizeof(int) * 2);
        scanf("%d %d", &times[i][0], &times[i][1]);
    }

    int **res = merge(times, n);
    for (int i = 0; i < rows; i++) {
        printf("%d %d\n", res[i][0], res[i][1]);
    }

    return 0;
}