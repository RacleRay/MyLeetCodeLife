#python3
import sys

class StackWithMax():
    def __init__(self):
        self.__stack = []
        self.__maxstack = []

    def Push(self, a):

        if len(self.__stack) == 0:
            self.__maxstack.append(a)
            self.__stack.append(a)
        else:
            max_ = max(a, self.__maxstack[-1])

            if max_ == a:  # 只记录新的值
                self.__maxstack.append(a)

        self.__stack.append(a)


    def Pop(self):
        assert(len(self.__stack))
        if self.__stack.pop() == self.__maxstack[-1]:
            self.__maxstack.pop()

    def Max(self):
        assert(len(self.__stack))
        return self.__maxstack[-1]


if __name__ == '__main__':
    stack = StackWithMax()

    num_queries = int(sys.stdin.readline())
    for _ in range(num_queries):
        query = sys.stdin.readline().split()

        if query[0] == "push":
            stack.Push(int(query[1]))
        elif query[0] == "pop":
            stack.Pop()
        elif query[0] == "max":
            print(stack.Max())
        else:
            assert(0)

    # for query in [['push', 7], ['push', 1], ['push', 7], ['max'], ['pop'], ['max']]:
    #
    #     if query[0] == "push":
    #         stack.Push(int(query[1]))
    #     elif query[0] == "pop":
    #         stack.Pop()
    #     elif query[0] == "max":
    #         print(stack.Max())
    #     else:
    #         assert(0)
