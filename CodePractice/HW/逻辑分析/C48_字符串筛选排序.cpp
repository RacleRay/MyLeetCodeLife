#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000


int cmp(const void* a, const void* b) {
    return (*(char*)a) - (*(char*)b);
}


int main() {
    char s[MAX_SIZE + 3];
    fgets(s, MAX_SIZE, stdin);

    int k; 
    scanf("%d", &k);

    int n = strlen(s) - 1;  // 知道为什么要减一吗？精髓
    char tmp[n + 1];
    strcpy(tmp, s);

    // sort
    qsort(tmp, n, sizeof(char), cmp);
    if (k > n) {
        k = n;
    }

    char target = tmp[k - 1];
    printf("%ld\n", strchr(s, target) - s);

    return 0;
}