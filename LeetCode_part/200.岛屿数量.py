"""
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1
示例 2:

输入:
11000
11000
00100
00011

输出: 3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/number-of-islands
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
"""
import collections

class Solution(object):

    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        # 方法一：DFS
        if not grid or not grid[0]:
            return 0
        self.max_x = len(grid)
        self.max_y = len(grid[0])
        self.grid = grid
        self.visited = set()

        self.dx = [-1, 1, 0, 0]
        self.dy = [0, 0, -1, 1]

        return sum([self.floodfill_DFS(i, j) for i in range(self.max_x) for j in range(self.max_y)])

    def floodfill_DFS(self, x, y):
        """寻找最大岛"""
        if not self._is_valid(x, y):
            return 0

        self.visited.add((x, y))
        for k in range(4):
            self.floodfill_DFS(x + self.dx[k], y + self.dy[k])

        return 1

    def _is_valid(self, x, y):
        if x < 0 or x >= self.max_x or y < 0 or y >= self.max_y:
            return False
        if self.grid[x][y] == '0' or ((x, y) in self.visited):
            return False
        return True

    # 方法二：BFS
    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0
        self.max_x = len(grid)
        self.max_y = len(grid[0])
        self.grid = grid
        self.visited = set()

        self.dx = [-1, 1, 0, 0]
        self.dy = [0, 0, -1, 1]

        return sum(self.floodfill_BFS(i, j) for i in range(self.max_x) for j in range(self.max_y))

    def floodfill_BFS(self,x, y):
        if not self._is_valid(x, y):
            return 0

        self.visited.add((x, y))
        queue = collections.deque()
        queue.append((x, y))

        while queue:
            cur_x, cur_y = queue.popleft()
            for i in range(4):
                new_x, new_y = cur_x + self.dx[i], cur_y + self.dy[i]
                if self._is_valid(new_x, new_y):
                    self.visited.add((new_x, new_y))
                    queue.append((new_x, new_y))

        return 1

    def _is_valid(self, x, y):
        if x < 0 or x >= self.max_x or y < 0 or y >= self.max_y:
            return False
        if self.grid[x][y] == '0' or ((x, y) in self.visited):
            return False
        return True

    # bonus：
    # 超简洁实现
    def numIslands(self, grid):
        def sink(i, j):
            if 0 <= i < len(grid) and 0 <= j < len(grid[0]) and grid[i][j] == '1':
                grid[i][j] = '0'  # 同一个岛已经走过变成0，实际上最好复制一份grid，不要在源数据上操作
                map(sink, (i+1, i-1, i, i), (j, j, j+1, j-1))  # 只有无路可走才返回
                return 1
            return 0
        return sum(sink(i, j) for i in range(len(grid)) for j in range(len(grid[0])))


    # 方法三：并查集
    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0

        uf = UnionFind(grid)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        m, n = len(grid), len(grid[0])

        for i in range(m):
            for j in range(n):
                if grid[i][j] == '0':
                    continue
                for d in directions:
                    new_m, new_n = i + d[0], j + d[1]
                    if new_m >= 0 and new_n >= 0 and new_m < m and new_n < n \
                        and grid[new_m][new_n] == '1':
                        uf.union(i*n + j, new_m*n + new_n)

        return uf.count



class UnionFind(object):
    def __init__(self, grid):
        m, n = len(grid), len(grid[0])
        self.count = 0
        self.parent = [-1] * (m*n)  # 父节点
        self.rank = [0] * (m*n)  # 深度
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1':
                    self.parent[i*n + j] = i*n + j  # 二维坐标转换为一维, 并指向自身
                    self.count += 1

    def find(self, i):
        """find root"""
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, x, y):
        rootx = self.find(x)
        rooty = self.find(y)
        if rootx != rooty:
            # rank低的，将root指向rank高的root
            if self.rank[rootx] > self.rank[rooty]:
                self.parent[rooty] = rootx
            elif self.rank[rootx] < self.rank[rooty]:
                self.parent[rootx] = rooty
            else:
                self.parent[rooty] = rootx
                self.rank[rootx] += 1
            self.count -= 1  # 不同集合合并次数





