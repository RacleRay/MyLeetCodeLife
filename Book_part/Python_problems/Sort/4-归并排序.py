def mergeSort(alist):
    if len(alist) == 1:
        return alist

    split = len(alist) // 2
    left = alist[:split]
    right = alist[split:]

    left = mergeSort(left)
    right = mergeSort(right)

    if left[-1] <= right[0]:  # 有序时
        return left + right
    l = r = k = 0
    while l < len(left) and r < len(right):
        if left[l] <= right[r]:
            alist[k] = left[l]
            l += 1
        else:
            alist[k] = right[r]
            r += 1
        k += 1
    alist.extend(left[l:])
    alist.extend(right[r:])

    return alist



if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(mergeSort(l))