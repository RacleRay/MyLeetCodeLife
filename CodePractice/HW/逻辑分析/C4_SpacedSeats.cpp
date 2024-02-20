#include <iostream>
#include <vector>

// https://blog.csdn.net/qfc_128220/article/details/130764903?spm=1001.2014.3001.5501

using namespace std;


static inline void solution() {
    std::string inputs;
    cin >> inputs;

    int res = 0, n_seats = inputs.size();
    bool left_empty, right_empty;
    for (int i = 0; i < n_seats; ++i) {
        if (inputs[i] == '1') {
            continue;
        }

        left_empty = (i == 0) || (inputs[i - 1] == '0');
        right_empty = (i == n_seats - 1) || (inputs[i + 1] == '0');

        if (left_empty && right_empty) {
            res++;
            inputs[i] = '1';
            ++i;
        }
    }

    cout << res << endl;
}


int main() {
    solution();

    return 0;
}