#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;


bool backtrace(vector<int> &tasks, vector<int> &workers, int idx, int limit) {
    if (idx >= tasks.size()) {
        return true;
    }

    int current = tasks[idx];
    for (int i = 0; i < workers.size(); i++) {
        if (i > 0 && workers[i] == workers[i - 1]) {
            continue;
        }

        if (workers[i] + current <= limit) {
            workers[i] += current;
            if (backtrace(tasks, workers, idx + 1, limit)) {
                return true;
            }
            workers[i] -= current;
        }

        if (workers[i] == 0 || workers[i] + current == limit) {
            break;
        }
    }

    return false;
}


bool can_finish(vector<int> &tasks, int n, int limit) {
    vector<int> workers(n, 0);
    return backtrace(tasks, workers, 0, limit);
}


int solve(vector<int> &tasks, int n) {
    sort(tasks.begin(), tasks.end(), greater<int>());

    int l = tasks[0], r = accumulate(tasks.begin(), tasks.end(), 0);
    while (l < r) {
        int mid = l + (r - l) / 2;

        if (can_finish(tasks, n, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}



int main() {
    vector<int> tasks;
    string inputs;

    getline(cin, inputs);
    istringstream iss(inputs);

    int val;
    while (iss >> val) {
        tasks.push_back(val);
    }    

    int n;
    cin >> n;

    cout << solve(tasks, n) << endl;

    return 0;
}