"""
匹配出一个字符串中所有子串位置
"""

class Solution:
    def strstr(self, source, target):
        if not target: return 0

        for i in range(len(source) - len(target) + 1):
            for j in range(len(target)):
                if source[i + j] != target[j]:
                    break
            else:  # 没有遇到任何 break 语句. for else 语句块.
                return i

        return -1

    #########################################################################
    ### 方法2 robin_karp
    #########################################################################
    def robin_karp(self, source, target):
        """使用 hash 进行字符串匹配，作为KMP算法的一种替代"""
        hash_base, hash_size = 31, 2 ** 20 + 7

        if not source or not target: return -1
        m, n = len(source), len(target)
        if m < n: return -1

        top_power = 1
        for _ in range(n - 1):
            top_power = (top_power * hash_base) % hash_size

        target_hash, running_hash = 0, 0
        for i in range(n - 1):
            target_hash = (target_hash * hash_base + ord(target[i])) % hash_size
            running_hash = (running_hash * hash_base + ord(source[i])) % hash_size
        target_hash = (target_hash * hash_base + ord(target[n - 1])) % hash_size

        for end in range(n, m+1):
            i, j = end - n, end - 1
            running_hash = (running_hash * hash_base + ord(source[j])) % hash_size

            if running_hash == target_hash and source[i: end] == target:
                return i

            running_hash = (running_hash - ord(source[i]) * top_power) % hash_size

        return -1


if __name__ == "__main__":
    solution = Solution()

    print(solution.robin_karp("asdfasdgasdgasdgasdgasdgasdgasdfasdfwersdasdgasd", "wersda"))