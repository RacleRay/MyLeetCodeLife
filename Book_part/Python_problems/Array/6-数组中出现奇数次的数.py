# 字典
from array import array

def get_single(arr):
    if arr is None:
        return None

    dic = {}
    for item in arr:
        if item not in dic:  # 0, 1分别代表偶数次和奇数次
            dic[item] = 1
        else:
            dic[item] = 0

    for k, v in dic.items():
        if v == 1:
            print('Single: ', k)


def get_single_xor(arr):
    if arr is None:
        return None

    result = 0
    position = 0

    for item in arr:
        result = result ^ item

    # 找到异或结果中为1的位置(第一个位置)
    tmp = result
    while tmp & 1 == 0:
        position += 1
        tmp >>= 1

    # 将所有position位置为1的数与result异或（两个single值之一）
    res_1 = 0
    for item in arr:
        if (item >> position) & 1 == 1:
            res_1 = res_1 ^ item

    res_2 = result ^ res_1  # 另一个single的值

    print(res_1, res_2)


if __name__ == "__main__":
    arr = array('B', [3, 5, 6, 6, 5, 7, 2, 2])
    get_single(arr)

    get_single_xor(arr)