# python3


def reverse(string):
    chars = list(string)
    length = len(chars)
    i = 0; j = length - 1
    while i < j:
        chars[i], chars[j] = chars[j], chars[i]
        i += 1
        j -= 1
    return "".join(chars)


def reverse2(string):
    """异或法

    令 a_new = a ^ b 那么：
        令 b_new = a_new ^ b = a ^ (b ^ b) = a ^ 0 = a
        令 a_new = a_new ^ b_new = (a ^ b) ^ a = b
    """
    chars = list(string)
    length = len(chars)
    i = 0; j = length - 1
    while i < j:
        chars[i] = chr(ord(chars[i]) ^ ord(chars[j]))
        chars[j] = chr(ord(chars[i]) ^ ord(chars[j]))
        chars[i] = chr(ord(chars[i]) ^ ord(chars[j]))
        i += 1
        j -= 1
    return "".join(chars)


if __name__ == "__main__":
    string = "abcde"
    print(reverse(string))
    print(reverse2(string))
