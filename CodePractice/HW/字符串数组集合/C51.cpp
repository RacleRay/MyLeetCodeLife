#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


int main() {
    string s;
    cin >> s;

    string min_s = s;

    sort(min_s.begin(), min_s.end());

    if (s != min_s) {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != min_s[i]) {
                char tmp = s[i];
                s[i] = min_s[i];

                auto swap_idx = s.rfind(min_s[i]);

                s[swap_idx] = tmp;
                break;
            }
        }
    }

    cout << s << endl;

    return 0;
}