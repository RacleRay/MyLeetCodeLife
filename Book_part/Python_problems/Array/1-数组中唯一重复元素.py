"""只有唯一一个重复，不使用额外的内存空间"""

def find_duplicate(array):
    """异或：自己对自己异或取值为0，0与任何值取异或结果为这个任何值本身。"""
    if len(array) == 0:
        return None

    res = 0
    for elem in array:
        res ^= elem

    # 值域为1到1000
    for elem in range(1, 1001):
        res ^= elem

    return res


def find_duplicate_cycle_way(array):
    """当做链表，每个位置的值作为next指针指向的地址"""
    if len(array) == 0:
        return None

    slow_p = 0
    fast_p = 0
    while True:
        fast_p = array[array[fast_p]]
        slow_p = array[slow_p]
        if fast_p == slow_p:
            break

    # 重置fast_p，使得再次相遇时，两次fast_p走的距离刚好比slow_p多，一个循环的距离
    # 第二次fast_p步长变为1
    fast_p = 0
    while True:
        fast_p = array[fast_p]
        slow_p = array[slow_p]
        if fast_p == slow_p:
            return fast_p


if __name__ == "__main__":
    array = [i for i in range(1, 1001)] + [3]

    print(find_duplicate(array))
    print(find_duplicate_cycle_way(array))