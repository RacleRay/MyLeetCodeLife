#include "tree.h"
#include <stdio.h>


Node *build_demo() {
    Node *node = init(1);
    node->lchild = init(2);
    node->rchild = init(3);
    node->lchild->lchild = init(4);
    node->lchild->rchild = init(5);
    node->rchild->rchild = init(6);
    return node;
}


void preorder(Node_p node) {
    if (!node) return;

    printf("%c ", node->data);
    preorder(node->lchild);
    preorder(node->rchild);

    return;
}


void inorder(Node_p node) {
    if (!node) return;

    inorder(node->lchild);
    printf("%c ", node->data);
    inorder(node->rchild);

    return;
}


void postorder(Node_p node) {
    if (!node) return;

    postorder(node->lchild);
    postorder(node->rchild);
    printf("%c ", node->data);

    return;
}





Node_p build_from_pre_in(char pre_str[], char in_str[], int len) {
    Node_p p = init(pre_str[0]);
    int pos = strchr(in_str, pre_str[0]) - in_str;
    
    if (pos > 0) {
        // 从根节点开始，递归复原左子树
        p->lchild = build_from_pre_in(pre_str + 1, in_str, pos);
    }
    if (len - pos - 1 > 0) {
        p->rchild = build_from_pre_in(pre_str + pos + 1, in_str + pos + 1, len - pos - 1);
    }

    return p;
}


Node_p build_from_post_in(char post_str[], char in_str[], int len) {
    Node_p p = init(post_str[len - 1]);
    int pos = strchr(in_str, post_str[len - 1]) - in_str;

    if (pos > 0) {
        p->lchild = build_from_post_in(post_str, in_str, pos);
    }
    if (len - pos - 1 > 0) {
        p->rchild = build_from_post_in(post_str + pos, in_str + pos + 1, len - pos - 1);
    }

    return p;
}


int main() {
    Node_p res = build_from_pre_in("abdgcefh", "dgbaechf", 8);
    Node_p res2 = build_from_post_in("DECBHGFA", "BDCEAFHG", 8);

    postorder(res);
    puts("");
    inorder(res2);

    return 0;
}
