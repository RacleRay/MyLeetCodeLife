# python3

class Solution:
    def __init__(self) -> None:
        self.SIZE = None

    def __isPossible(self, map_: list, x: int, y: int) -> bool:
        return x >= 0 and \
               x < self.SIZE and \
               y >= 0 and \
               y < self.SIZE and \
               map_[x][y] == 1

    def __arrive(self, x: int, y: int) -> bool:
        return x == self.SIZE - 1 and y == self.SIZE - 1

    def getPath(self, map_, x, y):
        self.SIZE = len(map_)
        sign_map = [[0] * self.SIZE for _ in range(self.SIZE)]

        if self.__arrive(x, y):
            sign_map[]