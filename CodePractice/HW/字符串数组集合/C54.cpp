#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;


class Student {
public:
    string name;
    int *rank;

    Student(string name, int *rank): name(std::move(name)), rank(rank) {}
};


int main() {
    int n, m;
    cin >> n >> m;

    map<string, int> subject_rank_idx;
    for (int i = 0; i < m; i++) {
        string subject;
        cin >> subject;
        subject_rank_idx[subject] = i;
    }

    vector<Student> students;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;

        int* rank = new int[m + 1];
        int score_sum = 0;

        for (int j = 0; j < m; j++) {
            cin >> rank[j];
            score_sum += rank[j];
        }

        rank[m] = score_sum;

        students.emplace_back(name, rank);
    }

    string rank_subject;
    cin >> rank_subject;

    int rank_idx = subject_rank_idx.count(rank_subject) ? subject_rank_idx[rank_subject] : m;
    sort(students.begin(), students.end(), [rank_idx](const Student& a, const Student& b) {
        if (a.rank[rank_idx] == b.rank[rank_idx]) {
            return a.name < b.name;
        }
        return a.rank[rank_idx] > b.rank[rank_idx];
    });

    cout << students.front().name;
    students.erase(students.begin());
    for (auto &students: students) {
        cout << " " << students.name;
    }

    cout << endl;

    return 0;
}