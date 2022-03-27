/*************************************************************************
    > File Name: easyexec.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv) {
    int  opt;
    char msg[1024] = {0};
    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
        case 'm':
            strncpy(msg, optarg, strlen(optarg));
            break;
        default:
            fprintf(stderr, "Usage: %s [-m] string\n", argv[0]);
            exit(1);
        }
    }

    if (strlen(msg) > 0) {
        printf("%s\n", msg);
        return 0;
    }

    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        execlp("vim", "vim", "tmp.txt", NULL);
        perror("vim exec");
        exit(-1);
    }

    // parent wait
    wait(0);
    // no need for another fork. But it`s a way to solve this problem.
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        execlp("cat", "cat", "tmp.txt", NULL);
        perror("cat exec");
        exit(-1);
    }

    wait(0);
    return 0;
}
