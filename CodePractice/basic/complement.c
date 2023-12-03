/*************************************************************************
    > File Name: complement.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <stdio.h>

/*
  -n = ~(n - 1) = ~n + 1

  n的最后一个1：n & (-n)   n & ~(n - 1)   n & (-n + 1)

  n去掉整数中最后一个1：n & (n - 1)

  负数位运算：左移右边补1，结果仍是补码

  判断是否为-1：~n 是否为 0

  变号：~n + 1

  绝对值：(n ^ (n >> 31)) - (n >> 31)    n >> 31 就是 -1(n为负数时)

  对 p (2的次方) 取余： n & (p - 1)
  */

int main() {
    int num = 0;
    scanf("%d", &num);
    
    char bits[32] = {0};
    
    for (int i = 0; i < 32; ++i) {
        bits[i] = num & 1;
        num >>= (i + 1);
    }
    
    for (int i = 31; i >= 0; --i) {
        printf("%hhd", bits[i]);
    }
    printf("\n");

    return 0;
}
