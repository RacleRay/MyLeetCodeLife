/*************************************************************************
    > File Name: test.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <stdio.h>                
#include <string.h>
#include <stdlib.h>

int main() {
    char s[100];
    while (fgets(s, sizeof(100), stdin)) {
        if (!strcmp(s, "\n")) break;
        printf(">> %s, %ld\n", s, strlen(s));
    }


    return 0;
}
