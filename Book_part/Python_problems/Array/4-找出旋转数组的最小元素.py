"""把一个有序数组最开始的几个元素搬到数组末尾称之为数组旋转"""

def swap(array, low, high):
    while low < high:
        array[low], array[high] = array[high], array[low]
        low += 1
        high -= 1


def rotate_array(array, cut_idx):
    """实现数组旋转"""
    if array is None or cut_idx < 0 or cut_idx >= len(array):
        print('参数不合法')
        return

    if cut_idx == 0 or cut_idx == len(array) - 1:
        return

    swap(array, 0, cut_idx)
    swap(array, cut_idx + 1, len(array) - 1)
    swap(array, 0, len(array) - 1)


def find_min(array):
    """数组为从小到大"""
    if array is None:
        return

    def _find_min(array, low, high):
        """low -- 遍历左端起点
        high -- 遍历右端起点
        """
        if high < low:
            return array[0]

        if low == high:
            return array[low]

        mid = low + ((high - low) >> 1)
        if array[mid] < array[mid - 1]:
            return array[mid]
        elif array[mid + 1] < array[mid]:
            return array[mid + 1]
        elif array[high] > array[mid]:  # 在左半部分
            return _find_min(array, low, mid - 1)
        elif array[mid] > array[low]:  # 在右半部分
            return _find_min(array, mid + 1, high)
        else:  # 出现多个相同元素
            return min(_find_min(array, low, mid - 1),
                       _find_min(array, mid + 1, high))

    return _find_min(array, 0, len(array) - 1)


if __name__ == "__main__":
    array = [i for i in range(1, 10)]
    rotate_array(array, 4)
    print('res is: ', find_min(array))

    array2 = [0] + [1 for i in range(1, 9)]
    rotate_array(array2, 3)
    print('res is: ', find_min(array2))