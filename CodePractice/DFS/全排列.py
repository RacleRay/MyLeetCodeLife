def permute(nums):
    if not nums:
        return [[]]

    permutations = []
    dfs(nums, set(), [], permutations)
    return permutations


def dfs(nums, visited, permutation, permutations):
    if len(nums) == len(permutation):
        permutations.append(list(permutation))
        return

    for num in nums:
        if num in visited:
            continue
        permutation.append(num)
        visited.add(num)
        dfs(nums, visited, permutation, permutations)
        visited.remove(num)
        permutation.pop()


if __name__ == "__main__":
    nums = [1, 2, 3]
    res = permute(nums)
    print(res)