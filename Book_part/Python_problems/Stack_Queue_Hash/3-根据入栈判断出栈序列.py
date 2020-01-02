from stack import ArrayStack


def is_pop_series(push_seq,  pop_seq):
    if push_seq is None or pop_seq is None:
        return False

    push_len = len(push_seq)
    pop_len = len(pop_seq)
    if push_len != pop_len:
        return False

    push_idx = 0
    pop_idx = 0
    stack = ArrayStack()
    while push_idx < push_len:
        stack.push(push_seq[push_idx])
        push_idx += 1

        # 出栈条件
        while not stack.is_empty() and stack.top() == pop_seq[pop_idx]:
            _ = stack.pop()
            pop_idx += 1

    # 栈为空，且pop元素全部遍历
    return stack.is_empty() and pop_idx == pop_len


if __name__ == "__main__":
    push_seq = "12345"
    pop_seq = "32541"
    if is_pop_series(push_seq, pop_seq):
        print("True")
    else:
        print("False")
