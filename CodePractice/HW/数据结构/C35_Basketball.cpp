#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    string inputs;
    string outputs;

    getline(cin, inputs);
    getline(cin, outputs);

    vector<int> in;
    istringstream iss(inputs);
    string tmp;
    while (getline(iss, tmp, ',')) {
        in.push_back(stoi(tmp));
    }

    vector<int> out;
    istringstream oss(outputs);
    while (getline(oss, tmp, ',')) {
        out.push_back(stoi(tmp));
    }


    deque<int> basket;
    int idx = 0;

    string res;
    for (auto& elem: in) {
        basket.push_back(elem);
        while (!basket.empty()) {
            int left = basket.front();
            int right = basket.back();
            if (left == out[idx]) {
                res.push_back('L');
                basket.pop_front();
                idx++;
            } else if (right == out[idx]) {
                res.push_back('R');
                basket.pop_back();
                idx += 1;
            } else {
                break;
            }
        }
    }

    if (basket.size() != 0) {
        cout << "NO" << endl;
    } else {
        cout << res << endl;
    }

    return 0;
}