"""
给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:

输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-product-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        if nums == []:
            return 0
        a = [0] * len(nums)
        a[0] = nums[0]
        minv = 0
        for i,j in enumerate(nums):
           if i > 0:
            a[i] = max(a[i-1] * j, j, minv * j)
            minv = min(a[i-1] * j, j, minv * j)
        return max(a)


    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if nums == []:
            return 0

        dp = [[0 for _ in range(2)] for _ in range(2)]

        # dp[0][1]: 当前最小值，包含nums[0]; dp[0][0]: 当前最大值，包含nums[0]
        dp[0][1], dp[0][0], res = nums[0], nums[0], nums[0]

        for i in range(1, len(nums)):
            x, y = i % 2, (i-1) % 2  # 1,0; 0,1 只需要两个位置，交替储存两个相邻轮次的值
            dp[x][0] = max(dp[y][0] * nums[i], dp[y][1] * nums[i], nums[i])
            dp[x][1] = min(dp[y][0] * nums[i], dp[y][1] * nums[i], nums[i])  # 考虑负负得正
            res = max(res, dp[x][0])

        return res


