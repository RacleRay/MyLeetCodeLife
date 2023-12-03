#include "../header.h"


struct MinHeapNode {
    char         data;
    size_t       frequence{1};
    MinHeapNode *left{nullptr}, *right{nullptr};

    MinHeapNode(char data, size_t frequence)
        : data(data), frequence(frequence) {}

    explicit MinHeapNode(char data) : data(data) {}

    MinHeapNode() = delete;

    MinHeapNode(const MinHeapNode&)            = default;
    MinHeapNode& operator=(const MinHeapNode&) = default;

    MinHeapNode(MinHeapNode&&) noexcept            = default;
    MinHeapNode& operator=(MinHeapNode&&) noexcept = default;

    ~MinHeapNode() = default;
};


struct compare {
    bool operator()(MinHeapNode* node1, MinHeapNode* node2) {
        return node1->frequence > node2->frequence;
    }
};


auto huffman_code(char data[], size_t frequence[], size_t n) {
    MinHeapNode *left, *right, *parent;

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (size_t i = 0; i < n; i++) {
        minHeap.push(new MinHeapNode(data[i], frequence[i]));
    }

    while (minHeap.size() > 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // @ : internal node label
        parent       = new MinHeapNode('@', left->frequence + right->frequence);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    return minHeap;
}

void print_codes(MinHeapNode* root, string str) {
    if (!root) {
        return;
    }

    if (root->data != '@') {
        std::cout << "Huffman code of " << root->data << " with frequence "
                  << root->frequence << ": " << str << std::endl;
    }

    // 0 for going left, 1 for going right
    print_codes(root->left, str + "0");
    print_codes(root->right, str + "1");
}


void free_huffman_tree(MinHeapNode* root) {
    if (!root) {
        return;
    }

    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    delete root;
}


int main() {
    char   arr[]  = {'a', 'b', 'c', 'd', 'e', 'f'};
    size_t freq[] = {1, 2, 3, 4, 5, 6};

    auto minHeap = huffman_code(arr, freq, sizeof(arr) / sizeof(arr[0]));

    print_codes(minHeap.top(), "");

    free_huffman_tree(minHeap.top());

    return 0;
}