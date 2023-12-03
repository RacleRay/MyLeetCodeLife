#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct Node {
    char         ch;
    double       freq;
    struct Node *lchild, *rchild;
} Node;

struct cmp {
    bool operator()(const Node* a, const Node* b) { return a->freq > b->freq; }
};

priority_queue<Node*, vector<Node*>, cmp> q;

Node* getNewNode(char ch, double freq, Node* lchild, Node* rchild) {
    Node* p   = (Node*)malloc(sizeof(Node));
    p->ch     = ch;
    p->freq   = freq;
    p->lchild = lchild;
    p->rchild = rchild;
    return p;
}

void clear(Node* root) {
    if (root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

Node* buildHuffman() {
    while (!q.empty()) {
        Node* a = q.top();
        q.pop();
        Node* b = q.top();
        q.pop();
        q.push(getNewNode(0, a->freq + b->freq, a, b));
    }
    return q.top();
}

void getHuffmanCode(Node* root, int k, char* buff, char* code[]) {
    if (root == NULL) return;
    buff[k] = 0;
    if (root->ch) {
        code[root->ch] = strdup(buff);
        return;
    }
    buff[k] = '0';
    getHuffmanCode(root->lchild, k + 1, buff, code);
    buff[k] = '1';
    getHuffmanCode(root->rchild, k + 1, buff, code);
    return;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char   ch[10];
        double freq;
        scanf("%s%lf", ch, &freq);
        q.push(getNewNode(ch[0], freq, NULL, NULL));
    }
    Node* root      = buildHuffman();
    char *code[256] = {0}, buff[100];

    getHuffmanCode(root, 0, buff, code);
    for (int i = 1; i < 256; i++) {
        if (code[i] == NULL) continue;
        printf("%c : %s\n", i, code[i]);
    }

    clear(root);
    return 0;
}