#include <iostream>
#include <string>

// https://blog.csdn.net/qfc_128220/article/details/134451796

using namespace std;


static inline void solution() {
    std::string inputs;
    cin >> inputs;

    int counts = 0;

    int i = 0;
    for (auto& ch: inputs) {
        counts += (ch == 'o');
    }

    cout << (counts % 2 == 0 ? inputs.size() : inputs.size() - 1);

    return;
}



int main() {
    solution();

    return 0;
}