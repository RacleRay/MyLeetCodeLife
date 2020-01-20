"""N + M个自然数元素中，找出M个重复的元素"""


def find_duplicate(array, dup_num):
    res = set()
    if len(array) == 0:
        return res

    length = len(array)
    idx = array[0]  # 元素为下一个遍历位置的索引
    dup_num -= 1

    while True:
        # 遇到重复元素，让遍历能够访问到后面的元素，指向 length - dup_num 的索引，保证遍历完所有元素
        if array[idx] < 0:
            dup_num -= 1
            array[idx] = length - dup_num
            res.add(idx)

        if dup_num == 0:
            return res

        array[idx] *= -1  # 遍历后改变值符号，已遍历idx处的值将会是负数
        idx = array[idx] * -1  # 下一个遍历位置

if __name__=='__main__':
    array = [1, 2, 3, 3, 3, 4, 5, 5, 5, 5, 6]
    dup_num = 5

    for i in find_duplicate(array, dup_num):
        print(i, end=' ')