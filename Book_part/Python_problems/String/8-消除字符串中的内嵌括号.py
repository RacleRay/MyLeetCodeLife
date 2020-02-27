"""(a,b,(c),d) >>> (a,b,c,d)"""


def removeParenthesis(string):
    if string is None:
        return None

    res = string[0]
    parentheses_num = 0
    i = 1
    while i < len(string) - 1:  # 开头和结尾括号不处理
        char = string[i]
        if char == '(':
            parentheses_num += 1
        elif char == ')':
            parentheses_num -= 1
        else:
            res = res + char
        i += 1

    if parentheses_num != 0:
        print("parenthesis is not paired.")
        return None

    res = res + string[-1]
    return res


if __name__ == '__main__':
    string = "(a,b,(c),d)"
    print(removeParenthesis(string))

