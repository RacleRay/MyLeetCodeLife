#!/usr/bin/env python
# -*- encoding: utf-8 -*-
'''
@File    :   rabin-karp.py
@Author  :   Racle
@Version :   1.0
@Desc    :   None
'''

PRIME = 72057594037927931     # < 2^{56}
DOMAIN = 128                  # 进制


def roll_hash(old_val, out_digit, in_digit, last_pos):
    """roll_hash ：向右移动窗口的递推hash值，减去左边第一个，加上右边下一个
    %PRIME -- 完成所有运算再取模，等价于分别取模之后再完成运算
    """
    val = (old_val - out_digit * last_pos + DOMAIN * PRIME) % PRIME
    val = (val * DOMAIN) % PRIME
    return (val + in_digit) % PRIME


def match(s, t, i, j, k):
    """当hash值相同时，进行检测。当PRIME很大，也可以不检测，因为hash冲突概率很小。"""
    for d in range(k):
        if s[i + d] != t[j + d]:
            return False
    return True


def rk_substring_check(s, t):
    """Find a substring by Rabin-Karp

    :param s: the source string
    :param t: the target string

    :returns: index i such that s[i: i + len(t)] == t, or -1
    :complexity: O(len(s) + len(t)) in expected time,
                and O(len(s) * len(t)) in worst case
    """
    hash_s = 0
    hash_t = 0
    len_s = len(s)
    len_t = len(t)
    last_pos = pow(DOMAIN, len_t - 1) % PRIME  # 从左向右第一个位置的常数项
    if len_s < len_t:              # substring too long
        return -1
    for i in range(len_t):
        hash_s = (DOMAIN * hash_s + ord(s[i])) % PRIME
        hash_t = (DOMAIN * hash_t + ord(t[i])) % PRIME
    for i in range(len_s - len_t + 1):
        if hash_s == hash_t:                # hashes match
            # check character by character
            if match(s, t, i, 0, len_t):
                return i
        if i < len_s - len_t:
            # shift window and calculate new hash on s
            hash_s = roll_hash(hash_s, ord(s[i]), ord(s[i + len_t]),
                               last_pos)
    return -1


def rk_common_string(s, t, k):
    """Find a common factor by Rabin-Karp

    :param int k: factor length
    :returns: (i, j) such that s[i:i + k] == t[j:j + k] or None.
              In case of tie, lexicographical minimum (i, j) is returned
    :complexity: O(len(s) + len(t)) in expected time,
                and O(len(s) + len(t) * k) in worst case
    """
    last_pos = pow(DOMAIN, k - 1) % PRIME
    pos = {}
    assert k > 0
    if len(s) < k or len(t) < k:
        return None
    hash_t = 0

    # 先找到其中一个序列的所有k长度的substring hash
    for j in range(k):
        hash_t = (DOMAIN * hash_t + ord(t[j])) % PRIME
    for j in range(len(t) - k + 1):
        # store the start position with the hash value
        if hash_t in pos:
            pos[hash_t].append(j)
        else:
            pos[hash_t] = [j]
        if j < len(t) - k:
            hash_t = roll_hash(hash_t, ord(t[j]), ord(t[j + k]), last_pos)

    hash_s = 0
    # Now check for matching factors in s
    for i in range(k):         # preprocessing
        hash_s = (DOMAIN * hash_s + ord(s[i])) % PRIME
    for i in range(len(s) - k + 1):
        if hash_s in pos:
            for j in pos[hash_s]:
                if match(s, t, i, j, k):
                    return (i, j)
        if i < len(s) - k:
            hash_s = roll_hash(hash_s, ord(s[i]), ord(s[i + k]), last_pos)
    return None


import unittest
import random
from kmp import knuth_morris_pratt

class Test(unittest.TestCase):
    def test_knuth_morris_pratt(self):
        for match in [rk_substring_check, knuth_morris_pratt]:
            p = "a" * 10 + "b"
            t = "a" * 100 + "b"
            self.assertEqual(match(t, p), len(t) - len(p))
            p = ''.join(map(str, [random.randint(0, 9) for _ in range(10)]))
            t = ''.join(map(str, [random.randint(0, 9) for _ in range(100)]))
            self.assertEqual(match(t, p), -1)  # hopefully
            self.assertEqual(match("ab", "a"), 0)
            self.assertEqual(match("ab", "b"), 1)
            self.assertEqual(match("ab", "c"), -1)
            self.assertEqual(match("", "c"), -1)


if __name__ == '__main__':
    unittest.main()