#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_ROW (100)
#define MAX_ROW_LEN (10000)


typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    int size;
    Node *head;
    Node *tail;
} List;


List *new_link() {
    List *list = (List *)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}


void add_last(List *list, int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}


int remove_first(List *list) {
    if (list->size == 0) {
        exit(-1);
    }

    Node *removed = list->head;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
    }
    list->size--;

    int val = removed->val;
    free(removed);

    return val;
}


int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    getchar();

    List *lists[MAX_ROW];
    int nlists = 0;

    char s[MAX_ROW_LEN];
    while (fgets(s, sizeof(s), stdin)) {
        if (!strcmp(s, "\n")) {
            break;
        }

        List *list = new_link();
        char *token = strtok(s, " ");
        while (token != NULL) {
            add_last(list, atoi(token));
            token = strtok(NULL, " ");
        }

        lists[nlists++] = list;
    }


    int windows[k * n];
    int idx = 0;
    int level = 0;

    while (idx < k * n) {
        int bflag = 0;
        for (int i = 0; i < n; i++) {
            windows[idx++] = remove_first(lists[level]);

            if (lists[level]->size == 0 && nlists > 1) {
                for (int j = level + 1; j < nlists; j++) {
                    lists[j - 1] = lists[j];
                }
                nlists--;
                level %= nlists;
                bflag = 1;
            }
        }

        if (!bflag) {
            level = (level + 1) % nlists;
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < k; i++) {
            printf("%d", windows[i * n + j]);
            if (j != n - 1 || i != k - 1) {
                printf(" ");
            }
        }
    }

    return 0;
}

