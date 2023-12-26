#include <iostream>
#include <vector>

using namespace std;


/**
 * @brief 
 * 
 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
 例如，当字符串为 We Are Happy. 则经过替换之后的字符串为 We%20Are%20Happy.
 */

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
        // i 遍历原字符串
        // newLen 指向新字符串的待插入位置
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