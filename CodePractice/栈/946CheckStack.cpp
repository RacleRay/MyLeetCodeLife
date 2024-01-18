#include "../header.h"


class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;

        int i_pop = 0;
        for (int num : pushed) {
            stk.push(num);
            while (!stk.empty() && stk.top() == popped[i_pop]) {
                stk.pop();
                i_pop++;
            }
        }    

        return stk.empty();
    }
};