"""非零整型数组中有三个出现一次的数，找到其中之一"""

def isOne(num, bit_idx):
    return (num & (1 << bit_idx)) != 0


def findSingle(arr):
    size = len(arr)
    i = 0
    while i < 32:
        group0 = group1 = count0 = count1 = 0
        j = 0
        while j < size:
            if isOne(arr[j], i):
                group0 ^= arr[j]
                count0 += 1
            else:
                group1 ^= arr[j]
                count1 += 1
            j += 1
        i += 1

        if count0 % 2 == 1 and group0 != 0:
            return group0
        if count1 % 2 == 1 and group1 != 0:
            return group1


if __name__ == "__main__":
    array = [6, 3, 9, 4, 3, 9, 2, 4]
    print("Result is: ", findSingle(array))