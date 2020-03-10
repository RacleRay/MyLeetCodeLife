from random import randint


def partition(alist, start, end):
    """3-way快排, 多重复值输入的情况，效果更好"""
    randPivot = randint(start, end)
    alist[end], alist[randPivot] = alist[randPivot], alist[end]
    pivot = alist[end]

    lessPivotP = start - 1
    equalPivotP = start
    greatPivotP = end
    while equalPivotP < greatPivotP:
        if alist[equalPivotP] < pivot:  # lessPivotP + 1即为 == pivot的第一个位置
            alist[equalPivotP], alist[lessPivotP + 1] = alist[lessPivotP + 1], alist[equalPivotP]
            equalPivotP += 1
            lessPivotP += 1
        elif alist[equalPivotP] == pivot:
            equalPivotP += 1
        else:
            alist[equalPivotP], alist[greatPivotP - 1] = alist[greatPivotP - 1], alist[equalPivotP]
            greatPivotP -= 1
    alist[end], alist[greatPivotP] = alist[greatPivotP], alist[end]
    # lessPivotP小于pivot的最后位置，greatPivotP大于pivot的第一个位置 - 1
    return lessPivotP, greatPivotP


def quicksorts(alist, start, end):
    if start > end: return None
    lessPivotP, greatPivotP = partition(alist, start, end)
    quicksorts(alist, start, lessPivotP)
    quicksorts(alist, greatPivotP + 1, end)  # greatPivotP + 1大于pivot的第一个位置


def quickSort(alist):
    if len(alist) <= 1:
        return alist
    quicksorts(alist, 0, len(alist) - 1)
    return alist


if __name__ == "__main__":
    l = [2, 3, 2, 4, 5, 5, 9, 8, 6]
    print(quickSort(l))