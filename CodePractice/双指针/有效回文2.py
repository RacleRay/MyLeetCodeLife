"""
给定一个非空字符串 s，请判断如果 最多 从字符串中删除一个字符能否得到一个回文字符串。

 

示例 1:

输入: s = "aba"
输出: true
示例 2:

输入: s = "abca"
输出: true
解释: 可以删除 "c" 字符 或者 "b" 字符
示例 3:

输入: s = "abc"
输出: false
 

提示:

1 <= s.length <= 105
s 由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/RQku0D
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

class Solution:
    def validPalindrome(self, s: str) -> bool:
        if not s: return False

        # find difference postion
        left_d, right_d = self.findDifference(s, 0, len(s) - 1)

        if left_d >= right_d:
            return True

        # check if it is vaild when delete one of the difference chars.
        return self.isPalindrome(s, left_d + 1, right_d) or \
               self.isPalindrome(s, left_d, right_d - 1)

    @staticmethod
    def isPalindrome(s, left, right):
        # no difference
        left_d, right_d = Solution.findDifference(s, left, right)
        return left_d >= right_d

    @staticmethod
    def findDifference(s, left, right):
        while left < right:
            if s[left] != s[right]:
                return left, right
            left += 1
            right -= 1
        return left, right


"""
```c++
class Solution {
public:
    bool isPalindrome(const string s, int i, int j) const {
        while (i < j) {
            if (s[i] == s[j]) {
                i++, j--;
                continue;
            } else return false;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int i = 0, j = s.length() - 1;
        while (i < j) {
            if (s[i] == s[j]) i++, j--;
            else {
                return isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);
            }
        }
        return true;
    }
};
"""
