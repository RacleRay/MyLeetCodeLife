# python3

from helper import LNode, construct_loop_list, print_list, construct_list


# 1. Hash set

# 2. 快慢指针，并找到环入口位置：从相遇位置开始何从起点位置开始的指针，再次相遇的点为入口点。
def has_loop(head):
    if head == None or head.next == None:
        return None

    slow = head.next
    fast = head.next

    # 2 step
    while fast != None and fast.next != None:
        slow = slow.next
        fast = fast.next.next

        if slow == fast:
            return slow

    return None


def loop_enter(head, meetNode):
    first = head.next
    from_meet = meetNode

    while first != from_meet:
        first = first.next
        from_meet = from_meet.next

    return first


if __name__ == '__main__':
    head = construct_loop_list()
    meetNode = has_loop(head)

    # head = construct_list()
    # meetNode = has_loop(head)

    if meetNode == None:
        print('Nope!')
    else:
        loop_entry = loop_enter(head, meetNode)
        print('Entry is: ', loop_entry.data)
