#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node, *Node_p;

typedef struct Tree {
    int len;
    Node_p root;
} Tree;


Node *init(int data) {
    Node_p node = (Node_p)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
}


Node_p insert(Node_p root, int val) {
    if (!root) {
        Node_p node = init(val);
        return node;
    }

    if (root->data < val) {
        root->rchild = insert(root->rchild, val);
    } else {
        root->lchild = insert(root->lchild, val);
    }
}


void insert_no_return(Node_p *raddr, int val) {
    if (!(*raddr)) {
        *raddr = init(val);
        return;
    }

    if ((*raddr)->data < val) {
        insert_no_return(&((*raddr)->rchild), val);
    } else {
        insert_no_return(&((*raddr)->lchild), val);
    }

    return;
}


void insert_tree(Tree *tree, int val) {
    if (!tree) return;
    tree->root = insert(tree->root, val);
    tree->len++;
}


void clear(Node_p node) {
    if (node->lchild)
        clear(node->lchild);
    if (node->rchild)
        clear(node->rchild);
    free(node);
}


void clear_tree(Tree *tree) {
    if (tree->root) clear(tree->root);

    free(tree);

    return;
}