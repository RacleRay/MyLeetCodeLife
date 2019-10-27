# python3
import sys
from functools import reduce


def BWT(text):
    text_cycles = [text]

    cycle = text
    for _ in range(1, len(text)):
        cycle = cycle[1: ] + cycle[0]
        text_cycles.append(cycle)

    text_cycles.sort()

    res = reduce(lambda txt_i, txt_j: txt_i + txt_j[-1], text_cycles)
    res = res[len(text) - 1: ]

    return res

if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    print(BWT(text))