/*************************************************************************
    > File Name: write.c
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#include "head.h"

void myerror(const char* msg) {
    perror(msg);
    exit(1);
}

int main() {
    key_t fkey  = ftok("~/1.txt", 6);
    int   shmid = shmget(fkey, 1024, IPC_EXCL | 0666);
    if (shmid < 0) {
        myerror("shmget");
    }

    IPCnode* node   = shmat(shmid, NULL, 0);
    int tmplen = 0;
    char buf[BUFLEN] = {0};
    while (1) {
        if ((tmplen = read(0, buf, BUFLEN)) < 0)
            myerror("read from stdin");

        pthread_mutex_lock(&node->mutex);

        /*printf(">> %s", node->buf);*/
        /*printf(">> %d", node->buflen);*/
        strncpy(node->buf, buf, tmplen);
        node->buflen = tmplen;

        if (strncmp(node->buf, "quit", 4) == 0) {
            pthread_cond_signal(&node->has_info);
            pthread_mutex_unlock(&node->mutex);
            break;
        }

        pthread_cond_signal(&node->has_info);
        pthread_mutex_unlock(&node->mutex);
    }

    return 0;
}
