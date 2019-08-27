class Solution(object):
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        maxArea = 0
        for left in range(len(height)):
            for right in range(left, len(height)):
                maxArea = max(maxArea, min(height[left], height[right])*\
                                           (right - left))
        return maxArea


    def maxArea_2(self, height):
        """
        双指针夹逼
        """
        maxArea = 0
        left = 0
        right = len(height) - 1
        while left < right:
            maxArea = max(maxArea, min(height[left], height[right]) * \
                                       (right - left))
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        return maxArea