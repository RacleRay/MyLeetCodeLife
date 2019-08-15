"""
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-palindromic-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        res = ''
        for i in range(len(s)):
            tmp = max(self._findPalindrome(s, i, i),
                      self._findPalindrome(s, i, i+1), key=len)
            if len(res) < len(tmp):
                res = tmp
        return res

    def _findPalindrome(self, s, left_begin, right_begin):
        while left_begin >= 0 and right_begin < len(s) and s[left_begin] == s[right_begin]:
            left_begin -= 1
            right_begin += 1
        return s[left_begin + 1: right_begin]

