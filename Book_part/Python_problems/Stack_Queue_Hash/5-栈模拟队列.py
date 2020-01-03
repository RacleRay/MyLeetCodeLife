# python3
from stack import ArrayStack


class StackQueue:
    def __init__(self):
        self.input_stack = ArrayStack()
        self.output_stack = ArrayStack()

    def push(self, item):
        self.input_stack.push(item)

    def pop(self):
        if self.output_stack