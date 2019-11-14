# python3

class ArrayStack:
    """没有额外指针，但是空间申请和释放不够灵活。"""
    def __init__(self):
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def size(self):
        return len(self.items)

    def top(self):
        if not self.is_empty():
            return self.items[len(self.items) - 1]
        else:
            return None

    def pop(self):
        if len(self.items) > 0:
            return self.items.pop()
        else:
            print('Stack is empty.')
            return None

    def push(self, item):
        self.items.append(item)


class LNode:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkStack:
    """灵活，但是需要额外空间存指针。"""
    def __init__(self):
        self.data = None
        self.next = None

    def is_empty(self):
        if self.next is None:
            return True
        else:
            return False

    def size(self):

        size = 0
        pointer = self.next
        while pointer is not None:
            pointer = pointer.next
            size += 1

        return size

    def top(self):
        if self.next is not None:
            return self.next.data
        else:
            print('Stack is empty.')
            return None

    def push(self, elem):
        # 前端插入
        new = LNode(elem)
        new.next = self.next
        self.next = new

    def pop(self):

        tmp = self.next
        if tmp is not None:
            self.next = tmp.next
            return tmp.data

        return None



if __name__ == '__main__':
    stack = ArrayStack()

    for i in range(5):
        stack.push(i + 1)

    first_out = stack.pop()
    print('Pop: ', first_out)

    print('Top: ', stack.top())

    ############################
    stack = LinkStack()

    for i in range(8):
        stack.push(i + 1)

    first_out = stack.pop()
    print('Pop: ', first_out)

    print('Top: ', stack.top())