/*************************************************************************
    > File Name: head.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 1024

typedef struct IPCnode {
    pthread_mutex_t     mutex;
    pthread_mutexattr_t mutex_attr;
    pthread_cond_t      has_info;
    pthread_condattr_t  cond_attr;
    int                 buflen;
    int                 stat;
    char                buf[BUFLEN];
} IPCnode;


#endif
