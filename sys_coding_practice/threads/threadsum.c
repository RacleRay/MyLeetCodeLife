/*************************************************************************
    > File Name: threadsum.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define BUFLEN 100

typedef struct args {
    char path[24];
    int  limit;
} args;

void* rountine(void* arg) {
    int       fd;
    char      buf[BUFLEN] = {0};
    long long res = 0, curval = 0;
    args*     parg = (args*)arg;
    if ((fd = open(parg->path, O_RDWR)) < 0) {
        perror("file open");
        exit(2);
    }

    while (1) {
        if (flock(fd, LOCK_EX) != 0) {
            perror("flock");
            exit(2);
        }

        lseek(fd, 0, SEEK_SET);
        if (read(fd, buf, BUFLEN) < 0) {
            perror("read");
            exit(1);
        }
        sscanf(buf, "%lld %lld", &res, &curval);

        if (curval > parg->limit) {
            close(fd);
            return NULL;
        }

        res += curval;
        ++curval;
        sprintf(buf, "%lld %lld", res, curval);

        lseek(fd, 0, SEEK_SET);
        if (write(fd, buf, BUFLEN) < 0) {
            perror("write");
            exit(1);
        }

        if (flock(fd, LOCK_UN) < 0) {
            perror("flock unlock");
            exit(1);
        }
    }

    return NULL;
}

int main(int argc, char** argv) {
    int       opt, nthred = 1;
    long long maxval      = 1000;
    char      buf[BUFLEN] = {0};
    while ((opt = getopt(argc, argv, "i:n:")) != -1) {
        switch (opt) {
        case 'i':
            nthred = atoi(optarg);
            printf("#thread is %d \n", nthred);
            break;
        case 'n':
            maxval = atol(optarg);
            printf("max val is %lld \n", maxval);
            break;
        default:
            fprintf(stderr, "Usage: %s -i [process] -n [limit]\n", argv[0]);
            exit(1);
        }
    }
    if (argc == 1) {
        printf("Using default config: i = 1, n = 1000\n");
    }

    // create a new file
    int fd = open("./fileitc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    write(fd, "0 1", BUFLEN);
    close(fd);


    // n threads work
    args parg;
    strncpy(parg.path, "./fileitc", 24);
    parg.limit = maxval;

    pthread_t tid[nthred];
    for (int i = 0; i < nthred; i++) {
        pthread_create(&tid[i], NULL, rountine, &parg);
    }

    void* sts;
    for (int i = 0; i < nthred; i++) {
        pthread_join(tid[i], &sts);
    }


    // print out result
    fd = open("./fileitc", O_RDONLY);
    lseek(fd, 0, SEEK_SET);
    if (read(fd, buf, BUFLEN) < 0) {
        perror("read");
        exit(1);
    }

    long long res, curval;
    sscanf(buf, "%lld %lld", &res, &curval);
    printf("Result is : %lld\n", res);

    close(fd);

    return 0;
}
