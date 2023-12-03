"""
Given n unique positive integers, number k and target.
Find all possible k integers where their sum is target.
"""

# 不可以重复使用数字
# 所有数值(包括target ) 都是正整数

def kSum(arr, k, target):
    # 在不去重条件下，不需要进行sort，也没有要求输出顺序
    subsets = []
    dfs(arr, 0, k, target, [], subsets)
    return subsets

def dfs(arr, index, k, target, subset, subsets):
    if k == 0 and target == 0:
        subsets.append(list(subset))
        return

    if k == 0 or target <= 0:
        return

    for i in range(index, len(arr)):
        subset.append(arr[i])
        dfs(arr, i + 1, k - 1, target - arr[i], subset, subsets)
        subset.pop()