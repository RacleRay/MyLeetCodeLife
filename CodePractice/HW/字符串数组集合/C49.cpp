#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string &s, int k) {
    if (k <= 0) { return -1; }

    s += "0";

    map<char, int> cnts;

    char b = s[0];
    int len = 1;
    for (int i = 1; i < s.length(); i++) {
        char c = s[i];

        if (b == c) {
            len++;
        } else {
            if (cnts.count(b) == 0 || cnts[b] < len) {
                cnts[b] = len;
            }
            len = 1;
            b = c;
        }
    }

    vector<int> arr;
    for (const auto &item: cnts) {
        arr.push_back(item.second);
    }

    if (k > arr.size()) { return -1; }

    sort(arr.begin(), arr.end(), [](int next, int prev) { return prev > next; });
    return arr[k - 1];
}


int main() {
    string s;
    cin >> s;

    int k;
    cin >> k;

    cout << solution(s, k) << endl;

    return 0;
}