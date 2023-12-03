"LintCode 285. 高楼大厦"

class Solution:
    def tallBuilding(self, arr):
        results = [1 for _ in range(len(arr))]
        self.count_buildings(arr, results, range(len(arr)))
        self.count_buildings(arr, results, range(len(arr) - 1, -1, -1))
        return results

    def count_buildings(self, arr, results, index_list):
        stack = []
        for i in index_list:
            results[i] += len(stack)
            while stack and arr[stack[-1]] <= arr[i]:
                stack.pop(-1)
            stack.append(i)