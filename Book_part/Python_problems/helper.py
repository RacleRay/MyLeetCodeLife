# python3

class LNode():
    def __init__(self, x):
        self.data = x
        self.next = None


def construct_list():
    head = LNode(-1)
    cur = head
    i = 1
    while i < 8:
        cur.next = LNode(i)
        cur = cur.next
        i += 1

    return head


def construct_list_design(x, bound):
    head = LNode(-1)
    cur = head
    i = x
    while i < bound:
        cur.next = LNode(i)
        cur = cur.next
        i += 1

    return head


def construct_list_with_a_pointer(x, bound):
    head = LNode(-1)
    cur = head
    i = x
    while i < bound:
        cur.next = LNode(i)
        cur = cur.next
        i += 1

        if bound - i == 3:
            pointer = cur

    return head, pointer


def construct_loop_list():
    head = LNode(-1)
    cur = head

    i = 1
    while i < 8:
        cur.next = LNode(i)
        cur = cur.next
        i += 1

    cur.next = head.next.next.next

    return head


def print_list(head):
    cur = head.next
    while cur != None:
        print(cur.data, end=' ')
        cur = cur.next