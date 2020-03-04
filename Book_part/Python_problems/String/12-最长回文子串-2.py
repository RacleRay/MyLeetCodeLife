class Solution:
    """中心扩展，从中心向两边扩展对比"""
    def __init__(self):
        self.startIdx = 0
        self.curLen = 0
        self.string = ''

    def expand(self, start1, start2):
        "Two cases: start1 == start2; start1 == start2 - 1"
        length = len(self.string)
        while start1 >= 0 and start2 < length and self.string[start1] == self.string[start2]:
            start1 -= 1
            start2 += 1
        tmpLen = start2 - start1 - 1  # while 退出条件下
        if tmpLen > self.curLen:
            self.curLen = tmpLen
            self.startIdx = start1 + 1  # while 退出条件下

    def getLongestPalindrome(self, string):
        if string is None:
            return None
        self.string = string

        i = 0
        while i < len(self.string) - 1:
            self.expand(i, i)  # odd
            self.expand(i, i + 1)  # even
            i += 1

        return self.string[self.startIdx: self.startIdx + self.curLen]


if __name__ == "__main__":
    string = 'abcdefgfedxyz'
    sol = Solution()
    result = sol.getLongestPalindrome(string)
    print(result)



