#include <string>
#include <sstream>
#include <vector>
#include <iostream>


using namespace std;


struct App {
    string name{""};
    int prior{0};
    int start_time{0};
    int end_time{0};

    App(string name, int prior, int start_time, int end_time)
            : name(std::move(name)), prior(prior), start_time(start_time), end_time(end_time) {}
};


int convert(const string& s) {
    stringstream ss(s);

    string hours;
    getline(ss, hours, ':');

    string mins;
    getline(ss, mins, ':');

    return stoi(hours) * 60 + stoi(mins);
}


string solution(vector<App> &apps, int query) {
    vector<App> regs;

    for (const auto& app: apps) {
        if (app.start_time >= app.end_time) { continue; }

        vector<int> removed;
        bool flag = false;
        for (int j = 0; j < regs.size(); ++j) {
            App reg = regs[j];
            if (reg.start_time >= app.end_time || app.start_time >= reg.end_time) {
                continue;
            }

            if (app.prior > reg.prior) {
                removed.push_back(j);
            } else {
                flag = true;
            }
        }

        // no need to remove
        if (flag) {
            continue;
        }

        // must traval reverse
        for (int k = removed.size() - 1; k >= 0; --k) {
            int del_idx = removed[k];
            regs.erase(regs.begin() + del_idx);
        }

        regs.emplace_back(app);
    }

    string ans = "NA";
    for (const auto& app: regs) {
        if (app.start_time <= query && query < app.end_time) {
            ans = app.name;
            break;
        }
    }

    return ans;
}


int main() {
    int n;
    cin >> n;

    vector<App> apps;
    for (int i = 0; i < n; ++i) {
        string name;
        int prior;
        string start_time;
        string end_time;

        cin >> name >> prior >> start_time >> end_time;

        apps.emplace_back(name, prior, convert(start_time), convert(end_time));
    }

    string query_time;
    cin >> query_time;

    cout << solution(apps, convert(query_time)) << endl;

    return 0;
}