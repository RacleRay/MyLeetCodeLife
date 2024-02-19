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
    for (int i = 0; i < length - 1; ++i) {
        int swapped = 0;
        for (int j = 0; j < length - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                swap(&data[j], &data[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}


void sort_better(int* data, int length) {
    int issorted = 0;
    do {
        issorted = 1;
        length--;
        for (int i = 0; i < length; i++) {
            if (data[i] > data[i + 1]) {
                swap(&data[i], &data[i + 1]);
                issorted = 0;
            }
        }
    } while (!issorted);
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