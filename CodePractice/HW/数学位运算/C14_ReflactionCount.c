#include <stdio.h>


#define MAX_SIZE (100)


int main() {
    int w, h, x, y, sx, sy, t;
    scanf("%d %d %d %d %d %d %d", &w, &h, &x, &y, &sx, &sy, &t);
    getchar();

    char matrix[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < h; i++) {
        fgets(matrix[i], MAX_SIZE, stdin);
    }

    int ans = 0;
    while (t >= 0) {
        if (matrix[y][x] == '1') {
            ans++;
        }

        x += sx;
        y += sy;

        if (x < 0) {
            x = 1;
            sx = -sx;
        } else if (x >= w) {
            x = w - 2;
            sx = -sx;
        }

        if (y < 0) {
            y = 1;
            sy = -sy;
        } else if (y >= h) {
            y = h - 2;
            sy = -sy;
        }

        t--;
    }

    printf("%d\n", ans);

    return 0;
}