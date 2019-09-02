"""详细算法介绍和性能对比见notebook"""

def bubbleSort(alist):
    exchange = False
    last_n = len(alist)

    for i in range(last_n, 0, -1):
        for j in range(i):
            if alist[j] > alist[i]:  # 从小到大排序
                alist[j], alist[i] = alist[i], alist[j]
                exchange = True
        if not exchange:
            break

    return alist
