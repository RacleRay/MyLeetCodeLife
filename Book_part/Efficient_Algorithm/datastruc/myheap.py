"""
heapq 模块不能修改堆中的元素值，而这个操作在 Dijkstra 算法中可以优化时间复杂度。
因此，完成更完整的实现方式。
"""

class Heap:
    def __init__(self, items):
        self.n = 0
        self.heap = [None]  # heap[0]没有实际意义，只为方便index计算
        self.rank = {}      # 查找堆中元素的下标index
        for x in items:
            self.push(x)

    def __len__(self):
        return len(self.heap) - 1

    def push(self, x):
        assert x not in self.rank
        end = len(self.heap)
        self.heap.append(x)  # 尾部添加并上浮，保持堆排序
        self.rank[x] = end
        self.up(end)

    def pop(self):
        root = self.heap[1]
        del self.rank[root]
        x = self.heap.pop()  # 尾部pop元素，重新从堆顶下沉，保持堆排序
        if len(self.heap) != 0:  # 堆非空
            self.heap[1] = x
            self.rank[x] = 1
            self.down(1)
        return root

    def up(self, i):
        x = self.heap[i]
        while i > 1 and x < self.heap[i//2]:
            self.heap[i] = self.heap[i//2]
            self.rank[self.heap[i//2]] = i
            i //= 2
        self.heap[i] = x
        self.rank[x] = i

    def down(self, i):
        x = self.heap[i]
        curLen = len(self.heap)
        while True:
            left = 2 * i
            right = left + 1
            if right < curLen and self.heap[right] < x and \
              self.heap[right] < self.heap[left]:
                self.heap[i] = self.heap[right]
                self.rank[self.heap[right]] = i
                i = right
            elif left < curLen and self.heap[left] < x:
                self.heap[i] = self.heap[left]
                self.rank[self.heap[left]] = i
                i = left
            else:
                self.heap[i] = x
                self.rank[x] = i
                return

    def update(self, old, new):
        "更改元素old为new"
        i = self.rank[old]
        del self.rank[old]
        self.heap[i] = new
        self.rank[new] = i
        if old < new:
            self.down(i)
        else:
            self.up(i)