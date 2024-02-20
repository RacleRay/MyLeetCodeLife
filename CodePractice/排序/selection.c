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
    int tmp;
    for (int i = 0; i < length - 1; ++i) {
        tmp = i;
        for (int j = i + 1; j < length - 1; ++i) {
            if (data[tmp] > data[j]) {
                tmp = j;
            }
        }
        if (i != tmp) {
            swap(&data[i], &data[tmp]);
        }
    }
}


void sort_better(int* data, int length) {
    if (length <= 1) {
        return;
    }
    
    register int *last = data + length - 1, *p, *minPtr;
    for (; data < last; ++data) {
        minPtr = data;
        for (p = data + 1; p <= last; ++p) {
            if (*p < *minPtr) {
                minPtr = p;
            }
        }
        if (data != minPtr) {
            swap(data, minPtr);
        }
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