/*************************************************************************
    > File Name: numbersOfOne.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

typedef int (*func_p)(int x);

void time_test(func_p func) {
    clock_t start, end;
    
    int result = 0;
    start = clock();
    for (int i = 0; i < 100000; ++i) {
        int x = rand() - (INT_MAX >> 1);
        func(rand());
    }
    end = clock();

    printf("%d 中1的个数：%d \n", 139, func(139));
    printf("%d 中1的个数：%d \n", -139, func(-139));
    printf("%s duration: %.2e \n", __PRETTY_FUNCTION__, (double)(end - start) / CLOCKS_PER_SEC);
}

int loop_shift(int x) {
    int cnt = 0;
    int n_bits = sizeof(int) * 8;
    for (int i = 0; i < n_bits; ++i) {
        cnt += (x >> i) & 1;
    }
    return cnt;
}

// unsigened int --> 定义目的为数据，目的可能是位操作
// int           --> 定义目的为数字，有正负号区别，目的时数学运算  
int loop_shift_2(int x) {
    int cnt = 0;
    while (x != 0) {
        x &= x - 1;
        ++cnt;
    }
    return cnt;
}

int loop_shift_3(int x) {
    int cnt = 0;
    int n_bits = sizeof(int) * 8;
    if (x < 0) {
        x &= ~(1 << (n_bits - 1));
        ++cnt;
    }

    while (x != 0) {
        cnt += x & 1;
        x >>= 1;
    }

    return cnt;
}

int main() {
    time_test(loop_shift);
    time_test(loop_shift_2);
    time_test(loop_shift_3);
    return 0;
}
