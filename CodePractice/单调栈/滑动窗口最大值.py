"LintCode 362. 滑动窗口的最大值"

from heapq import heappop, heappush
import collections

class Solution:
    def maxSlidingWindow(self, nums, k):
        if not nums:
            return []

        max_values = []
        maxheap = Heap()
        for i in range(len(nums)):
            maxheap.push(i, -nums[i])
            if (i < k - 1):
                continue
            max_values.append(-max_values.top()[1])
            maxheap.delete(i - k + 1)

        return max_values


    def maxSlidingWindow_2(self, nums, k):
        if not nums: return []

        deque = collections.deque()
        results = []

        for i in range(len(nums)):
            while deque and nums[deque[-1]] < nums[i]:
                deque.pop()
            deque.append(i)

            if i >= k - 1:
                results.append(nums[deque[0]])

            if i - k + 1 == deque[0]:
                deque.popleft()

        return results

class Heap:
    def __init__(self) -> None:
        self.minheap = []
        self.delete_set = set()  # for lazy deletion

    def push(self, index, val):
        heappush(self.minheap, (index, val))

    def _lazy_deletion(self):
        while self.minheap and self.minheap[0][0] in self.delete_set:
            heappop(self.minheap)

    def top(self):
        self._lazy_deletion()
        return self.minheap[0]

    def pop(self):
        self._lazy_deletion()
        heappop(self.minheap)

    def delete(self, index):
        self.delete_set.add(index)

    def is_empty(self):
        return not bool(self.minheap)
