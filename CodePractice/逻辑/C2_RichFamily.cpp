#include <iostream>
#include <vector>

// https://blog.csdn.net/qfc_128220/article/details/134383453

using namespace std;

void solution(int n_node) {
    vector<int> wealth;
    wealth.reserve(n_node + 1);
    vector<int> family;
    family.reserve(n_node + 1);

    for (int i = 1; i <= n_node; i++) {
        cin >> wealth[i];
        family[i] = wealth[i]; 
    }

    int parent = 0, child = 0;
    for (int i = 0; i < n_node - 1; ++i) {
        cin >> parent >> child;
        family[parent] += wealth[child];
    }

    int max = family[1];
    for (int i = 2; i <= n_node; ++i) {
        max = max > family[i] ? max : family[i];
    }

    cout << max << endl;
}


int main() {
    int n_node = 0;
    cin >> n_node;

    solution(n_node);

    return 0;
}