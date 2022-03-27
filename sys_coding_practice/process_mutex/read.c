/*************************************************************************
    > File Name: read.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "head.h"

void myerror(const char* msg) {
    perror(msg);
    exit(1);
}

void mutex_init(IPCnode* shnode) {
    if (pthread_mutexattr_init(&shnode->mutex_attr) < 0
        || pthread_mutexattr_setpshared(&shnode->mutex_attr,
                                        PTHREAD_PROCESS_SHARED)
               < 0)
        myerror("mutexattr init");
    if (pthread_condattr_init(&shnode->cond_attr) < 0
        || pthread_condattr_setpshared(&shnode->cond_attr,
                                       PTHREAD_PROCESS_SHARED)
               < 0)
        myerror("condattr init");
    if (pthread_mutex_init(&shnode->mutex, &shnode->mutex_attr) < 0
        || pthread_cond_init(&shnode->has_info, &shnode->cond_attr) < 0)
        myerror("mutex init");
}

int main() {
    key_t    fkey  = ftok("~/1.txt", 6);
    int      shmid = shmget(fkey, 1024, IPC_CREAT | 0666);
    IPCnode* node  = shmat(shmid, NULL, 0);

    (void)mutex_init(node);

    node->buflen     = 0;
    node->stat       = 0;
    int  retlen      = 0;
    int  tmplen      = 0;
    char buf[BUFLEN] = {0};
    while (1) {
        pthread_mutex_lock(&node->mutex);
        if (node->buflen == 0) {
            pthread_cond_wait(&node->has_info, &node->mutex);
        }

        strncpy(buf, node->buf, node->buflen);
        tmplen       = node->buflen;
        node->buflen = 0;

        pthread_mutex_unlock(&node->mutex);

        if ((retlen = write(1, buf, tmplen)) < 0) myerror("read to term");
        if (strncmp(buf, "quit", 4) == 0) break;
    }

    pthread_mutexattr_destroy(&node->mutex_attr);
    pthread_condattr_destroy(&node->cond_attr);
    pthread_mutex_destroy(&node->mutex);
    pthread_cond_destroy(&node->has_info);

    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
