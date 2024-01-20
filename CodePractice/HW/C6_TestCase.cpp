/*************************************************************************
    > File Name: C6_TestCase.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TestCase {
    int priority{0};
    int id{0};

    TestCase(int priority, int id) : priority(priority), id(id) {}
};


int main() {
    //int n, m;
    //cin >> n >> m;

    //vector<int> features;
    //int tmp = 0;
    //for (int i = 0; i < n; ++i) {
        //cin >> tmp;
        //features.push_back(tmp);
    //}

    //vector<TestCase> cases;
    //for (int i = 0; i < m; ++i) {
        //int feature_id;
        //int priority = 0;
        //while (scanf("%d", &feature_id)) {
            //priority += features[feature_id - 1];
            //if (getchar() != ' ') break;
        //}
        //cases.emplace_back(priority, i + 1);
    //}

    //sort(cases.begin(), cases.end());

    //for (auto& ca : cases) {
        //cout << ca.id << endl;
    //}

    int N, M;
    cin >> N >> M;

    vector<int> f_priorities(N);
    for (int i = 0; i < N; ++i) {
        cin >> f_priorities[i];
    }

    vector<TestCase> cases;
    for (int i = 0; i < M; ++i) {
        int priority_sum = 0;
        for (int j = 0; j < N; ++j) {
            int feat;
            cin >> feat;
            priority_sum += f_priorities[feat - 1];
        }
        cases.emplace_back(priority_sum, i + 1);
    }

    sort(cases.begin(), cases.end(), [](const TestCase &a, const TestCase& b) {
        if (a.priority == b.priority) {
            return a.id < b.id;
        }
        return a.priority > b.priority;
    });

    for (const auto& ca : cases) {
        cout << ca.id << endl;
    }

    return 0;
}

