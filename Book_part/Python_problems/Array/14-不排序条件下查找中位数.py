#python3


class Solution:
    def __init__(self):
        self.pos = 0

    def partition(self, arr, left, right):
        """以arr[left]为pivot，划分数组
        return：pos -- arr[left]的实际位置
        """
        pivot = arr[left]
        while left < right:
            while left < right and arr[right] > pivot:
                right -= 1
            arr[left] = arr[right]
            while left < right and arr[left] < pivot:
                left += 1
            arr[right] = arr[left]
        arr[left] = pivot
        pos = left
        return pos

    def getmiddle(self, arr):
        length = len(arr)
        left = 0
        right = length - 1
        mid = (left + right) // 2

        while True:
            self.pos = self.partition(arr, left, right)
            if self.pos == mid:
                break
            elif self.pos > mid:
                right = self.pos - 1
            else:
                left = self.pos + 1

        # 奇数个与偶数个
        return arr[mid] if (length & 1) == 1 else \
                                (arr[mid] + arr[mid + 1]) / 2


if __name__ == "__main__":
    array = [7, 5, 3, 1, 11]
    sol = Solution()
    res = sol.getmiddle(array)
    print("Result is: {}".format(res))