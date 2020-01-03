# python3
from stack import ArrayStack


class StackQueue:
    def __init__(self):
        self.input_stack = ArrayStack()
        self.output_stack = ArrayStack()

    def push(self, item):
        self.input_stack.push(item)

    def pop(self):
        if self.output_stack.is_empty():
            while not self.input_stack.is_empty():
                self.output_stack.push(self.input_stack.pop())

        return self.output_stack.pop()


if __name__ == "__main__":
    queue = StackQueue()

    queue.push(1)
    queue.push(2)
    queue.push(3)

    print(queue.pop())
    print(queue.pop())
    print(queue.pop())