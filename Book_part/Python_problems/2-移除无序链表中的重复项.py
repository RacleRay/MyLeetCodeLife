# python3

from helper import LNode


def remove_dup_1(head):
    """T:O(N2)暴力求解"""
    if head == None or head.next == None:
        return

    outLooper = head.next  # key
    innerLooper = None
    innerPre = None

    while outLooper != None:
        innerLooper = outLooper.next  # query
        innerPre = outLooper  # tmp record

        while innerLooper != None:
            # print(outLooper.data, innerLooper.data)
            if outLooper.data == innerLooper.data:
                innerPre.next = innerLooper.next  # delete
                innerLooper = innerLooper.next  # next query
            else:
                innerPre = innerLooper
                innerLooper = innerLooper.next  # next query

        outLooper = outLooper.next  # next key


def remove_dup_2(head):
    """T:O(N2)递归求解"""
    def remove_recursive(first):
        # 尾结点时边界
        if first.next is None:
            return first

        next_ = None
        cur = first

        # 子链表递归删除
        first.next = remove_recursive(first.next)

        # 每次递归的处理逻辑
        next_ = first.next
        while next_ is not None:
            if first.data == next_.data:
                cur.next = next_.next  # delete
                next_ = cur.next  # next query
            else:
                next_ = next_.next  # next query
                cur = cur.next  # current index

        return first

    # 有头节点
    if head == None:
        return

    head.next = remove_recursive(head.next)


if __name__ == "__main__":
    i = 1
    head = LNode(i)

    tmp = None
    cur = head
    while i < 7:

        if i % 2 == 0:
            tmp = LNode(i + 1)
        elif i % 3 == 0:
            tmp = LNode(i - 2)
        else:
            tmp = LNode(i)

        tmp.next = None
        cur.next = tmp
        cur = tmp
        i += 1

    print('Before: ')
    cur = head.next
    while cur != None:
        print(cur.data)
        cur = cur.next

    # remove_dup_1(head)
    remove_dup_2(head)

    print('Remove: ')
    cur = head.next
    while cur != None:
        print(cur.data)
        cur = cur.next

