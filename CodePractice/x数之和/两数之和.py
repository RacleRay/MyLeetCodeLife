"""
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

 

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]
 

提示：

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案
进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""

from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        """
        哈希解法
        """
        hash_table ={}
        # check target - num, add num
        for i, num in enumerate(nums):
            if target - num in hash_table:
                return [hash_table[num], hash_table[target - num]]
            hash_table[num] = i

        return []

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        """
        双指针: 分别从两侧开始向中间遍历，注意左右指针的移动条件
        """
        if not nums: return []

        # sort
        nums_g = ((num, index) for index, num in enumerate(nums))
        nums_sorted = sorted(nums_g)

        left = 0, right = len(nums) - 1
        while left < right:
            # adjust sum
            if nums_sorted[left][0] + nums_sorted[right][0] > target:
                right -= 1
            if nums_sorted[left][0] + nums_sorted[right][0] < target:
                left += 1
            if nums_sorted[left][0] + nums_sorted[right][0] == target:
                return [nums_sorted[left][1], nums_sorted[right][1]]

        return []
