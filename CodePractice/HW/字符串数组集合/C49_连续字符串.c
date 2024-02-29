#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}


int solution(char*s, int k) {
    if (k <= 0) { return -1; }

    strcat(s, "0");

    int count[128];
    for (int i = 0; i < 128; i++) {
        count[i] = -1;
    }

    char b = s[0];
    int len = 1;
    for (int i = 1; i < strlen(s); i++) {
        char c = s[i];
        if (b == c) {
            len++;
        } else {
            if (count[b] == -1 || count[b] < len) {
                count[b] = len;
            }
            len = 1;
            b = c;
        }
    }

    int arr[150];
    int arr_size = 0;

    for (int i = 0; i < 128; i++) {
        if (count[i] != -1) {
            arr[arr_size++] = count[i];
        }
    }

    qsort(arr, arr_size, sizeof(int), cmp);
    if (k > arr_size) {
        return -1;
    } else {
        return arr[k - 1];
    }
}


int main() {
    char s[150];
    scanf("%s", s);

    int k;
    scanf("%d", &k);

    printf("%d\n", solution(s, k));

    return 0;
}
