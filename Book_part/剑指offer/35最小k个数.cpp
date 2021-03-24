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
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> result;
        if (k > arr.size()) return result;

        priority_queue<int, vector<int>, less<int>> priority;

        for (int e: arr){
            if (priority.size()<k)
                priority.push(e);
            else{
                if (priority.top() > e){
                    priority.pop();
                    priority.push(e);
                }
            }
        }

        while (!priority.empty()){
            result.push_back(priority.top());
            priority.pop();
        }

        return result;
    }
};