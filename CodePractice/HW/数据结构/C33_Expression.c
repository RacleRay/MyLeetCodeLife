#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEN 200


typedef struct Fractions {
    int fa;
    int ch;
} Fractions;


Fractions* new_faction(int fa, int ch) {
    Fractions* f = (Fractions*)malloc(sizeof(Fractions));
    f->fa = fa;
    f->ch = ch;
    return f;
}


// 操作数栈
Fractions *oper_num[MAX_LEN];
int oper_num_len = 0;

// 操作符栈
char oper_sign[MAX_LEN];
int oper_sign_len = 0;


int gcd(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}


void calc() {
    Fractions *b = oper_num[--oper_num_len];
    Fractions *a = oper_num[--oper_num_len];

    char op = oper_sign[--oper_sign_len];

    Fractions *res = new_faction(1, 0);

    if (op == '+') {
        res->fa = a->fa * b->fa;
        res->ch = a->ch * b->fa + b->ch * a->fa;
    } else if (op == '-') {
        res->fa = a->fa * b->fa;
        res->ch = a->ch * b->fa - b->ch * a->fa;
    } else if (op == '*') {
        res->fa = a->fa * b->fa;
        res->ch = a->ch * b->ch;
    } else if (op == '/') {
        res->fa = a->fa * b->ch;
        res->ch = a->ch * b->fa;
    }

    oper_num[oper_num_len++] = res;
}


int main() {
    char s[MAX_LEN];
    fgets(s, MAX_LEN, stdin);

    int priority[128] = {0};
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;

    char num_str[MAX_LEN] = {0};
    int num_len = 0;

    int i = 0;
    while (s[i] != '\0') {
        char ch = s[i];

        if (ch >= '0' && ch <= '9') {
            while (ch >= '0' && ch <= '9') {
                num_str[num_len++] = ch;
                if (s[i + 1] == '\0') {
                    break;
                }
                i++;
                ch = s[i];
            }

            oper_num[oper_num_len++] = new_faction(1, strtol(num_str, NULL, 10));
            memset(num_str, 0, MAX_LEN);
            num_len = 0;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (oper_sign_len > 0 && oper_sign[oper_sign_len - 1] != '(' && priority[oper_sign[oper_sign_len - 1]] >= priority[ch]) {
                calc();
            }
            oper_sign[oper_sign_len++] = ch;
        } else if (ch == ')') {
            while (oper_sign[oper_sign_len - 1] != '(') {
                calc();
            }
            oper_sign_len--;
        } else if (ch == '(') {
            oper_sign[oper_sign_len++] = ch;
        }

        i++;
    }

    while (oper_sign_len > 1) {
        calc();
    }

    Fractions *res = oper_num[--oper_num_len];
    if (res->fa == 0) {
        puts("ERROR");
        return 0;
    }

    int k = gcd(res->fa, res->ch);
    res->fa /= k;
    res->ch /= k;

    if (res->fa * res->ch < 0) {
        printf("-");
    }

    int fa = abs(res->fa);
    int ch = abs(res->ch);
    if (fa == 1) {
        printf("%d\n", ch);
    } else {
        printf("%d/%d\n", ch, fa);
    }

    return 0;
}