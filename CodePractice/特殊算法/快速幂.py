#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   快速幂.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
求 a^n % b
"""


class Solution:
    def fast_power1(self, a, b, n):
        if n == 0:
            return 1 % b
        if n == 1:
            return a % b
        power = self.fast_power1(a, b, n // 2)
        power = (power * power) % b

        if n % 2 == 1:
            power = (power * a) % b

        return power

    def fast_power2(self, a, b, n):
        ans = 1
        while n > 0:
            if n % 2 == 1:
                ans = (ans * a) % b
            a = a * a % b
            n = n // 2
        return ans % b


if __name__ == "__main__":
    solution = Solution()
    print(solution.fast_power1(3, 128, 9))
    print(solution.fast_power2(3, 128, 9))