#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmp(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

int main() {
    char s[1005];
    fgets(s, 1005, stdin);

    // solution
    int len = strlen(s);
    char minS[len];
    strncpy(minS, s, len);

    qsort(minS, len, sizeof(char), cmp);

    if (strcmp(minS, s) == 0) {
        goto out;
    }

    for (int i = 0; i < len; i++) {
        if (s[i] != minS[i]) {
            char tmp = s[i];
            s[i] = minS[i];

            int swap_idx = strrchr(s, minS[i]) - s;
            s[swap_idx] = tmp;
            break;
        }
    }

out:
    puts(s);
    return 0;
}