"""20个数组，每个有500个元素，且每个数组有序拍好，找出其中前500的数。"""


import heapq
import random


def getRes(matrix, total):
    rowSize = len(matrix)
    colSize = len(matrix[0])
    result = []

    heap = []
    for i in range(rowSize):
        # (val, source row, col idx)
        # elem = (None, None, None)
        elem = (-matrix[i][0], i, 0)  # 每个数组的最大元素先加入
        heapq.heappush(heap, elem)  # 最小堆
        i += 1

    i = 0
    while i < total:
        minElem = heapq.heappop(heap)
        result.append(-minElem[0])

        source = minElem[1]
        colIdx = minElem[2]
        inputElem = (-matrix[source][colIdx + 1], source, colIdx + 1)
        heapq.heappush(heap, inputElem)
        i += 1

    return result


if __name__ == "__main__":
    m = [sorted([random.randint(1, 10000) for _ in range(500)], reverse=True) for _ in range(500)]
    # print(m)
    print(getRes(m, 500))