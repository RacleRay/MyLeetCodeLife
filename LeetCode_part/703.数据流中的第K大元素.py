"""
设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。

示例:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
说明:
你可以假设 nums 的长度≥ k-1 且k ≥ 1。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/kth-largest-element-in-a-stream
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
class KthLargest(object):

    def __init__(self, k, nums):
        """
        :type k: int
        :type nums: List[int]
        """
        self._heapsize = k
        if len(nums) >= k:
            self._heap = nums[:k]
            for i in range(self._parent(k - 1), -1, -1):
                self._siftdown(i)
            for j in nums[k:]:
                _ = self.add(j)
        else:
            self._heap = nums

    def _parent(self, i):
        return (i - 1) // 2  # 二叉树父节点求法

    def _leftchild(self, i):
        return i * 2 + 1

    def _rightchild(self, i):
        return i * 2 + 2

    def _siftdown(self, i):
        """自下向上交换

        Arguments:
            i {int} -- 当前节点index
        """
        i_value = self._heap[i]
        while self._leftchild(i) < self._heapsize:
            lchild = self._leftchild(i)
            rchild = self._rightchild(i)
            if rchild < self._heapsize and self._heap[rchild] < self._heap[lchild]:
                smaller = self._heap[rchild]
                i_smaller = rchild
            else:
                smaller = self._heap[lchild]
                i_smaller = lchild

            if smaller < i_value:
                self._heap[i] = smaller
                i = i_smaller
            else:
                break

        self._heap[i] = i_value

    def _siftup(self, i):
        """自上向下交换

        Arguments:
            i {int} -- 当前节点index
        """
        i_value = self._heap[i]
        while i > 0 and i_value < self._heap[self._parent(i)]:
            self._heap[i] = self._heap[self._parent(i)]
            i = self._parent(i)
        self._heap[i] = i_value

    def add(self, val):
        """
        :type val: int
        :rtype: int
        """
        if len(self._heap) < self._heapsize - 1:
            self._heap.append(val)
            return None

        if len(self._heap) == self._heapsize - 1:
            self._heap.append(val)
            for i in range(self._parent(self._heapsize - 1), -1, -1):
                self._siftdown(i)
            return self._heap[0]

        if val <= self._heap[0]:
            return self._heap[0]
        self._heap[0] = val
        self._siftdown(0)
        return self._heap[0]


# 直接用库
import heapq
class KthLargest_2:
    def __init__(self, k: int, nums):
        self.pool = heapq.nlargest(k, nums)
        heapq.heapify(self.pool)
        self.k = k

    def add(self, val: int) -> int:
        if len(self.pool) < self.k:
            heapq.heappush(self.pool,val)
        else:
            heapq.heappushpop(self.pool,val)
        return self.pool[0]


# Your KthLargest object will be instantiated and called as such:
if __name__ == "__main__":
    k = 2
    nums = []
    obj = KthLargest_2(k, nums)
    param_1 = obj.add(3)

    print(param_1)