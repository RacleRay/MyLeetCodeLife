#include <stdio.h>


int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    int graph[rows * cols];
    int start = 0;

    int gray = 0;
    int len = 0;
    while (scanf("%d %d", &gray, &len)) {
        for (int i = start; i < start + len; i++) {
            graph[i] = gray;
        }
        start += len;
        if (getchar() != ' ') { break; }
    }

    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", graph[x * cols + y]);

    return 0;
}