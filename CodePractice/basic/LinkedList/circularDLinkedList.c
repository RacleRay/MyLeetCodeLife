#include <stdlib.h>


#define RIGHT (0)
#define LEFT (1)


/**
 * @brief 这里可以在此结构体基础上，增加成员，通过强转为DLinkList指针，调用下列函数。
 *        这么做是可行的，甚至C++的继承也利用了这一机制。
 * 
 */
struct dLinkList {
    struct dLinkList *next[2];
};

typedef struct dLinkList *DLinkList;


DLinkList listCreate(void);
void listRemove(DLinkList e);
void listInsert(DLinkList head, int dir, DLinkList e);
void listSplit(DLinkList e1, DLinkList e2);
void listSplice(DLinkList e1, DLinkList e2);
void listDestroy(DLinkList e);


DLinkList listCreate(void) {
    DLinkList e;
    e = (DLinkList)malloc(sizeof(struct dLinkList));
    if (e) {
        e->next[LEFT] = e->next[RIGHT] = e;
    }
    return e;
}


void listRemove(DLinkList e) {
    e->next[RIGHT]->next[LEFT] = e->next[LEFT];  // remove e in LEFT direction
    e->next[LEFT]->next[RIGHT] = e->next[RIGHT]; // remove e in LEFT direction
}


void listInsert(DLinkList head, int dir, DLinkList e) {
    // point to neighbors
    e->next[dir] = head->next[dir];
    e->next[!dir] = head;

    // neighbors point to e
    e->next[dir]->next[!dir] = e;
    e->next[!dir]->next[dir] = e;
}

// remove all elements between e1 and e2, include e1 and e2, from linked list
void listSplite(DLinkList e1, DLinkList e2) {
    e2->next[RIGHT]->next[LEFT] = e1->next[LEFT];
    e1->next[LEFT]->next[RIGHT] = e2->next[RIGHT];

    e2->next[RIGHT] = e1;
    e1->next[LEFT] = e2;
}

/* splice a list starting at e2 after e1 */
void listSplice(DLinkList e1, DLinkList e2) {
    e2->next[LEFT]->next[RIGHT] = e1->next[RIGHT];
    e1->next[RIGHT]->next[LEFT] = e2->next[LEFT];

    e1->next[RIGHT] = e2;
    e2->next[LEFT] = e1;
}


void listDestroy(DLinkList e) {
    DLinkList target;
    DLinkList next;

    for (target = e->next[RIGHT]; target != e; target = next) {
        next = target->next[RIGHT];
        free(target);
    }

    free(e);
}