def shiftDown(alist, bound, idx):
    elem = alist[idx]
    while (idx + 1) * 2 < bound:
        leftChild = idx * 2 + 1
        rightChild = leftChild + 1
        maxChild = leftChild
        if rightChild < bound and alist[rightChild] > alist[leftChild]:
            maxChild = rightChild
        if elem >= alist[maxChild]:
            break
        alist[idx] = alist[maxChild]
        idx = maxChild
    alist[idx] = elem


def heapSort(alist):
    # build max heap
    lens = len(alist)
    idx = (lens - 1 - 1) // 2  # 最后一父节点的index
    while idx >= 0:
        shiftDown(alist, lens, idx)
        idx -= 1

    # extract max, shiftDown
    unsorted_bound = lens - 1
    while unsorted_bound > 0:
        alist[0], alist[unsorted_bound] = alist[unsorted_bound], alist[0]
        shiftDown(alist, unsorted_bound, 0)
        unsorted_bound -= 1

    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(heapSort(l))