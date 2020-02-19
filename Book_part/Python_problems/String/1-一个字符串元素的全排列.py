# 递归方法

def swap(str_list, i, j):
    str_list[i], str_list[j] = str_list[j], str_list[i]

def permutate(str_list, start):
    if str_list is None or start < 0:
        return None

    if start == len(str_list) - 1:
        print("".join(str_list))
    else:
        i = start
        while i < len(str_list):
            swap(str_list, i, start)
            permutate(str_list, start + 1)  # 固定第一个位置
            swap(str_list, i, start)
            i += 1

def show_results(sting):
    permutate(list(sting), 0)


# 非递归
def getNextPermutation(string):
    # sting为升序
    end_idx = len(string) - 1
    cur = end_idx
    before_cur = 0
    while cur > 0:
        # 从后向前遍历字符串
        before_cur = cur
        cur -= 1
        if string[cur] < string[before_cur]:
            tmp = end_idx
            while string[tmp] < string[cur]:
                tmp -= 1
            swap(string, cur, tmp)
            reverse(string, before_cur, end_idx)
            return True
    return False

def reverse(string, begin, end):
    while begin < end:
        swap(string, begin, end)
        begin += 1
        end -= 1

def show_results2(string):
    if string is None or len(string) < 1:
        return None
    string_list = list(string)
    string_list.sort()  # 升序
    print("".join(string_list))
    while getNextPermutation(string_list):
        print("".join(string_list))


if __name__ == "__main__":
    s = 'abc'
    show_results(s)
    print()
    show_results2(s)