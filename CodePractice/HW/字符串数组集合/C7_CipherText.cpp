#include <iostream>
#include <string>


using namespace std;


int main() {
    string s;
    getline(cin, s);

    string res;

    for (size_t i = 0; i < s.length(); ) {
        if (i + 2 < s.length() && s[i + 2] == '*') {
            int num = (s[i] - '0') * 10 + s[i + 1] - '0';
            res += static_cast<char>('j' + num - 10);
            i += 3;
        } else {
            int num = s[i] - '0';
            res += static_cast<char>('a' + num - 1);
            ++i;
        }
    }

    cout << res << endl;

    return 0;
}