#include <iostream>
#include <string>

using namespace std;


int main() {
    string s;
    getline(cin, s);

    int i = 0;
    while (i < s.length()) {
        if (s[i] == ',') {
            break;
        }
        i++;
    }

    int prefix_last = i - 1;
    int suffix_first = i + 1;

    while (s[prefix_last] == '/') {
        prefix_last--;
    }

    while (s[suffix_first] == '/') {
        suffix_first++;
    }

    string prefix = s.substr(0, prefix_last + 1);
    string suffix = s.substr(suffix_first);

    cout << prefix << "/" << suffix << "\n";
    
    return 0;
}