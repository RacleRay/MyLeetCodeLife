def min_distance(arr, num1, num2):
    """两个可重复元素的最短距离
    """
    if arr is None:
        return

    last_num1 = -1
    last_num2 = -1
    min_dis = float('inf')

    i = 0
    while i < len(arr):

        if arr[i] == num1:
            last_num1 = i
            if last_num2 > 0:
                min_dis = min(min_dis, last_num1 - last_num2)

        elif arr[i] == num2:
            last_num2 = i
            if last_num1 > 0:
                min_dis = min(min_dis, last_num2 - last_num1)

        i += 1

    return min_dis


if __name__ == "__main__":
    arr = [4, 5, 1, 3, 1, 4, 2, 4, 2, 0, 1]
    print("result is: ", min_distance(arr, 1, 2))