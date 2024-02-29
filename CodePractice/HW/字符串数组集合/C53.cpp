#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>


using namespace std;


int main() {
    string s;

    cin >> s;

    stringstream ss(s);
    string token;
    vector<string> arr;
    while (getline(ss, token, ',')) {
        arr.emplace_back(token);
    }

    stable_sort(arr.begin(), arr.end(), [](string a, string b) {
        return a.back() < b.back();
    });

    cout << arr.front();
    arr.erase(arr.begin());
    for (const auto &i : arr) {
        cout << "," << i;
    }

    return 0;
}