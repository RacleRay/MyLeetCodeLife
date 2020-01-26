"""找到n个不同数值组成的数组中，随机删除一个后，被删除的数"""

# 方法一：累加求和再求差

# 方法二：异或法
def find_miss(array):
    if array is None:
        return

    ought_to_be = 0
    for i in range(1, len(array) + 2):  # 比array多一个元素
        ought_to_be ^= i

    array_res = 0
    for i in array:
        array_res ^= i

    return array_res ^ ought_to_be


if __name__ == "__main__":
    array = [1, 3, 4, 5, 6, 7, 8, 9]
    print('res: ', find_miss(array))