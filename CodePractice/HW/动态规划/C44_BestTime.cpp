#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;


int main() {
    int tolerated;
    cin >> tolerated;

    vector<int> fails;
    string line;
    getline(cin >> ws, line);

    istringstream iss(line);
    int num;
    while (iss >> num) {
        fails.push_back(num);
    }

    int arr_len = fails.size();
    vector<int> cumu_sum(arr_len);
    cumu_sum[0] = fails[0];
    for (int i = 1; i < arr_len; i++) {
        cumu_sum[i] = cumu_sum[i - 1] + fails[i];
    }

    vector<pair<int, int>> res;
    int max_len = 0;
    for (int start = 0; start < arr_len; start++) {
        for (int end = start; end < arr_len; end++) {
            int sum = (start == 0) ? cumu_sum[end] : cumu_sum[end] - cumu_sum[start - 1];
            int len = end - start + 1;
            int tolerated_sum = len * tolerated;

            if (sum <= tolerated_sum) {
                if (len > max_len) {
                    res.clear();
                    res.push_back(make_pair(start, end));
                    max_len = len;
                } else if (len == max_len) {
                    res.push_back(make_pair(start, end));
                }
            }
        }
    }

    if (res.empty()) {
        cout << "NULL" << endl;
    } else {
        sort(res.begin(), res.end());
        for (auto& item: res) {
            cout << item.first << "-" << item.second << " ";
        }
        cout << endl;
    }

    return 0;
}