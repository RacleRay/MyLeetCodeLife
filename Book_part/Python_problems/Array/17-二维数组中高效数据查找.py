# python3


"""二维数组，从左到右，从上到下递增"""

def findItem(arr, target):
    if arr is None:
        return None

    ROW_TOTAL = len(arr)
    COL_TOTAL = len(arr[0])
    row_idx = 0
    col_idx = COL_TOTAL - 1
    # Binary Search two dimensions
    while row_idx < ROW_TOTAL and col_idx >= 0:
        if arr[row_idx][col_idx] == target:
            return True
        elif arr[row_idx][col_idx] > target:
            col_idx -= 1
        else:
            row_idx += 1

    return False


if __name__ == "__main__":
    array = [[1, 2, 3, 4, 5],
                [6, 7, 8, 9, 10],
                [11, 12, 13, 14, 15],
                [16, 17, 18, 19, 20],
                [21, 22, 23, 24, 25]]

    print(findItem(array, 11))
    print(findItem(array, 0))