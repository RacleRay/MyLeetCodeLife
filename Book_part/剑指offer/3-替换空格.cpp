#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string replaceSpace(string s)
    {
        // inplace method
        int spaceCount = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
                spaceCount++;
        }

        int newLen = s.length() + spaceCount * 2;
        int oldLen = s.length();
        s.resize(newLen);
        for (int i = oldLen - 1; i >= 0 && newLen != i; --i)
        {
            if (s[i] != ' ')
                s[--newLen] = s[i];
            else
            {
                s[--newLen] = '0';
                s[--newLen] = '2';
                s[--newLen] = '%';
            }
        }

        return s;
    }
};