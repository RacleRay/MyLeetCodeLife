"""
描述
设计并实现一个 TwoSum 类。他需要支持以下操作:add 和 find。
add -把这个数添加到内部的数据结构。
find -是否存在任意一对数字之和等于这个值

样例
样例 1:

add(1);add(3);add(5);
find(4)//返回true
find(7)//返回false

https://www.lintcode.com/problem/607/description
"""

# class TwoSum:
#     """
#     方案一：保持排序，查找使用双指针, Time Limit Exceeded TLE
#     @param number: An integer
#     @return: nothing
#     """
#     nums = []
#     def add(self, number):
#         self.nums.append(number)
#         # insert and sort
#         index = len(self.nums) - 1
#         while index > 0 and self.nums[index] > self.nums[index - 1]:
#             self.nums[index], self.nums[index - 1] = self.nums[index - 1], self.nums[index]
#             index -= 1

#     """
#     @param value: An integer
#     @return: Find if there exists any pair of numbers which sum is equal to the value.
#     """
#     def find(self, value):
#         left, right = 0, len(self.nums) - 1
#         while left < right:
#             two_sum = self.nums[left] + self.nums[right]
#             if two_sum < value:
#                 left += 1
#             elif two_sum > value:
#                 right -= 1
#             else:
#                 return True
#         return False


class TwoSum:
    """
    方案二：hashset或者map
    @param number: An integer
    @return: nothing
    """
    # nums = {}
    # def add(self, number):
    #     self.nums[number] = self.nums.setdefault(number, 0) + 1

    # """
    # @param value: An integer
    # @return: Find if there exists any pair of numbers which sum is equal to the value.
    # """
    # def find(self, value):
    #     for num in self.nums.keys():
    #         num2 = value - num
    #         cnt = 2 if num == num2 else 1
    #         if self.nums.get(num2, 0) >= cnt:
    #             return True
    #     return False


    nums = []
    def add(self, number):
        self.nums.append(number)

    """
    @param value: An integer
    @return: Find if there exists any pair of numbers which sum is equal to the value.
    """
    def find(self, value):
        nset = set()
        for num in self.nums:
            num2 = value - num
            if num2 in nset:
                return True
            nset.add(num)
        return False
