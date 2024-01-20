#include <iostream>
#include <string>
#include <map>
#include <sstream>


using namespace std;


int main() {
    string inputs;
    getline(cin, inputs);

    istringstream iss(inputs);
    string token;
    map<char, string> tag_map;

    int i = 0;
    while (getline(iss, token, ',')) {
        tag_map['A' + i] = token;
        i++;
    }

    string res;
    for (const auto& item: tag_map) {
        int bi = item.second.find("<");
        int ei = item.second.find(">");

        if (bi == string::npos && ei == string::npos) {
            res += item.second + ",";
        }
        else if (bi == string::npos || ei == string::npos || bi > ei || ei - bi != 2) {
            cout << -1;
            return 0;
        } else {
            res += item.second.substr(0, bi) + tag_map[item.second[bi + 1]] + item.second.substr(ei + 1) + ",";
        }
    }

    cout << res.substr(0, res.length() - 1);

    return 0;
}