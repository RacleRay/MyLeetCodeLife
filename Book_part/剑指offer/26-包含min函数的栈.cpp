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

class MinStack
{
private:
    stack<int> mst;
    stack<int> st;

public:
    /** initialize your data structure here. */
    MinStack()
    {
    }

    void push(int x)
    {
        if (st.size() == 0 && mst.size() == 0)
        {
            st.push(x);
            mst.push(x);
            return;
        }
        else
        {
            if (x < mst.top())
            {
                st.push(x);
                mst.push(x);
                return;
            }
            else
            {
                st.push(x);
                mst.push(mst.top());
                return;
            }
        }
    }

    void pop()
    {
        st.pop();
        mst.pop();
    }

    int top()
    {
        return st.top();
    }

    int min()
    {
        return mst.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */

