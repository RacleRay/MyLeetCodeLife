"""
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

示例 1:

输入: coins = [1, 2, 5], amount = 11
输出: 3
解释: 11 = 5 + 5 + 1
示例 2:

输入: coins = [2], amount = 3
输出: -1
说明:
你可以认为每种硬币的数量是无限的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/coin-change
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def coinChange(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        # 自下而上
        # DP: dp[i]--达到i状态的最少coins数
        # dp方程：dp[i] = min{dp[i - coins[j]]} + 1  # j为遍历所有的coin
        # dp[amount]为最终结果

        dp = [amount + 1 for _ in range(amount + 1)]  # 0到amount
        dp[0] = 0

        for i in range(amount + 1):
            for j in coins:
                if j <= i:
                    # 遍历可能的所有前一个状态，再加上当前步
                    dp[i] = min(dp[i], dp[i - j] + 1)

        # 初始赋值为amount + 1
        return dp[amount] if dp[amount] <= amount else -1


    # dp：自上而下的实现
    def coinChange(self, coins, amount):
        """
        :type coins: List[int]
        :type amount: int
        :rtype: int
        """
        if amount < 1: return 0
        dp = [0 for _ in range(amount)]
        return self._coinChange(coins, amount, dp)

    def _coinChange(self, coins, amount, dp):
        if amount < 0: return -1
        if amount == 0: return 0
        if dp[amount-1] != 0: return dp[amount-1]  # 说明更新了，至少是-1的值

        minCount = 2e10
        for j in coins:
            # 遍历前一个所有状态的结果
            res = self._coinChange(coins, amount - j, dp)
            if res >= 0 and res < minCount:
                minCount = res + 1

        dp[amount-1] = -1 if minCount == 2e10 else minCount  # 检查是否更新
        return dp[amount-1]