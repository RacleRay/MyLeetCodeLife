# python3

from stack import ArrayStack


def moveButtonToTop(stack):
    """递归处理，使栈底元素逐层移动到顶层，同时根据大小选择是否交换位置。O(N)
    从栈顶到栈底，从大到小。

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
        if top < top_sub:
            stack.push(top)
            stack.push(top_sub)
        else:
            stack.push(top_sub)
            stack.push(top)

    else:
        stack.push(top)


def sortStack(stack):
    """递归处理每一个子栈，逐个将子栈的栈底元素移动到栈顶。O(N)

    Arguments:
        stack {array stack}
    """
    if stack.is_empty():
        return

    moveButtonToTop(stack)

    top = stack.pop()

    # Recursion
    sortStack(stack)
    stack.push(top)


if __name__ == '__main__':
    stack = ArrayStack()

    # 顶【5，4，3，2，1】
    for i in range(5):
        stack.push(i + 1)

    sortStack(stack)

    while not stack.is_empty():
        print(stack.pop())