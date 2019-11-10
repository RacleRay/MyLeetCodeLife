# python3
from helper import LNode


def reverse_1(head):
    """T:O(N), Space: O(1)"""
    if head == None or head.next == None:
        return None

    prev, cur, next = None, None, None

    # first
    cur = head.next
    next = cur.next  # 在改变引用指针之前
    cur.next = None

    prev = cur  # 新链表中的prev指针
    cur = next

    while cur.next != None:
        next = cur.next
        cur.next = prev
        prev = cur
        cur = next

    cur.next = prev
    head.next = cur


def reverse_2(head):
    """T:O(N), 栈操作消耗，性能下降"""
    def recusive_reverse(first_node):
        if first_node is None or first_node.next is None:
            return first_node

        new_first_node = recusive_reverse(first_node.next)
        # cur为first_node.next节点，加到已经逆序的尾部
        first_node.next.next = first_node
        first_node.next = None

        return new_first_node

    if head is None:
        return

    first_node = head.next
    new_first_node = recusive_reverse(first_node)
    head.next = new_first_node

    return head


def reverse_3(head):
    """遍历插入法，不需要前驱。T:O(N)"""
    if head is None or head.next is None:
        return

    cur, next = None, None

    cur = head.next.next
    head.next.next = None  # 处理掉原来的地址存储区域数据

    while cur is not None:
        next = cur.next
        cur.next = head.next  # 插入
        head.next = cur  # new first node
        cur = next  # next loop


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
        print(cur.data)
        cur = cur.next

    # reverse_1(head)
    # reverse_2(head)
    reverse_3(head)

    print('Reverse: ')
    cur = head.next
    while cur != None:
        print(cur.data)
        cur = cur.next