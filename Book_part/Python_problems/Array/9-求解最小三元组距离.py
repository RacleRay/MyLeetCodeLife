"""三个升序数组中各找一个元素，使得三元组中最大和最小的距离尽可能小
"""

def min_item(a, b, c):
    res = a if a < b else b
    res = res if res < c else c
    return res


def max_item(a, b, c):
    res = a if a > b else b
    res = res if res > c else c
    return res


def minDistance(alist, blist, clist):
    cur_distance = 0
    min_distance = float("inf")
    min_ = 0

    i, j, k = 0, 0, 0
    while True:
        cur_distance = max_item(abs(alist[i] - blist[j]),
                                abs(alist[i] - clist[k]),
                                abs(blist[j] - clist[k]))
        if cur_distance < min_distance:
            min_distance = cur_distance

        min_ = min_item(alist[i], blist[j], clist[k])
        if min_ == alist[i]:
            i += 1
            if i >= len(alist):
                break
        elif min_ == blist[j]:
            j += 1
            if j >= len(blist):
                break
        else:
            k += 1
            if k >= len(clist):
                break

    return min_distance


if __name__ == "__main__":
    a = [3, 4, 5, 7, 15]
    b = [10, 12, 14, 16, 17]
    c = [20, 21, 23, 24, 37, 30]
    print("result is: ", minDistance(a, b, c))