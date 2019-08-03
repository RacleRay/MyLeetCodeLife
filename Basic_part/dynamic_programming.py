#!/usr/bin/python
# encoding=utf8

"""
This program calculates the nth Fibonacci number in O(log(n)).
It's possible to calculate F(1000000) in less than a second.
"""
from __future__ import print_function
import sys

def fibonacci(n: int):
    if n < 0:
        raise ValueError("Negative args are not supported")
    return _fib(n)[0]

def _fib(n: int):
    """return (F(n), F(n-1))
    Arguments:
        n {int} -- 计算目标值
    """
    if n == 0:
        return (0, 1)
    else:
        # F(2n) = F(n)[2F(n+1) − F(n)]
        # F(2n+1) = F(n+1)^2+F(n)^2
        a, b = _fib(n // 2)
        c = a * (b * 2 - a)
        d = a * a + b * b
        if n & 1 == 0:
            return (c, d)
        else:
            return (d, c + b)


if __name__ == "__main__":
    # args = sys.argv[1:]
    # if len(args) != 1:
    #     print("Too few or too much parameters given.")
    #     exit(1)
    # try:
    #     n = int(args[0])
    # except ValueError:
    #     print("Could not convert data to an integer.")
    #     exit(1)
    # print("F(%d) = %d" % (n, fibonacci(n)))

    print("F(%d) = %d" % (100, fibonacci(100)))