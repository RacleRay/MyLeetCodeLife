"""不重复数：比如，1201，1234，而1101和1224这种相邻位置相同的数字为不重复数。
给定任意一个正整数，求大于该数的最小不重复数。
"""
def carryFill(num_list, idx):
    while idx > 0:
        if int(num_list[idx]) > 9:
            num_list[idx] = '0'
            num_list[idx - 1] = str(num_list[idx - 1] + 1)
        idx -= 1


def find(n):
    num_list = [int(ch) for ch in str(n)]
    lens = len(num_list)

    i = 1
    while i < lens:
        if num_list[i - 1] == num_list[i]:
            num_list[i] += 1
            carryFill(num_list, i)
            for j in range(i + 1, lens):
                num_list[j] = (j - 1) % 2
        i += 1

    return int(''.join([str(num) for num in num_list]))


if __name__ == '__main__':
    print(find(23345))
    print(find(1101010))
