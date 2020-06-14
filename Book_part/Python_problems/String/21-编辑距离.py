"""假设可以调节执行替换操作的weight"""


def editDistance(str1, str2, weight):
    if str1 is None or str2 is None:
        return max(len(str1), len(str2))
    len1 = len(str1)
    len2 = len(str2)
    dRecord = [[0 for _ in range(len2 + 1)] for _ in range(len1 + 1)]  # str1 -- col index

    i = 1
    while i < len1 + 1:
        dRecord[i][0] = i
        i += 1

    i = 1
    while i < len2 + 1:
        dRecord[0][i] = i
        i += 1

    i = 1  # str1
    while i < len1 + 1:
        j = 1  # str2
        while j < len2 + 1:
            dRecord[i][j] = min(dRecord[i - 1][j] + 1,
                                dRecord[i][j - 1] + 1,
                                dRecord[i - 1][j - 1] + weight * int(str1[i - 1] != str2[j - 1]))
            j += 1
        i += 1

    return dRecord


if __name__ == "__main__":
    s1 = "bclin"
    s2 = "fciling"
    dRecord = editDistance(s1, s2, 1)
    print(dRecord)
    print("Distance: ", dRecord[-1][-1])

    dRecord = editDistance(s1, s2, 2)
    print(dRecord)
    print("Distance(weight 2): ", dRecord[-1][-1])