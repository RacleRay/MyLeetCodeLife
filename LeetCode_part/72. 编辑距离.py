"""
给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
示例 1:

输入: word1 = "horse", word2 = "ros"
输出: 3
解释:
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2:

输入: word1 = "intention", word2 = "execution"
输出: 5
解释:
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/edit-distance
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
from functools import lru_cache

class Solution(object):
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        # DP
        # dp[i][j] -> 单词1的前i个字符到单词2的前j个字符，最少的变动次数

        # dp方程：1. i and j same                    -> dp[i-1][j-1]
        #         2. add to last i, so same as j     -> dp[i-1][j]
        #            or delete last j, so same as i
        #         3. delete last i, so same as j     -> dp[i][j-1]
        #            or add to last j, so same as i
        # dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1
        # NOTE: 可使用不同的权重，加在每个情况之后

        m, n = len(word1), len(word2)
        dp = [[0 for _ in range(n+1)] for _ in range(m+1)]

        for i in range(m+1): dp[i][0] = i
        for j in range(n+1): dp[0][j] = j

        for i in range(1, m+1):
            for j in range(1, n+1):
                dp[i][j] = min(dp[i-1][j-1] + (0 if word1[i-1]==word2[j-1] else 1),
                               dp[i-1][j],
                               dp[i][j-1])
        return dp[m][n]

    # 版本2：
    @lru_cache(maxsize=2**10)
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        if not word1 or not word2:
            return max(len(word1), len(word2))

        res = min(self.minDistance(word1[:-1], word2) + 1,
                  self.minDistance(word1, word2[:-1]) + 1,
                  self.minDistance(word1[:-1], word2[:-1]) + \
                             (0 if word1[-1]==word2[-1] else 1))

        return res

a = Solution()
res = a.minDistance('horse', 'ros')
print(res)