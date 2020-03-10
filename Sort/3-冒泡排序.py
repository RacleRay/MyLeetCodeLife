def bubbleSort(alist):
    lens = len(alist)
    for i in range(lens - 1):
        switchIdx = i  # 临时记录需要交换的位置，不必每次交换
        for j in range(i + 1, lens):
            if alist[switchIdx] > alist[j]:
                switchIdx = j
        alist[i], alist[switchIdx] = alist[switchIdx], alist[i]
    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(bubbleSort(l))