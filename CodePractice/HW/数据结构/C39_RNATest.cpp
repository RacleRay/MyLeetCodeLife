#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE (100)


typedef struct {
    int *fa;
} UF;


UF *new_UF(int n) {
    UF *u = (UF *)malloc(sizeof(UF));
    u->fa = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->fa[i] = i;
    }
    return u;
}


int find_UF(UF *u, int x) {
    if (x != u->fa[x]) {
        u->fa[x] = find_UF(u, u->fa[x]);
        return u->fa[x];
    }
    return x;
}

void union_UF(UF *u, int x, int y) {
    int x_fa = find_UF(u, x);
    int y_fa = find_UF(u, y);

    if (x_fa != y_fa) {
        u->fa[x_fa] = y_fa;
    }
}


int main() {
    int n;
    scanf("%d", &n);

    int confirmed[MAX_SIZE];
    int confirmed_cnt = 0;

    while (scanf("%d", &confirmed[confirmed_cnt++]) != EOF) {
        if (getchar() != ',') { break; }
    }

    UF *u = new_UF(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int v;
            scanf("%d", &v);
            if (v == 1) {
                union_UF(u, i, j);
            }
            getchar();
        }
    }

    int counts[MAX_SIZE] = {0};
    for (int i = 0; i < n ; i++) {
        int fa = find_UF(u, i);
        counts[fa]++;
    }

    int confirmed_fa[MAX_SIZE] = {0};
    int ans = 0;
    for (int i = 0; i < confirmed_cnt; i++) {
        int fa = find_UF(u, confirmed[i]);

        if (confirmed_fa[fa]) { continue; }
        confirmed_fa[fa] = 1;

        ans += counts[fa];
    }

    printf("%d\n", ans - confirmed_cnt);

    return 0;   
}