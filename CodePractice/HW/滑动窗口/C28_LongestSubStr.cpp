#include <iostream>
#include <deque>
#include <string>


using namespace std;

int main() {
    string str;
    cin >> str;

    int max_len = -1;
    bool has_letter = false;

    int l = 0, r = 0;
    deque<int> letter_idx;

    while (r < str.length()) {
        char ch = str[r];
        if (isalpha(ch)) {
            has_letter = true;
            letter_idx.push_back(r);

            if (letter_idx.size() > 1) {
                l = letter_idx.front() + 1;
                letter_idx.pop_front();
            }

            if (r == l) {
                r++;
                continue;
            }
        }

        max_len = max(max_len, r - l + 1);
        r++;
    }

    if (!has_letter) {
        cout << -1 << endl;
    } else {
        cout << max_len << endl;   
    }

    return 0;
}