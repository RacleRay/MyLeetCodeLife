#include <stdio.h>


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void print(int* data, int length) {
    for (int i = 0; i < length; i++) {
        i > 0 && printf(" ");
        printf("%d", data[i]);
    }
    printf("\n");
}


void sort(int* data, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i - 1; j >= 0; --j) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
            } else {
                break;
            }
        }
    }
}


void sort_better(int* data, int length) {
    int cur;
    for (int i = 1; i < length; i++) {
        cur = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > cur) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = cur;
    }
}


int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sort_better(arr, n);
    print(arr, n);

    return 0;
}