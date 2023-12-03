"""
给定一个包含非负整数的数组，你的任务是统计其中可以组成三角形三条边的三元组个数。

示例 1:

输入: [2,2,3,4]
输出: 3
解释:
有效的组合是: 
2,3,4 (使用第一个 2)
2,3,4 (使用第二个 2)
2,2,3
注意:

数组长度不超过1000。
数组里整数的范围为 [0, 1000]。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-triangle-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

from typing import List

class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        """
        不同于 A + B = T 的问题，三角形是 A + B > T 的问题。
        同时求解的是 可行解的个数，利用排序数组，可以批量跳过一些不必要的判断
        N^3 -> NlogN + N^2
        """
        if not nums or nums.size() < 3: return 0

        nums.sort()

        ans = 0
        # 遍历最大的边，寻找可行的短边
        for lidx in range(2, len(nums)):
            # 优化的 two sum 求解
            ans += self.__triangleTravel(nums, lidx)

        return ans

    def __triangleTravel(self, nums: List[int], lidx: int) -> int:
        left, right = 0, lidx - 1
        long_edge = nums[lidx]
        count = 0
        while left < right:
            if nums[left] + nums[right] > long_edge:
                # 更长的left都满足
                count += right - left
                right -= 1
            else:
                left += 1
        return count
