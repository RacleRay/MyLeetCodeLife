"""
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

示例 1:

输入: [3,3,5,0,0,3,1,4]
输出: 6
解释: 在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。
     随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。
示例 2:

输入: [1,2,3,4,5]
输出: 4
解释: 在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。  
     注意你不能在第 1 天和第 2 天接连购买股票，之后再将它们卖出。  
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
示例 3:

输入: [7,6,4,3,1]
输出: 0
解释: 在这个情况下, 没有交易完成, 所以最大利润为 0。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii
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
        if not prices: return 0

        # 3维：持股或者未持股；2维：已经交易几次；1维度：第几天
        profit = [[[0 for _ in range(2)] for _ in range(3)] for _ in range(len(prices))]

        profit[0][0][0], profit[0][0][1] = 0, -prices[0]  # 持股为买入，-prices[0
        profit[0][1][0], profit[0][1][1] = 0, -prices[0]
        profit[0][2][0], profit[0][2][1] = 0, 0  # 已交易两次，持股只能卖出

        for i in range(1, len(prices)):
            # 不操作
            profit[i][0][0] = profit[i-1][0][0]
            # 没有股票选择买入 或者 已经买入不卖出
            profit[i][0][1] = max(profit[i-1][0][1], profit[i-1][0][0] - prices[i])

            # 已经交易1次：买入 和 买入卖出
            profit[i][1][0] = max(profit[i-1][1][0], profit[i-1][0][1] + prices[i])
            profit[i][1][1] = max(profit[i-1][1][1], profit[i-1][1][0] - prices[i])

            # 已经交易2次，只能卖出现有 或者 已卖出什么都不能干
            profit[i][2][0] = max(profit[i-1][2][0], profit[i-1][1][1] + prices[i])

        end = len(prices) - 1
        return max(profit[end][0][0], profit[end][1][0], profit[end][2][0])


        # 解法二：
        if not prices: return 0
        hold1 = 0; hold2 = 0
        release1 = 0; release2 = 0

        for i in range(len(prices)):
            release2 = max(release2, hold2 + prices[i])  # 第二次交易
            hold2 = max(hold2, release1 - prices[i])
            release1 = max(release1, hold1 + prices[i])  # 第一次交易
            hold1 = max(hold1, -prices[i])

        return release2

