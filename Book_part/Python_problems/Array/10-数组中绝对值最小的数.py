def findMin(arr):
    """查找数组中绝对值最小的数
    """
    if arr is None:
        return

    length = len(arr)

    sorted_arr = sorted(arr)

    if sorted_arr[0] > 0:
        return sorted_arr[0]
    elif sorted_arr[-1] < 0:
        return sorted_arr[-1]
    else:
        first_idx = 0
        last_idx = length - 1
        while True:
            mid = first_idx + ((last_idx - first_idx) >> 1)
            if sorted_arr[mid] == 0:
                return 0

            elif sorted_arr[mid] < 0:
                if sorted_arr[mid + 1] < 0:
                    first_idx = mid + 1
                elif sorted_arr[mid + 1] == 0:
                    return 0
                else:
                    return sorted_arr[mid] if abs(sorted_arr[mid]) < sorted_arr[mid + 1] \
                                            else sorted_arr[mid + 1]

            else:
                if sorted_arr[mid - 1] > 0:
                    last_idx = mid - 1
                elif sorted_arr[mid - 1] == 0:
                    return 0
                else:
                    return sorted_arr[mid] if sorted_arr[mid] < abs(sorted_arr[mid - 1]) \
                                            else sorted_arr[mid - 1]


if __name__ == "__main__":
    array = [9, 3, 3, -1, 12, -4, -5]
    print("res is: ", findMin(array))


