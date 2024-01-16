#include <stdio.h>
#include <stdlib.h>

/*#pragma pack(1)*/
typedef struct {
    short a1;
    char b1;
    double c1;
} AA;
/*#pragma pack()*/


typedef struct {
    unsigned char x1:1;  // low address
    unsigned char x2:3;
    unsigned char x3:4;  // high address
    unsigned char x5:4;  // high address
    unsigned char x4:8;
} BitField;


union uu {
    int a;
    char b;
};



void func(int *a, int n) {
    n = n / 4 * 4;
    a = (int*)__builtin_assume_+
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
}



int main() {
    int cc = 10;

    union uu u;
    u.a = 1;

    int aaa = 10;

    AA a;

    printf("%lu\n", sizeof(a));
    a.a1 = 1;


    BitField bf;
    bf.x1 = 0;
    bf.x2 = 3;
    bf.x3 = 0xc;

    printf("bf = %hhx\n", bf);
    printf("bf size = %lu\n", sizeof(bf));


    srand(48);
    for (int i = 0; i < 10; ++i) {
        printf("%d\t", rand());
    }
    printf("\n");

    return 0;
}