#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>


using namespace std;


int main() {
    map<string, int> count_map;

    vector<string> lines;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        lines.push_back(line);
    }

    int n = stoi(lines[0]);
    for (int i = 1; i <= n; i++) {
        string part;
        stringstream ss(lines[i]);
        vector<string> parts;
        while (getline(ss, part, '/')) {
            parts.push_back(part);
        }

        for (int j = 1; j < parts.size(); j++) {
            string key = to_string(j) + '-' + parts[j];  // 层级-name
            count_map[key]++;
        }
    }

    stringstream ss(lines[n + 1]);
    string level, keyword;
    ss >> level >> keyword;

    string key = level + '-' + keyword;
    cout << (count_map.count(key) ? count_map[key] : 0) << endl;

    return 0;
}