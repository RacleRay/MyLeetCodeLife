"""
给一个一维数组，一开始站在下标 0
数组中每个值代表可以向右跳跃的最大距离
问是否能跳到最右边的下标
"""


class Solution:
    def canJump(self, A):
        if not A:
            return False

        n = len(A)
        # 能否调到 i
        dp = [False] * n
        dp[0] = True

        for i in range(1, n):
            for j in range(i):
                if dp[j] and j + A[j] >= i:
                    dp[i] = True
                    break
                # dp[i] = dp[i] or dp[j] and (j + A[j] >= i)

        return dp[n - 1]