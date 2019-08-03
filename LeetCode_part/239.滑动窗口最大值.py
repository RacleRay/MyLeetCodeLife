"""
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口 k 内的数字。滑动窗口每次只向右移动一位。

返回滑动窗口最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7]
解释:

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
注意：

你可以假设 k 总是有效的，1 ≤ k ≤ 输入数组的大小，且输入数组不为空。

进阶：

你能在线性时间复杂度内解决此题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sliding-window-maximum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
# import heapq

# class Solution(object):
#     def maxSlidingWindow(self, nums, k):
#         """
#         :type nums: List[int]
#         :type k: int
#         :rtype: List[int]
#         """
#         if k < 1 or k > len(nums):
#             return None
#         res = []
#         for i in range(0, len(nums)-k):
#             window = heapq.nlargest(k, nums[i:i+k])
#             res.append(window[0])
#         return res

from collections import deque

class Solution(object):
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        if n * k == 0:
            return []
        if k == 1:
            return nums
        # 暴力方法
        # res = []
        # window = deque(maxlen=k)
        # for i in nums[:k]:
        #     window.append(i)
        # res.append(max(window))
        # for i in nums[k:]:
        #     window.append(i)
        #     res.append(max(window))
        # return res

        def clean_deque(i):
            '删除将要移出window的值，删除较小的值'
            # remove indexes of elements not from sliding window
            if deq and deq[0] == i - k:  # i - k表示以i为结尾的window的前一个index（下一步的window）
                deq.popleft()

            # remove from deq indexes of all elements
            # which are smaller than current element nums[i]
            while deq and nums[i] > nums[deq[-1]]:  # 此时i还未插入，deq[-1]为当前的window尾
                deq.pop()                           # 直到，nums[i]不是最大（下一步时）

        # init deque and output
        deq = deque()
        max_idx = 0
        for i in range(k):  # i--代表了window的尾端index
            clean_deque(i)
            deq.append(i)
            # compute max in nums[:k]，记录还未满k时的最大，此时比较防止max_idx=0，而实际是1，2，3这种情况
            # 因为deque可能一直是一个元素，且不会进行popleft操作
            if nums[i] > nums[max_idx]:
                max_idx = i
        output = [nums[max_idx]]

        # build output
        for i in range(k, n):
            clean_deque(i)
            deq.append(i)
            # 开始popleft，保证了deq[0]一定是最大的，否则， while...deq.pop()会将其删除，而只有deq.append(i)
            # 的为一个最大元素
            output.append(nums[deq[0]])
        return output

# [1,3,-1,-3,5,3,6,7]
# 3
a = Solution()
res = a.maxSlidingWindow([1,3,-1,-3,5,3,6,7], 3)
print(res)