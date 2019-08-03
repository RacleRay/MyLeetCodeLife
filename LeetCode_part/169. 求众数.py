"""
给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在众数。

示例 1:

输入: [3,2,3]
输出: 3
示例 2:

输入: [2,2,1,1,1,2,2]
输出: 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/majority-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums) // 2
        count = {}
        for i in nums:
            count[i] = count.get(i, 0) + 1
            if count[i] > n:
                return i
        return None

        # 排序
        nums.sort()
        return nums[len(nums)//2]  # 总是存在的条件下

    # 分治
    def majorityElement(self, nums, low=0, high=None):
        def majority_element_rec(low, high):
            # base case; the only element in an array of size 1 is the majority
            # element.
            if low == high:
                return nums[low]

            # recurse on left and right halves of this slice. 找到左右众数
            mid = (high-low)//2 + low
            left = majority_element_rec(low, mid)
            right = majority_element_rec(mid+1, high)

            # if the two halves agree on the majority element, return it. 明显
            if left == right:
                return left

            # otherwise, count each element and return the "winner". 看左右不同的众数，谁更众
            left_count = sum(1 for i in range(low, high+1) if nums[i] == left)
            right_count = sum(1 for i in range(low, high+1) if nums[i] == right)

            return left if left_count > right_count else right

        return majority_element_rec(0, len(nums)-1)