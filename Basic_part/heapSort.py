
class MaxHeap():
    def __init__(self):
        self.heaplist = [0]
        self.count = 0

    def size(self):
        return self.count

    def isEmpty(self):
        return self.count == 0

    def insert(self, item):
        self.heaplist.append(item)
        self._shiftUp(self.count + 1)
        self.count += 1

    def _shiftUp(self, index):
        """
        尾端添加元素，上浮到MaxHeap中的正确位置

        i // 2: 父节点
        i * 2: 左孩子
        i * 2 + 1：右孩子
        注：元素在list中，从index=1的位置开始计算
        """
        while index > 1 and self.heaplist[index // 2] < self.heaplist[index]:
            self.heaplist[index // 2], self.heaplist[index] = \
                self.heaplist[index], self.heaplist[index // 2]
            index //= 2

    def getMax(self):
        assert self.count > 0
        return self.heaplist[1]

    def extractMax(self):
        """从最大堆中取出堆顶元素, 即堆中所存储的最大数据"""
        assert self.count > 0

        result = self.heaplist[1]
        # 为保持完全二叉树
        self.heaplist[1], self.heaplist[self.count] = \
            self.heaplist[self.count], self.heaplist[1]
        self.count -= 1
        self._shiftDown(1)

        return result

    def _shiftDown(self, index):
        """首端元素（index==1）下沉到MaxHeap中正确位置"""
        while index * 2 <= self.count:
            # init
            left_child = index * 2
            right_child = left_child + 1
            max_child = left_child

            if right_child <= self.count and \
              self.heaplist[right_child] > self.heaplist[left_child]:
                max_child = right_child

            if self.heaplist[index] >= self.heaplist[max_child]:
                break

            self.heaplist[index], self.heaplist[max_child] = \
                self.heaplist[max_child], self.heaplist[index]
            index = max_child

    def _shiftDown_2(self,index):
        """优化"""
        value = self.heaplist[index]
        while index * 2 <= self.count:
            # init
            left_child = index * 2
            right_child = left_child + 1
            max_child = left_child

            if right_child <= self.count and \
              self.heaplist[right_child] > self.heaplist[left_child]:
                max_child = right_child

            if value >= self.heaplist[max_child]:
                break

            self.heaplist[index] = self.heaplist[max_child]
            index = max_child

        # 找到正确位置后再赋值
        self.heaplist[index] = value

    def heapify(self, alist):
        """通过一个给定数组创建一个最大堆, heapify"""
        self.count = len(alist)
        index = len(alist) // 2  # 从最小父节点开始
        self.heaplist = [0] + alist[:]

        while index > 0:
            self._shiftDown(index)
            index -= 1

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
def heapSort_1(alist):
    """heapSort1, 将所有的元素依次添加到堆中, 在将所有元素从堆中依次取出来"""
    maxheap = MaxHeap()
    for i in range(len(alist)):
        maxheap.insert(alist[i])

    for i in range(len(alist) - 1, -1, -1):  # MaxHeap中，list为[0] + [alist]
        alist[i] = maxheap.extractMax()

    return alist

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
def heapSort_2(alist):
    """heapify过程创建堆"""
    maxheap = MaxHeap()
    maxheap.heapify(alist)   # O(n)

    for i in range(len(alist)-1, -1, -1): # O(nlogn)
        alist[i] = maxheap.extractMax()

    return alist

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
def heapSort_3(alist):
    """inplace的堆排序, 注意此时index从0开始, i * 2 + 1:左孩子"""

    def shiftDown(alist, n, index):
        """
        n: shiftDown操作边界
        i: shiftDown element index
        """
        value = alist[index]
        while index * 2 + 1 < n:
            # init
            left_child = index * 2 + 1
            right_child = left_child + 1
            max_child = left_child

            if right_child < n and alist[right_child] > alist[left_child]:
                max_child = right_child

            if value >= alist[max_child]:
                break

            alist[index] = alist[max_child]
            index = max_child

        alist[index] = value

    n = len(alist)
    index = (n - 1 - 1) // 2
    # alist >>> max heap
    while index >= 0:
        shiftDown(alist, n, index)
        index -= 1

    # max heap >>> extract max >>> sorted
    unsorted_bound = n - 1
    while unsorted_bound > 0:
        # max >>> right bound;
        alist[0], alist[unsorted_bound] = alist[unsorted_bound], alist[0]
        # unsorted part list: shift down >>> max heap
        shiftDown(alist, unsorted_bound, 0)
        unsorted_bound -= 1

    return alist