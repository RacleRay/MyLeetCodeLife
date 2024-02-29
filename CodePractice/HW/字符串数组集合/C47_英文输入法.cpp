#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>


using namespace std;


int main() {
    string sentence, prefix;

    getline(cin, sentence);
    getline(cin, prefix);

    replace_if(sentence.begin(), sentence.end(), [](char ch) { return !isalpha(ch); }, ' ');

    stringstream ss(sentence);

    set<string> word_set;
    string word;
    while (ss >> word) {
        word_set.insert(word);
    }
    
    string ans;
    for (auto s : word_set) {
        if (s.substr(0, prefix.length()) == prefix) {
            ans += s + " ";
        }
    }

    if (ans.length() > 0) {
        cout << ans << endl;
    } else {
        cout << prefix << endl;
    }

    return 0;
}