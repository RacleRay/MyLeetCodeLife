# python3

def reorder(string):
    length = len(string)
    left_idx = 0
    right_idx = length - 1
    string = list(string)

    while left_idx < right_idx:
        # 从左向右找小写字母，遇到大写字母退出循环
        while string[left_idx] >= 'a' and string[left_idx] <= 'z' and left_idx < right_idx:
            left_idx += 1
        # 从右向左找大写字母，遇到小写字母退出循环
        while string[right_idx] >= 'A' and string[right_idx] <= 'Z' and left_idx < right_idx:
            right_idx -= 1
        string[left_idx], string[right_idx] = string[right_idx], string[left_idx]

    return "".join(string)

if __name__== "__main__":
    string = "AaBbCc"
    print(reorder(string))