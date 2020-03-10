import math


def radixSort(alist, radix=10):
    k = int(math.ceil(math.log(max(alist), radix)))  # 位数
    buckets = [[] for i in range(radix)]
    for i in range(1, k + 1):
        for elem in alist:
            buckets[elem // (radix ** (i - 1)) % radix].append(elem)  # 根据每一轮不同位的数字进行排序
        del alist[:]
        # sort
        for buc in buckets:
            alist += buc
            del buc[:]  # reset for next position
    return alist


if __name__ == "__main__":
    l = [1230, 252, 214, 412, 587, 982]
    print(radixSort(l))