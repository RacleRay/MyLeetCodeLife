#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[1000 * 12];

int cmp(const void* a, const void* b) {
    char *A = (char*)a;
    char *B = (char*)b;
    return A[strlen(A) - 1] - B[strlen(B) - 1];
}


int main() {
    fgets(s, 1000 * 12, stdin);

    char nums[1000][12];
    int nums_size = 0;

    char *token = strtok(s, ",");
    while (token != NULL) {
        strncpy(nums[nums_size], token, 12);
        nums_size++;
        token = strtok(NULL, ", ");
    }

    qsort(nums, nums_size, sizeof(nums[0]), cmp);

    printf("%s", nums[0]);
    for (int i = 1; i < nums_size; i++) {
        printf(",%s", nums[i]);
    }

    return 0;
}