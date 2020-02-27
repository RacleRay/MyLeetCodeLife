"""123 >>> true
   +12 >>> true
   ++2 >>> false
   abc >>> false
"""


class Solution:
    def __init__(self):
        self.flag = None  # 是否为数字的标识
        self.res = None

    def is_number(self, char):
        return char >= '0' and char <= '9'

    def __strToInt(self, string, length):
        if length > 1:
            if not self.is_number(string[length - 1]):
                self.flag = False
                print('Not a number')
                return -1
            if string[0] == '-':
                return self.__strToInt(string, length - 1) * 10 - \
                    (ord(string[length - 1]) - ord('0'))
            else:
                return self.__strToInt(string, length - 1) * 10 + \
                    ord(string[length - 1]) - ord('0')
        else:
            if string[0] == '-':
                return 0
            else:
                if not self.is_number(string[0]):
                    self.flag = False
                    print('Not a number')
                    return -1
                return ord(string[0]) - ord('0')

    def strToInt(self, string):
        self.flag = True
        if string is None or (string[0] == '-' and len(string) == 1):
            self.flag = False
            print('Not a number')
            return None
        elif string[0] == '+':
            self.res = self.__strToInt(string[1: ], len(string) - 1)
        else:
            self.res = self.__strToInt(string, len(string))


if __name__ == "__main__":
    solution = Solution()
    string = "123"
    solution.strToInt(string)
    if solution.flag is True:
        print(solution.res)

    string = "+12"
    solution.strToInt(string)
    if solution.flag is True:
        print(solution.res)

    string = "++2"
    solution.strToInt(string)
    if solution.flag is True:
        print(solution.res)

    string = "abc"
    solution.strToInt(string)
    if solution.flag is True:
        print(solution.res)