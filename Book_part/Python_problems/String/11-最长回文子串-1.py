"""动态规划"""

class Solution:
    def __init__(self):
        self.startIdx = None
        self.curLen = None

    def getLongestPalindrome1(self, string):
        if string is None:
            return

        length = len(string)
        self.startIdx = 0
        self.curLen = 1
        record = [[-1] * length for _ in range(length)]

        # 长度为1的回文字符串
        i = 0
        while i < length:
            record[i][i] = 1
            i += 1
        # 长度为2
        i = 0
        while i < length - 1:
            if string[i] == string[i + 1]:
                record[i][i + 1] = 1
                self.startIdx = i
                self.curLen = 2
            i += 1
        # 长度从3开始
        tmpLen = 3
        while tmpLen <= length:
            i = 0
            while i < length - tmpLen + 1:
                j = i + tmpLen - 1
                # record[i + 1][j - 1]: 短length的都比较过
                if string[i] == string[j] and record[i + 1][j - 1] == 1:
                    record[i][j] = 1
                    self.startIdx = i
                    self.curLen = tmpLen
                i += 1
            tmpLen += 1

    # Method2
    @staticmethod
    def reverse(string):
        chars = list(string)
        length = len(chars)
        i = 0; j = length - 1
        while i < j:
            chars[i] = chr(ord(chars[i]) ^ ord(chars[j]))
            chars[j] = chr(ord(chars[i]) ^ ord(chars[j]))
            chars[i] = chr(ord(chars[i]) ^ ord(chars[j]))
            i += 1
            j -= 1
        return ''.join(chars)

    @staticmethod
    def getLongestCommonSubsequence(str1, str2):
        len1 = len(str1)
        len2 = len(str2)
        result = ''
        common_len = 0
        common_end = 0

        # M[i][j]: 以str1[i], str2[j]结尾的最长公共子串的的长度
        M = [[None] * (len1 + 1) for _ in range(len2 + 1)]
        for i in range(len1 + 1):
            M[i][0] = 0
        for j in range(len2 + 1):
            M[0][j] = 0
        for i in range(1, len1 + 1):
            for j in range(1, len2 + 1):
                if str1[i - 1] == str2[j - 1]:  # M中多出第0行，第0列，对应str中idx要减一
                    M[i][j] = M[i - 1][j - 1] + 1
                    if M[i][j] > common_len:
                        common_len = M[i][j]
                        common_end = i
                else:
                    M[i][j] = 0

        # result = str1[common_end - common_len: common_end]
        return (common_end, common_len)

    def getLongestPalindrome2(self, string):
        reverseString = self.reverse(string)
        result = self.getLongestCommonSubsequence(string, reverseString)
        return result


if __name__ == "__main__":
    string = 'abcdefgfedxyz'
    sol = Solution()
    sol.getLongestPalindrome1(string)
    if sol.curLen > 1:
        print(sol.startIdx, sol.curLen)
        print(string[sol.startIdx: sol.startIdx + sol.curLen])

    result = sol.getLongestPalindrome2(string)
    if result[1] > 1:
        print(string[result[0] - result[1]: result[0]])
