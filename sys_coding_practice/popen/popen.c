/*************************************************************************
    > File Name: popen.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t childpid = 0;

void myerror(const char* msg) {
    perror(msg);
    exit(-1);
}

FILE* myopen(const char* cmd, const char* type) {
    int   pipefd[2];
    pid_t pid;

    if (*type != 'r' && *type != 'w') {
        myerror("type");
    }

    if (pipe(pipefd) < 0) myerror("pipe");

    if ((pid = fork()) < 0) myerror("fork");

    if (pid == 0) {
        if (*type == 'r') {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }
        else {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
        }

        if (execlp("sh", "sh", "-c", cmd, NULL) < 0) myerror("exec");
    }

    FILE* fp = NULL;
    if (*type == 'r') {
        close(pipefd[1]);
        if ((fp = fdopen(pipefd[0], type)) == NULL) return NULL;
    }
    else {
        close(pipefd[0]);
        if ((fp = fdopen(pipefd[1], type)) == NULL) return NULL;
    }
    childpid = pid;

    return fp;
}

int mypclose(FILE* stream) {
    int   fd, stat;
    pid_t pid;

    if (childpid == 0) return -1;

    if (fclose(stream) == EOF) return -1;

    while (waitpid(childpid, &stat, 0) < 0)
        if (errno != EINTR) return -1;

    childpid = 0;
    return stat;
}


int main() {
    printf("\n>>> ===== TEST popen =====\n");

    FILE* fp = popen("cat ~/test.py", "r");
    if (!fp) {
        perror("popen");
        exit(1);
    }

    int c;
    while (~(c = fgetc(fp))) {
        putchar(toupper(c));
    }

    pclose(fp);

    printf("\n>>> ===== TEST myopen =====\n");

    FILE* fp2 = myopen("cat ~/test.py", "r");
    if (!fp2) {
        perror("popen");
        exit(1);
    }

    int cc;
    while (~(cc = fgetc(fp2))) {
        putchar(toupper(cc));
    }

    pclose(fp2);
    return 0;
}
