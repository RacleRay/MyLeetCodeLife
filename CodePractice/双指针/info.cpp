/*************************************************************************
    > File Name: info.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <iostream>


int* addition(int a, int b) {
    int* sum = new int(a + b);
    return sum;
}

int subtraction(int a, int b) {
    return a - b;
}

int operation(int x, int y, int (*func)(int, int)) {
    return (*func)(x, y);
}

int (*minus)(int, int) = subtraction;
int* m = addition(1, 2);
int n = operation(3, *m, minus);

int main() {
    int x;
    int * p1 = &x;
    const int * p2 = &x;
    int * const p3 = &x;
    const int * const p4 = &x;

    return 0;
}