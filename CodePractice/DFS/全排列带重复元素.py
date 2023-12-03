def permute(nums):
    if not nums:
        return [[]]

    permutations = []
    nums.sort()
    visited = [False for i in range(len(nums))]
    dfs(nums, visited, [], permutations)
    return permutations


def dfs(nums, visited, permutation, permutations):
    if len(nums) == len(permutation):
        permutations.append(list(permutation))
        return

    for i in range(len(nums)):
        if visited[i]:
            continue
        # 回溯时，跳过重复元素
        if (i > 0) and (nums[i] == nums[i - 1]) and not visited[i - 1]:
            continue
        permutation.append(nums[i])
        visited[i] = True
        dfs(nums, visited, permutation, permutations)
        visited[i] = False
        permutation.pop()


if __name__ == "__main__":
    nums = [1, 2, 2]
    res = permute(nums)
    print(res)