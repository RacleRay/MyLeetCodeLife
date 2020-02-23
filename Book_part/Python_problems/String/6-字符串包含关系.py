# python3

"""str2中的字符是否全部包含在str1中"""

def isContain(str1, str2):
    flag_list = [0 for _ in range(52)]  # 大小写字母
    (longer, shorter) = (str1, str2) if len(str1) > len(str2) else (str2, str1)

    different_char_count = 0
    flag_idx = -1
    for char in shorter:
        if ord(char) >= ord('A') and ord(char) <= ord('Z'):
            flag_idx = ord(char) - ord('A')
        else:
            flag_idx = ord(char) - ord('a') + 26
        if flag_list[flag_idx] == 0:
            flag_list[flag_idx] = 1
            different_char_count += 1

    for char in longer:
        if ord(char) >= ord('A') and ord(char) <= ord('Z'):
            flag_idx = ord(char) - ord('A')
        else:
            flag_idx = ord(char) - ord('a') + 26
        if flag_list[flag_idx] == 1:
            flag_list[flag_idx] = 0
            different_char_count -= 1
            if different_char_count == 0:
                return True

    return False


if __name__ == '__main__':
    str1 = "abcdef"
    str2 = "bcr"
    print(isContain(str1, str2))