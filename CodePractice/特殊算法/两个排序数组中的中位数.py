#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   两个排序数组中的中位数.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""

"""


class Solution:
    def find_median_of_two(self, A, B):
        t_len = len(A) + len(B)
        if t_len % 2 == 1:
            return self.find_kth(A, 0, B, 0, t_len // 2)
        print(self.find_kth(A, 0, B, 0, t_len // 2))
        print(self.find_kth(A, 0, B, 0, t_len // 2 + 1))

        return (self.find_kth(A, 0, B, 0, t_len // 2) + \
            self.find_kth(A, 0, B, 0, t_len // 2 + 1)) / 2.0

    def find_kth(self, A, a_start, B, b_start, k):
        # 视 A B 后续接上 无穷大 数值元素
        if a_start > len(A):
            return B[b_start + k - 1]
        if b_start > len(B):
            return A[a_start + k - 1]
        if k == 1:
            return min(A[a_start], B[b_start])

        a_key = 0
        b_key = 0
        if a_start + k // 2 - 1 < len(A):
            a_key = A[a_start + k // 2 - 1]
        else:
            a_key = float('inf')

        if b_start + k // 2 - 1 < len(B):
            b_key = B[b_start + k // 2 - 1]
        else:
            b_key = float('inf')

        if a_key < b_key:  # 第 k 个数，可能在 A 中后半段，或者 B 中
            return self.find_kth(A, a_start + k // 2, B, b_start, k - k // 2)
        else:
            return self.find_kth(A, a_start, B, b_start + k // 2, k - k // 2)


if __name__ == "__main__":
    solution = Solution()
    A = [1, 3, 5, 8, 12]
    B = [2, 4, 7, 11, 15]
    print(solution.find_median_of_two(A, B))
