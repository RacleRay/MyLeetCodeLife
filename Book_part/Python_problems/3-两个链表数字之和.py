# python3

from helper import LNode


def add(head_1, head_2):
    """从左向右加, T:O(N)"""
    if head_1 is None or head_1.next is None:
        return head_2

    if head_2 is None or head_2.next is None:
        return head_1

    carry = 0
    single_sum = 0

    pointer_1 = head_1.next
    pointer_2 = head_2.next

    head_res = LNode(-1)
    pointer_res = head_res

    while pointer_1 != None and pointer_2 != None:
        single_sum = pointer_1.data + pointer_2.data + carry
        carry = single_sum // 10  # 进位

        # 修改当前位置
        pointer_res.next = LNode(single_sum % 10)
        pointer_res = pointer_res.next

        pointer_1 = pointer_1.next
        pointer_2 = pointer_2.next

    # 不等长多余部分
    lefted_part = pointer_1 if pointer_2 is None else pointer_2
    while lefted_part is not None:
        single_sum = lefted_part.data + carry
        carry = single_sum // 10

        pointer_res.next = LNode(single_sum % 10)
        pointer_res = pointer_res.next

        lefted_part = lefted_part.next

    # 最后还有进位
    if carry == 1:
        pointer_res.next = LNode(carry)

    return head_res


if __name__ == "__main__":
    head_1 = LNode(-1)
    head_2 = LNode(-1)

    tmp = None
    cur = head_1
    i = 1
    while i < 7:
        tmp = LNode(i + 2)
        cur.next = tmp
        cur = tmp
        i += 1

    cur = head_2
    i = 9
    while i > 4:
        tmp = LNode(i)
        cur.next = tmp
        cur = tmp
        i -= 1

    print('Before: ')
    print('head_1: ')
    cur = head_1.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next
    print()

    print('head_2: ')
    cur = head_2.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next
    print()

    head_res = add(head_1, head_2)

    print('After: ')
    cur = head_res.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next