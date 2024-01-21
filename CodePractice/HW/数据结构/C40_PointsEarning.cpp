#include <iostream>
#include <queue>
#include <vector>

using namespace std;


int main() {
    int num_tasks;
    cin >> num_tasks;

    int max_time;
    cin >> max_time;

    vector<priority_queue<int>> tasks_by_deadline(max_time + 1);
    for (int i = 0; i < num_tasks; i++) {
        int deadline, score;
        cin >> deadline >> score;

        if (deadline <= max_time) {
            tasks_by_deadline[deadline].push(score);
        }
    }

    int total_score = 0;
    priority_queue<int> remaining_tasks;

    for (int i = max_time; i > 0; i--) {
        while (!tasks_by_deadline[i].empty()) {
            remaining_tasks.push(tasks_by_deadline[i].top());
            tasks_by_deadline[i].pop();
        }

        if (!remaining_tasks.empty()) {
            total_score += remaining_tasks.top();
            remaining_tasks.pop();
        }
    }

    cout << total_score << endl;

    return 0;
}