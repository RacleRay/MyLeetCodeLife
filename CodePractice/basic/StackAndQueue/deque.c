#include "deque.h"


struct deque {
    struct deque *next[NUM_DIRECTIONS];
    int value;
};

Deque *dequeCreate(void) {
    Deque *d;
    d = malloc(offsetof(struct deque, value));

    if (d) {
        d->next[DEQUE_FRONT] = d->next[DEQUE_BACK] = d;
    }

    return d;
}


// a-->b-->c
// a<--b<--c
void dequePush(Deque *d, int direction, int value) {
    struct deque *newNode;

    assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

    newNode = malloc(sizeof(struct deque));
    assert(newNode);

    // 
    newNode->next[direction] = d->next[direction];
    newNode->next[!direction] = d;
    newNode->value = value;

    d->next[direction] = newNode;
    newNode->next[direction]->next[!direction] = newNode;
}


int dequePop(Deque *d, int direction) {
    struct deque *e;
    int retval;

    assert(direction == DEQUE_FRONT || direction == DEQUE_BACK);

    e = d->next[direction];

    // remove node
    d->next[direction] = e->next[direction];
    e->next[direction]->next[!direction] = d;

    retval = e->value;

    free(e);

    return retval;
}


int dequeEmpty(const Deque *d) {
    return d->next[DEQUE_FRONT] == d;
}


void dequeDestroy(Deque *d) {
    while (!dequeIsEmpty(d)) {
        dequePop(d, DEQUE_FRONT);
    }

    free(d);
}