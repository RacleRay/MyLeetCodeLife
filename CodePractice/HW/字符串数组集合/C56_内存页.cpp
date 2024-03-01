#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


int main() {
    int n;
    cin >> n;

    map<int, int> cnts;
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;

        if (cnts.count(num) > 0) {
            cnts[num] += 1;
        } else {
            cnts[num] = 1;
        }
    }

    int threshold;
    cin >> threshold;

    vector<pair<int, int>> pairs;
    for (auto &pair : cnts) {
        if (pair.second >= threshold) {
            pairs.push_back(pair);
        }
    }

    cout << pairs.size() << endl;

    sort(pairs.begin(), pairs.end(), [](pair<int, int>&a, pair<int, int>&b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    for (const auto &item: pairs) {
        cout << item.first << endl;
    }

    return 0;
}