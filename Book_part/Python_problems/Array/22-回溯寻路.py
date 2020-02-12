# python3

class Solution:
    def __init__(self, map_) -> None:
        self.SIZE = len(map_)
        self.map_ = map_
        self.sign_map = [[0] * self.SIZE for _ in range(self.SIZE)]

    def __isPossible(self, x: int, y: int) -> bool:
        return x >= 0 and \
               x < self.SIZE and \
               y >= 0 and \
               y < self.SIZE and \
               self.map_[x][y] == 1

    def __arrive(self, x: int, y: int) -> bool:
        return x == self.SIZE - 1 and y == self.SIZE - 1

    def getPath(self, x, y):
        self.SIZE = len(map_)

        if self.__arrive(x, y):
            self.sign_map[x][y] = 1
            return True

        if self.__isPossible(x, y):
            self.sign_map[x][y] = 1
            if self.getPath(x + 1, y):
                return True
            if self.getPath(x, y + 1):
                return True
            self.sign_map[x][y] = 0  # 该位置没有通路
            return False

        return False


if __name__ == "__main__":
    map_ = [[1, 0, 0, 0],[1, 1, 0, 1],[0, 1, 0, 0], [1, 1, 1, 1]]
    sol = Solution(map_)
    if sol.getPath(0, 0):
        print(sol.sign_map)
