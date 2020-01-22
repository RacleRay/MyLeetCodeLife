"""假设数组中元素两两不同"""

class SolutionOne:
    """非递归分治方法"""
    def __init__(self, array):
        self._max = None
        self._min = None
        self._array = array

    def get_max(self):
        return self._max

    def get_min(self):
        return self._min

    def find_max_min(self):
        if self._array is None:
            return None

        # 将元素两两分组，一组中小的在做，大的在右。分组后在小的中找最小，大的中找最大
        length = len(self._array)
        i = 0
        while i < (length - 1):
            if self._array[i] > self._array[i + 1]:
                self._array[i], self._array[i + 1] = self._array[i + 1], self._array[i]
            i += 2

        self._min = self._array[0]
        i_min = 2
        while i_min < length:
            if self._array[i_min] < self._min:
                self._min = self._array[i_min]
            i_min += 2

        self._max = self._array[1]
        i_max = 3
        while i_max < length:
            if self._array[i_max] > self._max:
                self._max = self._array[i_max]
            i_max += 2

        # 计数个元素，最后一个组只有一个元素，且在第一步中未参与比较
        if length % 2 == 1:
            if self._max < self._array[-1]:
                self._max = self._array[-1]
            elif self._min > self._array[-1]:
                self._min = self._array[-1]


class SolutionTwo(SolutionOne):
    """递归法"""
    def __init__(self, array):
        super(SolutionTwo, self).__init__(array)

    def __find_max_min(self, left_i, right_i):
        if array is None:
            return None

        # 只有一个元素
        if left_i == right_i:
            return [self._array[left_i]]

        # 两个元素
        if left_i + 1 == right_i:
            self._max = max(self._array[left_i], self._array[right_i])
            self._min = min(self._array[left_i], self._array[right_i])
            return [self._min, self._max]  # 前小后大

        mid = (left_i + right_i) // 2
        left_res = self.__find_max_min(left_i, mid)
        right_res = self.__find_max_min(mid, right_i)

        self._max = left_res[1] if left_res[1] > right_res[1] else right_res[1]
        self._min = left_res[0] if left_res[0] < right_res[0] else right_res[0]

        return [self._min, self._max]

    def find_max_min(self):
        return self.__find_max_min(0, len(self._array) - 1)


if __name__ == "__main__":
    array = [7, 3, 19, 40, 4, 7, 1]
    obj = SolutionOne(array)
    obj.find_max_min()

    print(obj.get_max())
    print(obj.get_min())

    obj2 = SolutionTwo(array)
    obj2.find_max_min()

    print(obj2.get_max())
    print(obj2.get_min())


