#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <limits.h>

using namespace std;

class Solution
{
public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        if (pushed.size() == 0 && popped.size() == 0)
            return true;
        if (pushed.size() == 0 || popped.size() == 0 || pushed.size() != popped.size())
            return false;

        int len = pushed.size();
        int popidx = 0;

        stack<int> st;
        for (int i = 0; i < len; i++)
        {
            st.push(pushed[i]);
            while (popidx < len && !st.empty() && st.top() == popped[popidx])
            {
                st.pop();
                popidx++;
            }
        }

        return st.empty();
    }
};