"""
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
from collections import deque

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        start = maxLength = 0
        usedChar = {}

        for i in range(len(s)):
            # 不会考虑因重复而已经跳过的位置
            if s[i] in usedChar and start <= usedChar[s[i]]:
                start = usedChar[s[i]] + 1
            else:
                maxLength = max(maxLength, i - start + 1)
            usedChar[s[i]] = i
        return maxLength


    # dp
    # dp[i]--以s[i]为结尾的最长子序列长度
    # dp[i] = dp[i-1] + 1   ： 新char
    #         dp[i-1] + 1   ： 已有，但是dp[i-1]中也有重复
    #         i- usedChar[s[i]] : 已有，且dp[i-1]中无重复
    # 后两者明显取较小值
    if not s: return 0
    dp = [1] * len(s)
    usedChar = {s[0]: 0}
    maxLength = 1

    for i in range(1, len(s)):
        if s[i] in usedChar:
            dp[i] = min(dp[i-1] + 1, i - usedChar[s[i]])
        else:
            dp[i] = dp[i-1] + 1
        usedChar[s[i]] = i

    return max(dp)