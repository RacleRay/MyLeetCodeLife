#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;


int main() {
    int n;
    vector<int> heights, weights;

    cin >> n;
    heights.resize(n);
    heights.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    vector<int> person(n);
    // std::iota(person.begin(), person.end(), 1);
    for (int i = 0; i < n; i++) {
        person[i] = i + 1;
    }

    sort(person.begin(), person.end(), [&](int a, int b) {
        if (heights[a - 1] == heights[b - 1]) {
            if (weights[a - 1] == weights[b - 1]) {
                return a < b;
            }
            return weights[a - 1] < weights[b - 1];
        } else {
            return heights[a - 1] < heights[b - 1];
        }
    });

    for (int i = 0; i < n; i++) {
        cout << person[i] << " ";
    }

    cout << endl;

    return 0;
}
