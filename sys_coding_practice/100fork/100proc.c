/*************************************************************************
    > File Name: 100proc.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    for (int i = 0; i < 100; ++i) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) break;
    }

    if (pid == 0) {
        printf("I`m the %dth child!\n", getpid());
        return 0;
    }
    else {
        int total = 0;
        for (int i = 0; i < 100; i++) {
            wait(0);
            total++;
        }
        printf(" %d children >>> THE END.\n", total);
    }

    return 0;
}
