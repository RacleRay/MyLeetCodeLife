#include <numeric>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>


using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> map;

    for (auto str: strs) {
        string key = str;
        sort(key.begin(), key.end());
        map[key].push_back(str);
    }

    vector<vector<string>> result;
    for (auto it: map) {
        result.emplace_back(std::move(it.second));
    }

    return result;
}


vector<vector<string>> groupAnagrams2(vector<string>& strs) {
    auto hashfunc = [fn = hash<int>{}](const array<int, 26>& arr) {
        return std::accumulate(arr.begin(), arr.end(), 0, [fn](size_t acc, int num) {
            return (acc << 1) ^ fn(num);
        });
    };
    
    unordered_map<array<int, 26>, vector<string>, decltype(hashfunc)> map(0, hashfunc);

    for (auto& str: strs) {
        std::array<int, 26> tmp{};
        int len = str.length();

        for (int i = 0; i < len; ++i) {
            tmp[str[i] - 'a']++;
        }

        map[tmp].push_back(str);
    }

    vector<vector<string>> result;
    for (auto& it: map) {
        result.emplace_back(std::move(it.second));
    }

    return result;
}

