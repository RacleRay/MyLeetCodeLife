"""
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        if len(nums) < 3:
            return []
        nums.sort()  # 防止重复解出现，元素顺序不同
        res = set()
        for i, v in enumerate(nums[:-2]):  # 第一个值a，来遍历
            if i >= 1 and v == nums[i-1]:  # 相同元素跳过，避免重复解，已排序
                continue
            d = {}
            for x in nums[i+1:]:  # 第2，3个值
                if x not in d:  # 若x不在，将对应目标加入
                    d[-v-x] = 1
                else:           # 下一次当遇到这个目标，说明符合x的目标在后面存在，得出解
                    res.add((v, -v-x, x))
        return map(list, res)


        # res = []
        # nums.sort()
        # for i in range(len(nums)-2):
        #     if i > 0 and nums[i] == nums[i-1]:
        #         continue

        #     l, r = i+1, len(nums)-1
        #     while l < r:
        #         # 以和为标准，两边向中间靠
        #         s = nums[i] + nums[l] + nums[r]
        #         if s < 0: l += 1
        #         elif s > 0: r += 1
        #         else:  # 找到解
        #             res.append((nums[i], nums[l], nums[r]))

        #             # 防止重复解
        #             while l < r and nums[l] == nums[l+1]:
        #                 l += 1
        #             while l < r and nums[r] == nums[r-1]:
        #                 r -= 1
        #             l += 1; r -= 1
        # return res


# [-1,0,1,2,-1,-4]
# [-4,-1,-1,0,1,2]