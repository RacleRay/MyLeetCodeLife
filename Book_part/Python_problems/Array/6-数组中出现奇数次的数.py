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


if __name__ == "__main__":
    arr = array('B', [3, 5, 6, 6, 5, 7, 2, 2])
    get_single(arr)