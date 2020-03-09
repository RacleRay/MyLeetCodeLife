"""给出1 2 2 3 4 5，组合出4不在第三位，3和5不相连的数字。"""


class Solution:
    def __init__(self, elems: list):
        self.elems = elems
        self.size = len(elems)
        self.graph = [[0] * self.size for _ in range(self.size)]
        self.visited = [0 for _ in range(self.size)]
        self.tmp = ''
        self.res = set()

    def depthFirstSearch(self, start):
        self.visited[start] = 1
        self.tmp += str(self.elems[start])

        # 提前截断第3位是4的
        if len(self.tmp) == 3 and self.tmp[-1] == '4':
            self.tmp = self.tmp[:-1]  # 回溯
            self.visited[start] = 0  # 回溯使得当前遍历变为可用
            return None

        if len(self.tmp) == self.size:
            self.res.add(self.tmp)

        i = 0
        while i < self.size:
            if self.graph[start][i] == 1 and self.visited[i] == 0:
                self.depthFirstSearch(i)
            i += 1
        self.tmp = self.tmp[:-1]  # 回溯
        self.visited[start] = 0  # 回溯使得当前遍历变为可用

    def getCombination(self):
        # build graph
        for i in range(self.size):
            for j in range(self.size):
                if i == j:
                    self.graph[i][j] = 0
                else:
                    self.graph[i][j] = 1
        self.graph[3][5] = 0
        self.graph[5][3] = 0

        # search
        for i in range(self.size):
            self.depthFirstSearch(i)

    def getResult(self):
        return self.res


if __name__ == "__main__":
    elems = [1, 2, 2, 3, 4, 5]
    sol = Solution(elems)
    sol.getCombination()
    print(sol.getResult())
