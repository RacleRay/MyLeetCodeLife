#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (10000)


typedef struct Node {
    int val;
    struct Node *prev;
    struct Node *next;
} Node;


typedef struct CycleLink {
    Node *head;
    Node *tail;
    Node *cur;
    int size;
    int sum;
} CycleLink;


void add_node(CycleLink *cl, int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prev = NULL;
    node->next = NULL;

    if (cl->size == 0) {
        cl->head = node;
        cl->tail = node;
    } else {
        cl->tail->next = node;
        node->prev = cl->tail;
        cl->tail = node;
    }

    cl->size++;
    cl->sum += val;
}


CycleLink *new_cycle_link(int nums[], int nums_size) {
    CycleLink *cl = (CycleLink *)malloc(sizeof(CycleLink));
    cl->head = NULL;
    cl->tail = NULL;
    cl->cur = NULL;
    cl->size = 0;
    cl->sum = 0;

    for (int i = 0; i < nums_size; i++) {
        add_node(cl, nums[i]);
    }

    if (cl->head != NULL) {
        cl->head->prev = cl->tail;
        cl->tail->next = cl->head;
        cl->cur = cl->head;
    }

    return cl;
}


void remove_cur(CycleLink *cl) {
    cl->size--;
    cl->sum -= cl->cur->val;

    Node *prev = cl->cur->prev;
    Node *next = cl->cur->next;

    prev->next = next;
    next->prev = prev;

    cl->cur->prev = NULL;
    cl->cur->next = NULL;

    cl->cur = next;
}


void next_cur(CycleLink *cl) {
    cl->cur = cl->cur->next;
}


int sum_left(int nums[], int nums_size, int jump, int left) {
    CycleLink *cl = new_cycle_link(nums, nums_size);

    next_cur(cl);
    while (cl->size > left) {
        int zjump = jump % cl->size;
        for (int i = 0; i < zjump; i++) {
            next_cur(cl);
        }
        remove_cur(cl);
    }

    return cl->sum;
}


int main() {
    int nums[MAX_SIZE];
    int nums_size = 0;

    while (scanf("%d", &nums[nums_size++])) {
        if (getchar() != ',') { break; }
    }

    int jump;
    scanf("%d", &jump);

    int left;
    scanf("%d", &left);

    printf("%d\n", sum_left(nums, nums_size, jump, left));

    return 0;
}