#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   kmp.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

"""
给定一个长度为 n 的字符串 s 和一个长度为 m 的待匹配模式字符串 t，
我们希望找到 t 在 s 中第一次出现时的下标 i。
当 t 不是 s 的子串 时，返回值应该是 -1。
"""

def maximum_border_length(w):
    "pattern和source联合起来，查找。sep，保证了查找不会超出pattern。"
    n = len(w)
    f = [0] * n                # init f[0] = 0，记录从开头开始的匹配记录。
    k = 0                      # current longest border length
    for i in range(1, n):      # compute f[i]
        while w[k] != w[i] and k > 0:
            k = f[k - 1]       # mismatch: try the next border
        if w[k] == w[i]:       # last characters match
            k += 1             # we can increment the border length
        f[i] = k               # we found the maximal border of w[:i + 1]
    return f


def knuth_morris_pratt(s, t):
    sep = '#'                   # special unused character
    assert sep not in t and sep not in s
    f = maximum_border_length(t + sep + s)
    n = len(t)
    for i, fi in enumerate(f):
        if fi == n:                # found a border of the length of t
            return i - 2 * n       # beginning of the border in s
    return -1


if __name__ == "__main__":
    s = "asfnasf"
    p = "nas"
    print(knuth_morris_pratt(s, p))