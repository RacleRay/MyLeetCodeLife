# python3

from stack import ArrayStack


def moveButtonToTop(stack):
    """递归处理，使栈底元素逐层移动到顶层。O(N)

    Arguments:
        stack {array stack}
    """
    if stack.is_empty():
        return

    top = stack.pop()

    # Recursion
    if not stack.is_empty():
        # 取得所有栈顶元素为top
        moveButtonToTop(stack)

        # 递归返回前的收尾操作
        top_sub = stack.pop()

        # 交换
        stack.push(top)
        stack.push(top_sub)
    else:
        stack.push(top)


def reverse(stack):
    """递归处理每一个子栈，逐个将子栈的栈底元素移动到栈顶。O(N)

    Arguments:
        stack {array stack}
    """
    if stack.is_empty():
        return

    moveButtonToTop(stack)

    top = stack.pop()

    # Recursion
    reverse(stack)
    stack.push(top)


if __name__ == '__main__':
    stack = ArrayStack()

    # 顶【5，4，3，2，1】
    for i in range(5):
        stack.push(i + 1)

    reverse(stack)

    while not stack.is_empty():
        print(stack.pop())

