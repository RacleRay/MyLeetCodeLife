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
    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    sort(data, l, mid);
    sort(data, mid + 1, r);

    int tmp[r - l + 1];
    int x = l, y = mid + 1, loc = 0;
    while (x <= mid || y <= r) {
        if (x <= mid && (y > r || data[x] <= data[y])) {
            tmp[loc] = data[x++];
        } else {
            tmp[loc] = data[y++];
        }
        loc++;
    }

    for (int i = l; i <= r; i++) {
        data[i] = tmp[i - l];
    }
}


int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sort(arr, 0, n - 1);
    print(arr, n);

    return 0;
}