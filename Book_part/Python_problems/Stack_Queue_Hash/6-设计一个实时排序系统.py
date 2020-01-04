# python3
from collections import deque

class Item:
    def __init__(self, id, name):
        self.__id = id
        self.__name = name
        self.__order = 0

    def get_name(self):
        return self.__name

    def get_id(self):
        return self.__id

    def get_order(self):
        return self.__order

    def set_name(self, name):
        self.__name = name

    def set_order(self, order):
        self.__order = order

    def __eq__(self, other):
        return self.__id == other.get_id()

    def __repr__(self):
        return "id: " + str(self.__id) + ". name: " + str(self.__name) + ". order: " + str(self.__order)


class OrderQueue:
    def __init__(self):
        self.__queue = deque()

    def enqueue(self, item):
        item.set_order(len(self.__queue) + 1)
        self.__queue.append(item)

    def dequeue(self):
        "队头出队"
        self.__queue.popleft()
        self.__update_queue()

    def dequeue_random(self, item):
        "随机出队"
        self.__queue.remove(item)
        self.__update_queue()

    def __update_queue(self):
        "出队后，更新每个item的向右次序"
        order = 1
        for item in self.__queue:
            item.set_order(order)
            order += 1

    def print_list(self):
        for item in self.__queue:
            print(item)


if __name__ == "__main__":
    item1 = Item(1, "item1")
    item2 = Item(2, "item2")
    item3 = Item(3, "item3")
    item4 = Item(4, "item4")
    item5 = Item(5, "item5")

    queue = OrderQueue()
    queue.enqueue(item1)
    queue.enqueue(item2)
    queue.enqueue(item3)
    queue.enqueue(item4)
    queue.enqueue(item5)

    queue.print_list()
    print()

    queue.dequeue()
    queue.print_list()
    print()

    queue.dequeue_random(item3)
    queue.print_list()



