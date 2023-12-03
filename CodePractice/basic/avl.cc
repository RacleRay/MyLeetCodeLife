#include <cstdio>
#include <cstring>
#include <sstream>
#include <stdint.h>
#include <string>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct Node {
    int          value, h;
    struct Node *left, *right;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor)) void init_NIL() {
    NIL->value = -1;
    NIL->h     = 0;
    NIL->left = NIL->right = NIL;
    return;
}

Node* getNewNode(int value) {
    Node* p  = (Node*)malloc(sizeof(Node));
    p->value = value;
    p->h     = 1;
    p->left = p->right = NIL;
    return p;
}

void update_h(Node* root) {
    root->h = max(root->left->h, root->right->h) + 1;
    return;
}

Node* left_rotate(Node* root) {
    // printf("left rotate : %d\n", root->value);
    Node* tmp   = root->right;
    root->right = tmp->left;
    tmp->left   = root;
    update_h(root);
    update_h(tmp);
    return tmp;
}

Node* right_rotate(Node* root) {
    // printf("right rotate : %d\n", root->value);
    Node* tmp  = root->left;
    root->left = tmp->right;
    tmp->right = root;
    update_h(root);
    update_h(tmp);
    return tmp;
}

const char* maintain_str[] = {"", "LL", "LR", "RL", "RR"};

Node* maintain(Node* root) {
    if (abs(root->left->h - root->right->h) <= 1) return root;

    // 高度差为 2
    int maintain_type = 0;
    // 左⼦树更⾼, 是⼀个L类型的失衡
    if (root->left->h > root->right->h) {
        if (root->left->right->h > root->left->left->h) {
            root->left    = left_rotate(root->left);
            maintain_type = 2;  // LR
        }
        else {
            maintain_type = 1;  // LL
        }
        root = right_rotate(root);
    }
    else {
        // 右⼦树更⾼, 是⼀个R类型的失衡
        if (root->right->left->h > root->right->right->h) {
            root->right   = right_rotate(root->right);
            maintain_type = 3;  // RL
        }
        else {
            maintain_type = 4;  // RR
        }
        root = left_rotate(root);
    }
    // printf("AVL maintain : %s\n", maintain_str[maintain_type]);
    return root;
}

Node* insert(Node* root, int target) {
    if (root == NIL) return getNewNode(target);
    if (root->value == target) return root;
    if (root->value > target) {
        root->left = insert(root->left, target);
    }
    else {
        root->right = insert(root->right, target);
    }
    update_h(root);
    return maintain(root);
}

Node* get_pre(Node* root) {
    Node* tmp = root;
    while (tmp->right != NIL) {
        tmp = tmp->right;
    }
    return tmp;
}

Node* erase(Node* root, int target) {
    if (root == NIL) return root;
    if (root->value > target) {
        root->left = erase(root->left, target);
    }
    else if (root->value < target) {
        root->right = erase(root->right, target);
    }
    else {
        if (root->left == NIL || root->right == NIL) {
            Node* tmp = (root->left != NIL ? root->left : root->right);
            free(root);
            return tmp;
        }
        else {
            Node* tmp   = get_pre(root->left);
            root->value = tmp->value;
            root->left  = erase(root->left, tmp->value);
        }
    }
    update_h(root);
    return maintain(root);
}

void clear(Node* root) {
    if (root == NIL) return;
    clear(root->left);
    clear(root->right);
    free(root);
    return;
}

void output(Node* root) {
    if (root == NIL) return;
    printf("(%d(%d) | %d, %d) \n", root->value, root->h, root->left->value,
           root->right->value);
    output(root->left);
    output(root->right);
    return;
}

int main() {
    srand(time(0));
    Node* root = NIL;
    int   n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        // int val = rand() % 100;
        int val = i;
        printf("\n insert %d to AVL : \n", val);
        root = insert(root, val);
        output(root);
    }
    clear(root);
    return 0;
}