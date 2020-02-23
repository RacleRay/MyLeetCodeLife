# python3


def reverse(string, start, end):
    while start < end:
        string[start], string[end] = string[end], string[start]
        start += 1
        end -= 1


def swapWords(string):
    length = len(string)
    chars = list(string)

    reverse(chars, 0, length - 1)
    start = 0
    i = 1
    while i < length:
        if chars[i] == ' ':
            reverse(chars, start, i - 1)
            start = i + 1
        i += 1
    reverse(chars, start, length - 1)
    return "".join(chars)


if __name__ == '__main__':
    string = "hello words worth"
    print(swapWords(string))