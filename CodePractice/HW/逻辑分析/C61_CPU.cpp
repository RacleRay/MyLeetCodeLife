#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <climits>

using namespace std;

int main() {
    int l1, l2;
    cin >> l1 >> l2;

    int sum_a = 0;
    vector<int> A(l1, 0);
    A.reserve(l1);

    for (int i = 0; i < l1; i++) {
        cin >> A[i];
        sum_a += A[i];
    }

    int sum_b = 0;
    set<int> B;
    for (int i = 0; i < l2; i++) {
        int b;
        cin >> b;
        B.insert(b);
        sum_b += b;
    }

    int a_minus_b = (sum_a - sum_b) / 2;

    int min_a = numeric_limits<int>().max();
    string ans;
    for (const auto &a: A) {
        int b = a - a_minus_b;
        if (B.count(b) > 0) {
            if (a < min_a) {
                min_a = a;
                ans = to_string(a) + " " + to_string(b);
            }
        }
    }

    cout << ans << endl;

    return 0;
}