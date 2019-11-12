# python3

from helper import LNode

# 节点由0， 1， 2， 3，...，n变为0，n，1，n-1，2，n-2，3，...
def find_mid_node(first):
    """T:O(N), Space: O(1)"""
    if first == None or first.next == None:
        return first

    fast_p = first  # 2 p/step
    slow_p = first  # 1 p/step
    slow_pre = first  # 用于截断链表

    while fast_p is not None and fast_p.next is not None:
        slow_pre = slow_p
        slow_p = slow_p.next
        fast_p = fast_p.next.next

    slow_pre.next = None
    # 后半部分起点node
    return slow_p


def reverse(first):
    """后半部分不带头结点, T:O(N), Space: O(1)"""
    if first == None or first.next == None:
        return first

    prev = first
    cur = first.next
    next = cur.next

    prev.next = None
    while next != None:
        tmp = cur.next

        # reverse
        cur.next = prev
        prev = cur

        # next
        cur = tmp
        next = cur.next

    # add last node
    cur.next = prev
    prev = cur
    return prev


def reorder(head):
    """T:O(N), Space: O(1)"""
    if head == None or head.next == None:
        return head

    # pointer
    first_part = head.next
    second_part = find_mid_node(head.next)
    reverse_sec_part = reverse(second_part)

    # 合并
    tmp = None
    while first_part.next is not None:
        # 插入第二部分值
        tmp = first_part.next
        first_part.next = reverse_sec_part
        first_part = tmp  # 下一个添加位置

        # 插入第一部分值
        tmp = reverse_sec_part.next
        reverse_sec_part.next = first_part
        reverse_sec_part = tmp  # 下一个添加位置

    # 总共偶数个时，reverse_sec_part为最后一个值
    # 总共奇数个时，reverse_sec_part为None
    first_part.next = reverse_sec_part


if __name__ == '__main__':
    head = LNode(None)
    head.next = None
    cur = head

    i = 1
    tmp = None
    while i < 8:
        tmp = LNode(i)
        tmp.data = i
        cur.next = tmp
        cur = tmp
        i += 1

    print('Before: ')
    cur = head.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next
    print()

    reorder(head)

    print('Reverse: ')
    cur = head.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next
    print()