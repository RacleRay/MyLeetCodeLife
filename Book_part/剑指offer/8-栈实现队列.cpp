
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

class CQueue
{
public:
    CQueue()
    {
        while (!stackIn.empty())
        {
            stackIn.pop();
        }
        while (!stackOut.empty())
        {
            stackOut.pop();
        }
    }

    void appendTail(int value)
    {
        stackIn.push(value);
    }

    int deleteHead()
    {
        if (stackIn.empty() && stackOut.empty())
            return -1;

        int value = -1;
        if (stackOut.empty())
        {
            while (!stackIn.empty())
            {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
        if (!stackOut.empty())
        {
            value = stackOut.top();
            stackOut.pop();
        }
        return value;
    }

private:
    stack<int> stackIn, stackOut;
};
