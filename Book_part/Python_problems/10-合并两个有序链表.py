# python3

from helper import LNode, print_list, construct_list_design


def merge(head1, head2):
    if head1 == None or head1.next == None:
        return head2

    if head2 == None or head2.next == None:
        return head1

    pointer_1 = head1.next
    pointer_2 = head2.next

    new_head = LNode(-1)
    new_pointer = new_head

    while pointer_1 != None and pointer_2 != None:

        if pointer_1.data < pointer_2.data:
            new_pointer.next = pointer_1
            new_pointer = pointer_1
            pointer_1 = pointer_1.next
        else:
            new_pointer.next = pointer_2
            new_pointer = pointer_2
            pointer_2 = pointer_2.next

    # left part
    if pointer_1 != None:
        new_pointer.next = pointer_1

    if pointer_2 != None:
        new_pointer.next = pointer_2

    return new_head


if __name__ == "__main__":
    head1 = construct_list_design(1, 4)
    head2 = construct_list_design(3, 8)

    print_list(head1)
    print()
    print_list(head2)
    print()

    print('After: ')
    print_list(merge(head1, head2))