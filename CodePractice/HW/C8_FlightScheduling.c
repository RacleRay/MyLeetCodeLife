#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int cmp(const void *a, const void *b) {
    char *A = (char *)a;
    char *B = (char *)b;

    char pt1[3];
    strncpy(pt1, A, 2);
    char num1[5];
    strncpy(num1, A + 2, 4);

    char pt2[3];
    strncpy(pt2, B, 2);
    char num2[5];
    strncpy(num2, B + 2, 4);

    int res = strcmp(pt1, pt2);
    if (res == 0) {
        return strcmp(num1, num2);
    } else {
        return res;
    }
}


int main() {
    char s[1000];
    fgets(s, 1000, stdin);

    char flights[100][7];
    int size = 0;

    char *token = strtok(s, ",");
    while (token != NULL) {
        strcpy(flights[size], token);
        token = strtok(NULL, ",");
        size++;
    }

    qsort(flights, size, sizeof(flights[0]), cmp);

    for (int i = 0; i < size; i++) {
        printf("%s", flights[i]);
        (i != size - 1) && (printf(","));
    }

    return 0;
}