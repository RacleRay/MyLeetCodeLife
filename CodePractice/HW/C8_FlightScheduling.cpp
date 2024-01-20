#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;

int main() {
    string input;
    getline(cin, input);

    stringstream ss(input);
    string flight;

    vector<string> flights;
    while (getline(ss, flight, ',')) {
        flights.push_back(flight);
    }

    // 自定义比较规则
    // 返回 true 表示 a 小于 b
    // 返回 false 表示 a 大于等于 b
    sort(flights.begin(), flights.end(), [](const string& s1, const string& s2) {
        int prefix_cmp = s1.substr(0, 2).compare(s2.substr(0, 2));
        if (prefix_cmp == 0) {
            return s1.substr(2) < s2.substr(2);  // 后四位
        } else {
            return prefix_cmp < 0;  // 前两位
        }
    });

    for (int i = 0; i < flights.size(); i++) {
        cout << flights[i];
        if (i != flights.size() - 1) {
            cout << ",";
        }
    }

    return 0;
}
