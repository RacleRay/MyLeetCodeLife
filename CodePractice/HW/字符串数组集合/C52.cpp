#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;


int main() {
    int m;
    cin >> m;

    int arr[m];
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }

    int n;
    cin >> n;

    // ===========================================

    if (n <= 0) {
        cout << -1;
        return 0;
    }

    set<int> s;

    for (int i = 0; i < m; i++) {
        if (arr[i] < 0 || arr[i] > 1000) {
            cout << -1;
            return 0;
        }
        s.insert(arr[i]);
    }

    if (s.size() < n * 2) {
        cout << -1;
        return 0;
    }

    vector<int> v(s.begin(), s.end());

    int l = 0;
    int r = v.size() - 1;
    int ans = 0;

    while (n > 0) {
        ans += v[l++] + v[r--];
        n--;
    }    


    cout << ans << "\n";

    return 0;
}