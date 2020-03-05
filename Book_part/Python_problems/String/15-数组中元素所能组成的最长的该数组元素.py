class Solution:
    def isIn(self, string, stringList):
        for item in stringList:
            if item == string:
                return True
        return False

    def isContain(self, string, stringList, originLen):
        curLen = len(string)
        if curLen == 0:
            return True
        # 前缀在stringList中，就递归查询后缀子串
        i = 1
        while i <= curLen:
            if i == originLen:  # 所有前缀都不在其中
                return False
            prefix = string[: i]
            if self.isIn(prefix, stringList):
                return self.isContain(string[i: ], stringList, originLen)
            i += 1
        return False

    def getLongestString(self, stringList):
        stringList = sorted(stringList, key=len, reverse=True)
        for item in stringList:
            if self.isContain(item, stringList, len(item)):
                return item
        return None


if __name__ == "__main__":
    stringList = ["a", "ba", "cd", "sdf", "cdadfas", "bacd"]
    sol = Solution()
    print(sol.getLongestString(stringList))