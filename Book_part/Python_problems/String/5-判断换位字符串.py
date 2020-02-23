# python3
"""字符组成相同，但是字符位置不同"""


def compare(str1, str2):
    count_list = [0 for _ in range(256)]  # ASCII
    for char in str1:
        count_list[ord(char) - ord('0')] += 1

    for char in str2:
        count_list[ord(char) - ord('0')] -= 1

    result = True
    for val in count_list:
        if val != 0:
            result = False
            break

    return result


if __name__ == "__main__":
    str1 = "aaabbcc"
    str2 = "babacac"
    print(compare(str1, str2))