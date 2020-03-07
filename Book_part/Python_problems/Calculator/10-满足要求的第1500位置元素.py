"""满足能被2或3或5整除的第1500个元素"""


# 2，3，5的最小公倍数是30，那么每循环30个数字，就会出现重复的满足要求的数
def find(n):
    elems = [0]
    i = 1
    while i <= 30:
        if i % 2 == 0 or i % 3 == 0 or i % 5 == 0:
            elems.append(i)
        i += 1
    nums = len(elems)
    result = (n // 22) * 30 + elems[n % 22]  # 第n个数
    return result


if __name__ == '__main__':
    print(find(1500))

