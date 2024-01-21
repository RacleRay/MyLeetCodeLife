#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int m;
    cin >> m;
    // cin.ignore();

    std::vector<int> requirements;
    int work;
    while (cin >> work) {
        requirements.push_back(work);
    }

    // 从小到大
    sort(requirements.begin(), requirements.end());
    int sum = accumulate(requirements.begin(), requirements.end(), 0);

    int l = requirements.back();
    int r = requirements.back() + requirements[requirements.size() - 2];

    while (l < r) {
        int mid = l + (r - l) / 2;
        int need = 0;

        for (int i = requirements.size() - 1, j = 0; i >= j; i--) {
            if (requirements[i] > mid) {
                l = mid + 1;
                break;
            }

            if (i == j || requirements[i] + requirements[j] > mid) {
                need++;
            } else {
                j++;
                need++;
            }

            if (need > m) {
                l = mid + 1;
                break;
            }
        }

        if (need <= m) {
            r = mid;
        }
    }

    cout << l << endl;

    return 0;
}