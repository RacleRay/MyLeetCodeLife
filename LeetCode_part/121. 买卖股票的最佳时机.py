"""
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。

示例 1:

输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。
示例 2:

输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
# 121, 122, 123, 309, 188, 714
# 121: 只买卖1次
# 122：无数次
# 123：2次，只能有一份股票
# 309：冷却1天
# 188：交易最多k次
# 714：加上交易手续费

class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        # 解法1: dp
        if not prices: return 0

        res = 0

        profit = [[0 for i in range(3)] for i in range(len(prices))]

        profit[0][0] = 0 # 0天不操作
        profit[0][1] = -prices[0] # 0天买入
        profit[0][2] = 0 # 0天不能卖出

        for i in range(1, len(prices)):
            # 没有股票且不操作
            profit[i][0] = profit[i-1][0]
            # 没有股票选择买入 或者 已经买入不卖出
            profit[i][1] = max(profit[i-1][1], profit[i-1][0] - prices[i])
            # 有股票，选择卖出
            profit[i][2] = profit[i-1][1] + prices[i]
            res = max(res, profit[i][0], profit[i][1], profit[i][2])

        return res


        # 解法二
        if len(prices) <= 1:
            return 0

        min_price = prices[0]
        max_profit = 0
        for index in range(len(prices)):
            if prices[index] <= min_price:  # 记录最小价格
                min_price = prices[index]
            elif prices[index] - min_price > max_profit:  # 最大利润
                max_profit = prices[index] - min_price
        return max_profit
