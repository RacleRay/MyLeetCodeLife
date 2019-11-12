# python3

from helper import LNode, print_list, construct_list_with_a_pointer


def remove(pointer):
    """不能使用前驱节点"""
    # 没有后继节点时，不能删除。因为使用方法是复制后继节点到当前节点。
    if pointer == None or pointer.next == None:
        return None

    # copy
    pointer.data = pointer.next.data

    # remove
    pointer.next = pointer.next.next

    return True


if __name__ == '__main__':
    head, pointer = construct_list_with_a_pointer(1, 8)

    print_list(head)
    print()

    if remove(pointer):
        print('After: ')
        print_list(head)