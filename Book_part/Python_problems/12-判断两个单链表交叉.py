# python3

from helper import LNode, print_list, construct_list_with_a_pointer, construct_list_design


def is_intersect(head1, head2):
    if head1 == None or head1.next == None:
        return None

    if head2 == None or head2.next == None:
        return None

    pointer_1 = head1.next
    pointer_2 = head2.next

    def find_end(first):
        end = None
        length = 1

        while first.next != None:
            first = first.next
            length += 1

        end = first
        length += 1

        return end, length

    end1, length1 = find_end(pointer_1)
    end2, length2 = find_end(pointer_2)

    if end1 != end2:
        return None
    else:
        # 找到相交点
        fast_p, slow_p = (pointer_1, pointer_2) if length1 > length2 \
                            else (pointer_2, pointer_1)
        longer, shorter = (length1, length2) if fast_p == head1 \
                                else (length2, length1)

        # 先行
        while longer - shorter > 0:
            fast_p = fast_p.next
            longer -= 1

        while fast_p != slow_p:
            fast_p = fast_p.next
            slow_p = slow_p.next

        return fast_p


if __name__ == '__main__':
    head1, pointer = construct_list_with_a_pointer(1, 8)
    head2 = construct_list_design(10, 14)

    tmp = head2.next
    while tmp.next is not None:
        tmp = tmp.next

    tmp.next = pointer

    interNode = is_intersect(head1, head2)

    print('pointer：', pointer.data)
    if interNode:
        print('交点：', interNode.data)