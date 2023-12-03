"""
给定一个候选数字的集合 candidates 和一个目标值 target。
找到 candidates 中所有的和为 target 的组合。 在同一个组合中, candidates 中的某个数字出现次数不限。
"""

# 所有数值(包括target ) 都是正整数
# 返回的每一个组合内的数字必须是非降序的
# 不能包含重复的组合

def combinationSum(candidates, target):
    results = []
    if not candidates:
        return results

    # 注意需要去重
    unique_sorted_numbers = sorted(list(set(candidates)))
    dfs(unique_sorted_numbers, 0, [], target, results)
    return results

def dfs(nums, index, result, target, results):
    if target == 0:
        results.append(list(target))
        return

    for i in range(index, len(nums)):
        if target < nums[i]:
            break

        result.append(nums[i])
        # i : 因为可以重复使用
        dfs(nums, i, result, target - nums[i], results)
        result.pop()