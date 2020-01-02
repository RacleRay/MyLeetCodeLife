from stack import ArrayStack


class MinStack:
    """实现思路，使用一个额外的栈，保存当前栈中的最小元素"""
    def __init__(self):
        self.stack = ArrayStack()
        self.min_stack = ArrayStack()

    def push(self, item):
        self.stack.push(item)
        if self.min_stack.is_empty():
            self.min_stack.push(item)
        else:
            # 始终保持最小元素在栈顶
            if item < self.min_stack.top():
                self.min_stack.push(item)

    def pop(self):
        top_item = self.stack.pop()
        # 始终保持当前stack栈中的最小元素在min_stack栈顶
        if top_item == self.min_stack.top():
            _ = self.min_stack.pop()
        return top_item

    def min_item(self):
        if self.min_stack.is_empty():
            return None
        else:
            return self.min_stack.top()


if __name__ == "__main__":
    stack = MinStack()
    stack.push(100)
    print("Min is %d" % stack.min_item())
    stack.push(10)
    print("Min is %d" % stack.min_item())
    stack.push(1)
    print("Min is %d" % stack.min_item())
    stack.push(1000)
    print("Min is %d" % stack.min_item())
    stack.push(3)
    print("Min is %d" % stack.min_item())
