# 在C++中能输出结果，因为溢出机制，python中该方法不会输出结果，死循环。原因在于sums变成负数之后会反向增长。
# def add(num1, num2):
#     """加法的一种计算方式，分解为 sums -- 每个位置相加但不考虑进位的结果；
#     carry -- 每个位置来自低位的进位
#     """
#     sums = num1 ^ num2
#     carry = num1 & num2
#     while carry != 0:
#         num1 = sums
#         num2 = carry << 1
#         sums = num1 ^ num2
#         carry = num1 & num2
#     return sums


# def sub(num1, num2):
#     """减法，加上相反数 -- 而计算机中的二进制表示下，为保证对储存单元的最大容量取模，负数为各位取反再加1"""
#     return add(num1, add(~num2, 1))


def sub2(num1, num2):
    while True:
        # 去除所有二级制中相同位置的1，剩余两个数的对应位要么都为0，要么一个1一个0
        same = num1 & num2
        num1 ^= same
        num2 ^= same

        # 临时结果：相同的1已经减去，剩下的情况当num1对应位置为1，num2为0，相减之后为1
        #                                     当num2对应位置为1，num1为0，相减之后为1，但是需要向num2为1的左边一位借1
        num1 |= num2
        # 借位carry：当借位为0，结果就是num1
        num2 <<= 1
        if num2 == 0:
            return num1



if __name__ == "__main__":
    print(sub2(123, 12))