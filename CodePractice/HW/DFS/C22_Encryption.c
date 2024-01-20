#include <stdio.h>


#define MAX_SIZE 201

int n;
int datas[MAX_SIZE];

int m;
int secrets[MAX_SIZE][MAX_SIZE];

int starts[MAX_SIZE];
int starts_size;


int offset[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};


int dfs(int x, int y, int index, int path[], int *path_size, int used[][MAX_SIZE]) {
    if (index == n) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int new_x = x + offset[i][0];
        int new_y = y + offset[i][1];

        if (new_x < 0 || new_x >= m || new_y < 0 || new_y >= m || used[new_x][new_y] ||secrets[new_x][new_y] != datas[index]) {
            continue;
        }

        path[(*path_size)++] = new_x * m + new_y;
        used[new_x][new_y] = 1;

        if (dfs(new_x, new_y, index + 1, path, path_size, used)) {
            return 1;
        }

        used[new_x][new_y] = 0;
        (*path_size)--;
    }

    return 0;
}


void getResult() {
    for (int i = 0; i < starts_size; i++) {
        int x = starts[i] / m;
        int y = starts[i] % m;

        int used[MAX_SIZE][MAX_SIZE] = {0};
        used[x][y] = 1;

        int path[MAX_SIZE] = {0};
        int path_size = 0;
        path[path_size++] = starts[i];

        if (dfs(x, y, 1, path, &path_size, used)) {
            for (int j = 0; j < path_size; j++) {
                int pos = path[j];
                printf("%d %d", pos / m, pos % m);
                if (j < (path_size - 1)) {
                    printf(" ");
                }
            }

            return ;
        }
    }

    puts("error");
}


int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &datas[i]);
    }    

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &secrets[i][j]);
            if (secrets[i][j] == datas[0]) {
                starts[starts_size++] = i * m + j;
            }
        }
    }

    getResult();

    return 0;
}