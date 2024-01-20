#include <iostream>
#include <string>

using namespace std;


int main() {
    string ss, sl;

    getline(cin, ss);
    getline(cin, sl);   

    int idx_s = 0;
    int idx_l = 0;

    while (idx_s < ss.length() && idx_l < sl.length()) {
        if (ss[idx_s] == sl[idx_l]) {
            idx_s++;
        }
        idx_l++;
    }

    if (idx_s == ss.length()) {
        cout << idx_l - 1 << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}