"""通过p=0.5的伯努利分布，生成p=0.25的伯努利分布"""
import random


def random1():
    return int(round(random.random()))


def random2():
    a = random1()
    b = random1()
    # a, b分别在不同bit位上显示
    bits = a | (b << 1)
    if bits == 0:
        return 0
    else:
        return 1