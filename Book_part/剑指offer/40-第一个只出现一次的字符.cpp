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
    char firstUniqChar(string s) {
        unordered_map<char, int> umap;

        for (auto e: s){
            umap[e]++;
        }

        for (auto e: s){
            if (umap[e] == 1) return e;
        }

        return ' ';
    }
};