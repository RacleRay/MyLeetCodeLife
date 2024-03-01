#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[55];
    int hot;
} Project;


Project *new_project(char *name, int hot) {
    Project *project = (Project *)malloc(sizeof(Project));
    strncpy(project->name, name, 51);
    project->hot = hot;
    return project;
}


char *lower(char *s) {
    char *res = (char *)calloc(55, sizeof(char));
    strncpy(res, s, 51);

    int diff = 'a' - 'A';

    int i = 0;
    while (res[i] != '\0') {
        if (res[i] >= 'A' && res[i] <= 'Z') {
            res[i] = (char)(res[i] + diff);
        }
        i++;
    }

    return res; 
}


int cmp(const void* a, const void *b) {
    Project *p1 = *((Project **)a);
    Project *p2 = *((Project **)b);

    if (p1->hot == p2->hot) {
        return strcmp(lower(p1->name), lower(p2->name));
    } else {
        return p2->hot > p1->hot;
    }
}


int main() {
    int n;
    scanf("%d", &n);

    int weights[5];
    for (int i = 0; i < 5; i++) {
        scanf("%d", &weights[i]);
    }

    Project *projects[n];

    for (int i = 0; i < n; i++) {
        char name[55];
        scanf("%s", name);

        int hot = 0;
        for (int j = 0; j < 5; j++) {
            int val;
            scanf("%d", &val);

            hot += val * weights[j];
        }

        projects[i] = new_project(name, hot);
    }

    qsort(projects, n, sizeof(Project*), cmp);
    for (int i = 0; i < n; i++) {
        puts(projects[i]->name);
    }

    return 0;
}