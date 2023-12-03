"""
https://www.lintcode.com/problem/18/
"""

from typing import (
    List,
)
import pysnooper

class Solution:
    """
    @param nums: A set of numbers.
    @return: A list of lists. All valid subsets.
             we will sort your return value in output
    """
    def subsets_with_dup(self, nums: List[int]) -> List[List[int]]:
        if not nums or len(nums) == 0:
            return [[]]
        nums.sort()
        results = []
        subset = []
        self.dfs(nums, 0, subset, results)
        return results

    @pysnooper.snoop()
    def dfs(self, nums, startIndex, subset, results):
        results.append([x for x in subset])
        for i in range(startIndex, len(nums)):
            # 跳过相同子集（相当于跳过了相同的前缀序列，结合pop理解）
            if (i != 0 and nums[i] == nums[i - 1] and i > startIndex):
                continue
            subset.append(nums[i])
            self.dfs(nums, i + 1, subset, results)
            subset.pop()

    def subsets_with_dup_iter(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        subsets = [[]]
        neighbor_dup_record = [-1]
        for i in range(len(nums)):
            for j in range(len(subsets)):
                # 如果有重复数字出现，只有前上一个数字选了才能选当前数字
                if i > 0 and nums[i] == nums[i - 1] and neighbor_dup_record[j] != i - 1:
                    continue
                subsets.append(list(subsets[j]))
                subsets[-1].append(nums[i])
                neighbor_dup_record.append(i) # neighbor_dup_record 和 subsets 一直保持着长度一致
        return subsets


if __name__ == '__main__':
    s = Solution()
    r = s.subsets_with_dup_iter([1, 2])
    print(r)