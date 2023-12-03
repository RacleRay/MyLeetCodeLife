#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"


struct deque {
    size_t base;    // index of first element
    size_t length;  // number of elements
    size_t size;    // the size of contents
    int *contents;
};

#define INITIAL_SIZE (8)


static Deque* dequeCreateInternal(size_t size);

Deque* dequeCreate(void);
void dequePush(Deque* d, int direction, int value);
int dequePop(Deque*d, int direction);
int dequeIsEmpty(const Deque *d);
void dequeDestroy(Deque *d);


static Deque* dequeCreateInternal(size_t size) {
    struct deque *d;

    d = malloc(sizeof(struct deque));
    assert(d);

    d->base = 0;
    d->length = 0;
    d->size = size;

    d->contents = malloc(sizeof(int) * d->size);
    assert(d->contents);

    return d;
}


Deque *dequeCreate(void) {
    return dequeCreateInternal(INITIAL_SIZE);
}


void dequePush(Deque* d, int direction, int value) {
    struct deque *maysub;
    int *oldContent;

    // make sure there is enough space
    if (d->length == d->size) {
        maysub = dequeCreateInternal(INITIAL_SIZE * 2);

        while (!dequeIsEmpty(d)) {
            dequePush(maysub, DEQUE_BACK, dequePop(d, DEQUE_FRONT));
        }

        oldContent = d->contents;
        *d = *maysub;

        free(oldContent);
        free(maysub);
    }

    if (direction == DEQUE_FRONT) {
        if (d->base == 0) {
            d->base = d->size - 1;  // wrap around
        } else {
            d->base--;
        }

        d->length++;
        d->contents[d->base] = value;
    } else {
        d->contents[(d->base + d->length++) % d->size] = value;
    }
}


int dequePop(Deque*d, int direction) {
    int retval;

    if (dequeIsEmpty(d)) return DEQUE_EMPTY;

    if (direction == DEQUE_FRONT) {
        retval = d->contents[d->base];
        
        d->base = (d->base + 1) % d->size;
        d->length--;

        return retval;
    } else {
        return d->contents[(d->base + --d->length) % d->size];
    }
}


int dequeIsEmpty(const Deque *d) {
    return d->length == 0;
}


void dequeDestroy(Deque *d) {
    free(d->contents);
    free(d);
}
