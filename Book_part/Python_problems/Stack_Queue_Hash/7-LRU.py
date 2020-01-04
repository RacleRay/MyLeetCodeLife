# python3
from collections import deque


class LRU:
    """Least Recently Used"""
    def __init__(self, cache_size):
        self.__cache_size = cache_size
        self.__queue = deque()
        self.__hash_table = {}

    def __is_full(self):
        return len(self.__queue) == self.__cache_size

    def input_queue(self, id, address):
        # 删除最右边（最少使用）
        if self.__is_full():
            if id in self.__hash_table:
                self.__hash_table.pop(id)
            self.__queue.pop()  # rightmost

        self.__queue.appendleft(id)
        self.__hash_table[id] = address

    def access_item(self, id, address):
        # 当id不在队列中
        if id not in self.__hash_table:
            self.input_queue(id, address)
        # 当id在队列中，但是不在队首
        elif id != self.__queue[0]:
            self.__queue.remove(id)
            self.__queue.appendleft(id)

    def __repr__(self):
        res = ""
        for i in range(len(self.__queue)):
            res += 'id: ' + str(self.__queue[i]) + '; address: ' + str(self.__hash_table[self.__queue[i]]) + '\n'
        return res

if __name__ == '__main__':
    lru = LRU(3)

    lru.access_item(1, 'add1')
    lru.access_item(2, 'add2')
    lru.access_item(1, 'add1')
    lru.access_item(6, 'add6')
    lru.access_item(7, 'add7')

    print(lru)



