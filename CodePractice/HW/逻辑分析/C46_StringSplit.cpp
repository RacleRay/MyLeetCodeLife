#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;


int main() {
    int k;
    string ks;
    getline(cin, ks);
    k = stoi(ks);

    string s;
    getline(cin, s);

    vector<string> s_arr;
    size_t pos = 0;
    while ((pos = s.find("-")) != string::npos) {
        string token = s.substr(0, pos);
        s_arr.push_back(token);
        s.erase(0, pos + 1);
    }
    s_arr.push_back(s);

    string prefix = s_arr[0];
    string postfix;
    for (int i = 1; i < s_arr.size(); i++) {
        postfix += s_arr[i];
    }

    vector<char> postfix_chars(postfix.begin(), postfix.end());
    string new_s = "";
    for (int i = 0; i < postfix_chars.size(); i++) {
        if ((i + 1) % k == 0 && i + 1 != postfix_chars.size()) {
            new_s += postfix_chars[i];
            new_s += '-';
        } else {
            new_s += postfix_chars[i];
        }
    }

    vector<string> new_s_arr;
    pos = 0;
    while ((pos = new_s.find("-")) != string::npos) {
        string token = new_s.substr(0, pos);
        new_s_arr.push_back(token);
        new_s.erase(0, pos + 1);
    }
    new_s_arr.push_back(new_s);

    // deal with case
    string res = "";
    for (string str: new_s_arr) {
        int upper_case = count_if(str.begin(), str.end(), ::isupper);
        int lower_case = count_if(str.begin(), str.end(), ::islower);   

        if (upper_case > lower_case) {
            transform(str.begin(), str.end(), str.begin(), ::toupper);
            res += str;
            res += '-';
        } else if (upper_case < lower_case) {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            res += str;
            res += '-';
        } else {
            res += str;
            res += '-';
        }
    }

    res = res.substr(0, res.length() - 1);
    if (res.length() > 0) {
        cout << prefix << endl;
    } else {
        cout << prefix << "-" << res << endl;
    }

    return 0;
}