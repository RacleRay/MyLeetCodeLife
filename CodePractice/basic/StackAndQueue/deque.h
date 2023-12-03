#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#define NUM_DIRECTIONS (2)


typedef struct deque Deque;

#define DEQUE_FRONT (0) 
#define DEQUE_BACK (1) 
#define DEQUE_EMPTY (-1)


Deque *dequeCreate(void);
void dequePush(Deque *d, int direction, int value);
int dequePop(Deque *d, int direction);
int dequeIsEmpty(const Deque *d);
void dequeDestroy(Deque *d);