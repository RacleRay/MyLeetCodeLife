# python3

class ArrayQueue:
    """"""
    def __init__(self):
        self.arr = []
        self.front = 0  # 队头
        self.rear = 0   # 队尾：第一个空位置的index

    def isempty(self):
        return self.front == self.rear

    def size(self):
        return self.rear - self.front

    def getFront(self):
        if self.isempty():
            return None
        return self.arr[self.front]

    def getBack(self):
        if self.isempty():
            return None
        return self.arr[self.rear - 1]

    def deQueue(self):
        if self.rear > self.front:
            self.front += 1
        else:
            print("Queue is empty.")

    def enQueue(self, item):
        self.arr.append(item)
        self.rear += 1


class LNode:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkQueue:
    """"""
    def __init__(self):
        self.head = None
        self.end = None

    def isempty(self):
        if self.head == None:
            return True
        else:
            return False

    def size(self):
        size = 0
        pointer = self.head
        while pointer is not None:
            pointer = pointer.next
            size += 1
        return size

    def getFront(self):
        if self.head is None:
            print("Queue is empty.")
        else:
            return self.head.data

    def getBack(self):
        if self.end is None:
            print("Queue is empty.")
        else:
            return self.end.data

    def deQueue(self):
        if self.isempty():
            print("Queue is empty.")
        else:
            self.head = self.head.next
            if self.head is None:  # empty
                self.end = None

    def enQueue(self, item):
        p = LNode(item)
        if self.isempty():
            self.head = self.end = p
        else:
            self.end.next = p
            self.end = p


if __name__ == "__main__":
    queue = ArrayQueue()
    queue.enQueue(1)
    queue.enQueue(2)

    print(queue.getFront())
    print(queue.getBack())
    print(queue.size())
    queue.deQueue()
    print(queue.getFront())

    print("=" * 30)

    queue = LinkQueue()
    queue.enQueue(1)
    queue.enQueue(2)

    print(queue.getFront())
    print(queue.getBack())
    print(queue.size())
    queue.deQueue()
    print(queue.getFront())




