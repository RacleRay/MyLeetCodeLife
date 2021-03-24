#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <set>
#include <unordered_map>
#include <queue>
#include <functional>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;


class Solution {
public:
    string minNumber(vector<int>& nums) {
        vector<string> temp;
        for (int e: nums) {
            temp.push_back(to_string(e));
        }

        sort(temp.begin(), temp.end(), [](const string&a, const string&b){return a+b < b+a;});

        string result;
        for (string& t: temp){
            result += t;
        }

        return result;
    }
};