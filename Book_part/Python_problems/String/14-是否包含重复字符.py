def isDuplicate(string):
    length = len(string)

    flag_list = [0 for _ in range(8)]  # 一个int占32bit，一个bit为一个标记位代表一个ascii字符对应的ord
    i = 0
    while i < length:
        index = ord(string[i]) // 32
        shift = ord(string[i]) % 32
        if flag_list[index] & (1 << shift) != 0:
            return True
        flag_list[index] |= (1 << shift)

    return False


if __name__ == "__main__":
    print(isDuplicate("hello"))