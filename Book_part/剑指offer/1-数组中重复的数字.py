class Solution:
    def findRepeatNumber(self, nums: List[int]) -> int:
        record = set()
        for i in nums:
            if i in record:
                return i
            record.add(i)
        return -1

    def findRepeatNumber2(self, nums: List[int]) -> int:
        idx = 0
        while idx < len(nums):
            if nums[idx] == idx:
                idx += 1
                continue
            if nums[idx] == nums[nums[idx]]:
                return nums[idx]
            nums[nums[idx]], nums[idx] = nums[idx], nums[nums[idx]]
        return -1