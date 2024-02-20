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


void sort(int* data, int l, int r) {
    if (l > r) {
        return;
    } 

    int pivot = data[l], low = l, high = r;
    while (low < high) {
        while (low < high && data[high] >= pivot) {
            high--;
        }
        data[low] = data[high];
        while (low < high && data[low] <= pivot) {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;

    sort(data, l, low - 1);
    sort(data, low + 1, r);
}


void sort_better(int *data, int l, int r) {
    if (l >= r) {
        return;
    }

    while (l < r) {
        int x = l, y = r, pivot = data[(x + (y - x) / 2)];
        while (x <= y) {
            while (data[x] < pivot) {
                x++;
            }
            while (data[y] > pivot) {
                --y;
            }
            if (x <= y) {
                swap(&data[x++], &data[y--]);
            }
        }
        sort_better(data, l, y);
        l = x;
    }

    return;
}


int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sort_better(arr, 0, n - 1);
    print(arr, n);

    return 0;
}