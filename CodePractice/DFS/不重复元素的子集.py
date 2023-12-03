"""
https://www.lintcode.com/problem/17/
"""

from typing import (
    List,
)

class Solution:
    """
    @param nums: A set of numbers
    @return: A list of lists
             we will sort your return value in output
    """
    def subsets(self, nums: List[int]) -> List[List[int]]:
        if not nums: return [[]]
        nums.sort()
        results = []
        dfs(nums, 0, [], results)
        return results

def dfs(nums, index, subset, results):
    if index == len(nums):
        results.append([x for x in subset])
        return

    subset.append(nums[index])
    dfs(nums, index + 1, subset, results)

    subset.pop()
    dfs(nums, index + 1, subset, results)

def dfs2(nums, startIndex, subset, results):
    results.append(subset[:])
    for i in range(startIndex, len(nums)):
        subset.append(nums[i])
        dfs2(nums, i + 1, subset, results)
        subset.pop()

def dfs3(nums, results):
    q = []  # stack
    q.append([])
    while (len(q) > 0):
        subset = q.pop()
        results.append(subset[:])
        for i in range(len(nums)):
            if not subset or subset[-1] < nums[i]:
                newsub = subset[:]
                newsub.append(nums[i])
                q.append(newsub)
    return results

def bits(nums, results):
    n = len(nums)
    for i in range(1 << n):
        subset = []
        for j in range(n):
            if i & (1 << j):
                subset.append(nums[j])
        results.append(subset)
    return results