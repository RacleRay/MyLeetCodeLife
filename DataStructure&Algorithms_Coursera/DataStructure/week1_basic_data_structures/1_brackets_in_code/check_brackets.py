# python3

from collections import namedtuple

Bracket = namedtuple("Bracket", ["char", "position"])


def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]


def find_mismatch(text):
    opening_brackets_stack = []
    if text[0] in ")]}":
        return 1

    for i, next in enumerate(text):
        if next not in '([{)]}':
            continue

        if next in "([{":
            opening_brackets_stack.append(Bracket(next, i))

        if next in ")]}":
            if len(opening_brackets_stack) == 0 or \
              not are_matching(opening_brackets_stack[-1].char, next):
                return i + 1
            else:
                opening_brackets_stack.pop()

    if len(opening_brackets_stack) == 0:
        return 'Success'
    else:
        return opening_brackets_stack[0].position + 1


def main():
    text = input()
    mismatch = find_mismatch(text)
    print(mismatch)


if __name__ == "__main__":
    main()
