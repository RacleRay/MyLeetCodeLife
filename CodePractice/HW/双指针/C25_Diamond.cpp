#include <iostream>
#include <vector>


using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> gems(n);

    for (int i = 0; i < n; i++) {
        cin >> gems[i];
    }

    int money;
    cin >> money;

    int left = 0, right = 0, sum = 0;
    int max_gems = 0;

    while (right < gems.size()) {
        sum += gems[right];
        while (sum > money) {
            sum -= gems[left];
            left++;
        }

        max_gems = max(max_gems, right - left + 1);
        right++;
    }

    cout << max_gems << endl;
    return 0;
}