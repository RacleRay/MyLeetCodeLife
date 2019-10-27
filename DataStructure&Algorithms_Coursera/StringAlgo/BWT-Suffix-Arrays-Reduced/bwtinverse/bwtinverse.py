# python3
import sys
# from collections import OrderedDict

def InverseBWT(bwt):
    last = [(val, idx) for (idx, val) in enumerate(bwt)]
    first = sorted(last)

    first_to_last = {f: l for f, l in zip(first, last)}

    next = first[0]
    res = ''
    for i in range(len(bwt)):
        res += next[0]
        next = first_to_last[next]

    return res[: : -1]

    ###### method 2
    # length = len(bwt)
    # first_col = ''.join(sorted(bwt))
    # last_col = bwt
    # mark = [0] * length
    # order = OrderedDict()
    # order_mark = [0] * length
    #
    # for i, char in enumerate(last_col):
    #     num = order.get(char)
    #     if num is None:
    #         order[char] = 1
    #         order_mark[i] = 1
    #     else:
    #         num += 1
    #         order[char] = num
    #         order_mark[i] = num
    #
    # # 相对位置不变
    # # 处理第一行
    # prev_char = last_col[0]
    # res = prev_char + '$'
    # index = 0
    # mark[index] = 1
    #
    # while True:
    #
    #     order_ = order_mark[index]
    #     index = first_col.find(prev_char)
    #
    #     # 找到first col的正确位置
    #     count = 1
    #     while mark[index] == 1 or order_ != count:
    #         start = index + 1
    #         count += 1
    #         index = first_col.find(prev_char, start)
    #     mark[index] = 1
    #
    #     prev_char = last_col[index]
    #     if prev_char == '$':
    #         break
    #     res = prev_char + res
    #
    # return res


if __name__ == '__main__':
    # TTCCTAACG$A
    bwt = sys.stdin.readline().strip()
    print(InverseBWT(bwt))