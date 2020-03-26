from collections import namedtuple, deque
from pprint import pprint as pp


inf = float('inf')
Edge = namedtuple('Edge', ['start', 'end', 'cost'])

class Dijkstra:
    def __init__(self, edges):
        self.edges = [Edge(*edge) for edge in edges]
        self.vertices = {e.start for e in self.edges} | {e.end for e in self.edges}

    def dijkstra(self, source, target):
        assert source in self.vertices
        dist = {vertex: inf for vertex in self.vertices}
        dist[source] = 0
        previous = {vertex: None for vertex in self.vertices}
        queue = self.vertices.copy()
        neighbors = {vertex: set() for vertex in self.vertices}
        for start, end, cost in self.edges:
            neighbors[start].add((end, cost))

        while queue:
            current = min(queue, key=lambda vertex: dist[vertex])
            queue.remove(current)
            if dist[current] == inf or current == target:
                break
            for neighbor, cost in neighbors[current]:
                temp = dist[current] + cost
                if temp < dist[neighbor]:
                    dist[neighbor] = temp
                    previous[neighbor] = current

        path = deque()
        u = target
        while previous[u]:
            path.appendleft(u)
            u = previous[u]
        path.appendleft(u)
        return path


if __name__ == "__main__":
    graph = Dijkstra([("a", "b", 7),  ("a", "c", 9),  ("a", "f", 14), ("b", "c", 10),
               ("b", "d", 15), ("c", "d", 11), ("c", "f", 2),  ("d", "e", 6),
               ("e", "f", 9)])
    pp(graph.dijkstra("a", "e"))

