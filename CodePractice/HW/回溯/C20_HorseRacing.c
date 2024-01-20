#include <stdio.h>

#define  MAX_SIZE 10

int a[MAX_SIZE];
int a_size = 0;

int b[MAX_SIZE];
int b_size = 0;

int max_cnt = 0;
int ans = 0;



void dfs(int level, int used[], int bigger_count) {
    if (level >= a_size) {
        if (bigger_count > max_cnt) {
            max_cnt = bigger_count;
            ans = 1;
        } else if (bigger_count == max_cnt) {
            ans += 1;
        }

        return ;
    }

    for (int i = 0; i < a_size; i++) {
        if (used[i]) {
            continue;
        }
        used[i] = 1;
        dfs(level + 1, used, bigger_count + (a[i] > b[level] ? 1 : 0));
        used[i] = 0;
    }
}


int main() {
    while (scanf("%d", &a[a_size++]) != EOF) {
        if (getchar() != ' ') { break; }
    }

    while (scanf("%d", &b[b_size++]) != EOF) {
        if (getchar() != ' ') { break; }
    }

    int used[MAX_SIZE] = {0};

    dfs(0, used, 0);

    printf("%d\n", ans);

    return 0;
}
