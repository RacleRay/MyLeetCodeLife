#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>


using namespace std;
 
int main() {
    string s;
    getline(cin, s);

    istringstream iss(s);

    vector<int> times;
    int time;
    while (iss >> time) {
        times.push_back(time);
    }

    int max_time = 0;

    if (times.size() == 1) {
        cout << times[0] << endl;
        return 0;
    }

    queue<int> node_queue;
    node_queue.push(0);

    while (!node_queue.empty()) {
        int node = node_queue.front();
        node_queue.pop();

        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        if (left_child < times.size() && times[left_child] != -1) {
            times[left_child] += times[node];
            node_queue.push(left_child);
            max_time = max(max_time, times[left_child]);
        }

        if (right_child < times.size() && times[right_child] != -1) {
            times[right_child] += times[node];
            node_queue.push(right_child);
            max_time = max(max_time, times[right_child]);
        }
    }

    cout << max_time << endl;

    return 0;
}